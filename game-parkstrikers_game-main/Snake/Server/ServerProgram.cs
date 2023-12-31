﻿using NetworkUtil;
using GameModel;
using System.Text.RegularExpressions;
using Newtonsoft.Json;
using System.Xml;
using System.Runtime.Serialization;

namespace Server
{
    internal class GameServer
    {
        private Dictionary<long, SocketState> clients;
        private ServerWorld zeWorld;
        public GameSettings settings;
        private int MSPerFrame;
        static void Main(string[] args)
        {
            GameServer server = new();
            GameSettings? settings;
            // XML stuff

            // Set the reader settings.
            XmlReaderSettings xmlsettings = new XmlReaderSettings();
            xmlsettings.IgnoreComments = true;
            xmlsettings.IgnoreProcessingInstructions = true;
            xmlsettings.IgnoreWhitespace = true;

            try
            {   // try to find settings.xml
                try
                {
                    using (XmlReader reader = XmlReader.Create("settings.xml", xmlsettings))
                    {
                        DataContractSerializer ser = new DataContractSerializer(typeof(GameSettings));
                        settings = (GameSettings?)ser.ReadObject(reader);
                    }
                }
                catch
                {
                    using (XmlReader reader = XmlReader.Create("../../../settings.xml", xmlsettings))
                    {
                        DataContractSerializer ser = new DataContractSerializer(typeof(GameSettings));
                        settings = (GameSettings?)ser.ReadObject(reader);
                    }
                }
            }

            catch
            { // file was not found and the server should not start
                Console.WriteLine("file settings.xml not found. Did you put it in the right spot?");
                settings = null;    // so that settings is not unassigned
            }


            // ensure settings are valid. stop program if not
            if (settings is null)
                return;

            // make settings instance accessible by server methods
            server.settings = settings;

            server.zeWorld = new ServerWorld(settings);
            server.MSPerFrame = settings.MSPerFrame;

            server.StartServer();

            server.Run();     // main update loop
            // Sleep to prevent program from closing.
            // this thread is done, but other threads are still working.
            server.Run();     // main update loop
        }

        /// <summary>
        /// Initialized server's state
        /// </summary>
        public GameServer()
        {
            clients = new Dictionary<long, SocketState>();
            zeWorld = new ServerWorld();
            settings = new GameSettings();
        }

        /// <summary>
        /// Start accepting socket connections from clients
        /// </summary>
        public void StartServer()
        {
            // begin event loop
            Networking.StartServer(NewClientConnected, 11000);

            Console.WriteLine("Server is running. Accepting clients.");
        }

        /// <summary>
        /// Method invoked by networking library on new connection (StartServer)
        /// </summary>
        private void NewClientConnected(SocketState state)
        {
            if (state.ErrorOccurred)
            {
                Console.WriteLine("Error connecting client ID " + state.ID);
                RemoveClient(state.ID);
                return;
            }

            // delegate to be invoked whenever we receive some data from this client
            state.OnNetworkAction = ReceiveName;

            Console.WriteLine("Client " + state.ID + " has connected.");

            // data thread loop
            Networking.GetData(state);
        }

        /// <summary>
        /// initial handshake protocol for receiving player name
        /// </summary>
        /// <param name="state"></param>
        private void ReceiveName(SocketState state)
        {
            if (state.ErrorOccurred)
            {
                Console.WriteLine("Error finishing handshake with client ID " + state.ID);
                RemoveClient(state.ID);
                return;
            }

            string totalData = state.GetData();
            // Ignore empty strings added by the regex splitter
            if (totalData.Length == 0)
                return;

            // haven't received terminator character yet
            if (totalData[totalData.Length - 1] != '\n')
                return;

            // in this last case we have a full message ending with a terminator character
            // that we can use as a name

            // add client information to model
            lock (zeWorld)
            {
                //Checks if a snake can be added into the client
                if (!zeWorld.AddSnake(Regex.Replace(totalData, @"\t|\n|\r", ""), (int)state.ID))
                    RemoveClient(state.ID);

                // PS9 FAQ states to first send then add state to client set
                // is important because we need to ensure the client gets handshake info FIRST
                // and there are other threads broadcasting everything to all clients.
                Networking.Send(state.TheSocket,
                    state.ID + "\n"                 // send client ID
                + settings.UniverseSize + "\n");    // and then worldsize

                state.OnNetworkAction = ReceiveData;
                Console.WriteLine("Player " + Regex.Replace(totalData, @"\t|\n|\r", "") + " has joined the game.");


                // send Walls information to the client
                foreach (Wall wall in zeWorld.Walls)
                    SerializeAndSend(wall, state);
            }

            if (state.ErrorOccurred)
            {
                Console.WriteLine("Error finishing handshake with client ID " + state.ID);
                RemoveClient(state.ID);
                return;
            }

            // add client state to set of connections
            // locks for race conditions etc
            lock (clients)
            {
                clients.Add(state.ID, state);
            }

            // messaged was processed correctly so we can remove it
            state.RemoveData(0, totalData.Length);


            // resume client receive loop with whichever delegate is valid at this point
            Networking.GetData(state);
        }

        /// <summary>
        /// Method invoked by networking library on data receive
        /// </summary>
        /// <param name="state"></param>
        private void ReceiveData(SocketState state)
        {
            if (state.ErrorOccurred)
            {
                Console.WriteLine("Client " + state.ID + " disconnected");
                RemoveClient(state.ID);
                return;
            }

            // apply movement request
            ProcessData(state);

            // resume thread loop
            Networking.GetData(state);
        }

        /// <summary>
        /// Gathers the JSON strings and seperates them into substrings interpreted as movement commands
        /// </summary>
        /// <param name="state"></param>
        private void ProcessData(SocketState state)
        {
            string totalData = state.GetData();
            // splits received strings into substrings that end in newline
            string[] parts = Regex.Split(totalData, @"(?<=[\n])");


            lock (zeWorld)
            {
                // loop until we process all messages.
                // We may have received more than one.
                foreach (string p in parts)
                {
                    // Ignore empty strings added by the regex splitter
                    if (p.Length == 0)
                        continue;

                    // terminator string wasn't included
                    if (p[p.Length - 1] != '\n')
                        continue;

                    ControlCommand? Movement = JsonConvert.DeserializeObject<ControlCommand>(p);

                    // then we are given some weird string with a terminator character at the end
                    // possibly change to disable or remove client
                    if (Movement is null)
                        continue;

                    zeWorld.MoveSnake((int)state.ID, Movement);

                    state.RemoveData(0, p.Length);
                }
            }
        }

        /// <summary>
        /// Serializes some object to prepare it to be sent over the network.
        /// Uses should only be for walls, snakes, and powerups.
        /// </summary>
        /// <param name="obj"> a wall, snake, or powerup </param>
        private static void SerializeAndSend(object obj, SocketState socket)
        {
            // this method should only be sending a Snake, Wall, or Powerup instance
            if (obj is not Snake && obj is not Wall && obj is not Powerup)
                return;

            string toSendString = JsonConvert.SerializeObject(obj) + "\n";  // collection was modified error thrown here
            while (!Networking.Send(socket.TheSocket, toSendString))
            { /* mine for bitcoin */ }
        }

        /// <summary>
        /// Removes client from client set
        /// </summary>
        private void RemoveClient(long id)
        {
            Console.WriteLine("Client " + id + " disconnected");
            lock (clients)
                clients.Remove(id);

            // set dc and dead to true for next update frame
            if (zeWorld.Snakes.ContainsKey((int)id))
                lock (zeWorld)
                    zeWorld.Snakes[(int)id].Disconnect();
        }

        /// <summary>
        /// runs the server. a majority of the processing time should be spent in here from our program
        /// and our 
        /// </summary>
        public void Run()
        {
            // Start a new timer to control the frame rate
            System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
            watch.Start();

            while (true)
            {
                // wait until the next frame
                while (watch.ElapsedMilliseconds < MSPerFrame)
                { /* empty loop body */ }

                //Console.WriteLine("FPS: " + watch.ElapsedMilliseconds);

                watch.Restart();

                Update();
            }
        }

        /// <summary>
        /// method for communicating updates to the world
        /// </summary>
        private void Update()
        {
            // update objects and send them to each client

            string snakeSend = "";
            string powerSend = "";

            zeWorld.AddPower();

            lock (zeWorld)
            {
                // move each snake
                foreach (Snake s in zeWorld.Snakes.Values)
                {
                    snakeSend += JsonConvert.SerializeObject(s) + "\n";

                    if (!s.alive)
                    {
                        s.incrementDeathCounter();
                        zeWorld.CheckForRespawn(s);
                    }

                    else
                    {
                        s.Move(settings.UniverseSize);
                        s.incrementTurnCounter();
                    }
                    
                }
                
                // check for collisions
                foreach(Snake s in zeWorld.Snakes.Values)
                {
                    foreach (Wall wall in zeWorld.Walls)
                    {
                        if (s.CheckWallCollision(wall))
                        {
                            s.die();
                        }
                    }

                    foreach (Snake snake in zeWorld.Snakes.Values)
                    {
                        if (s.CheckSnakeCollision(snake, settings.UniverseSize))
                        {
                            if(s.ID == snake.ID && s.CheckSelfCollision(settings.UniverseSize))
                                s.die();
                            else
                            {
                                if (s.alive is true && zeWorld.BattleRoyale is true)
                                    snake.Grow();
                                s.die();
                                
                            }
                        }
                    }

                    foreach (Powerup p in zeWorld.Powerups.Values)
                    {
                        if (s.CheckPowerCollision(p))
                        {
                            p.die();
                            s.Grow();
                        }
                    }
                }

                foreach (Powerup p in zeWorld.Powerups.Values)
                {
                    powerSend += JsonConvert.SerializeObject(p) + "\n";
                }

            }

            lock (clients)
            {
                foreach(SocketState client in clients.Values)
                {
                    Networking.Send(client.TheSocket, snakeSend);
                    Networking.Send(client.TheSocket, powerSend);
                }
            }

            IEnumerable<int> playersToRemove = zeWorld.Snakes.Values.Where(snake => snake.dc).Select(snake => snake.ID);
            IEnumerable<int> powerToRemove = zeWorld.Powerups.Values.Where(powerup => (powerup.died)).Select(powerup => powerup.ID);
            foreach (int i in playersToRemove)
                zeWorld.Snakes.Remove(i);
            foreach (int i in powerToRemove)
                zeWorld.Powerups.Remove(i);
        }
    }


}