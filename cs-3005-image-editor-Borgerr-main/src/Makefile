#a note on .in files:
#only seperate with lines between commands. If you're entering in arguments for certain commands,
#include those arguments on the same line as the command itself.
#target: dependency
#variable := (do this thing)
#used by $(variable)
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -Wpedantic
#CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -Wpedantic -g	#debugger
LDFLAGS := -lpthread
DEPENDENCIES := user_io.o controllers.o image_drawing.o image_output.o PPM.o ActionData.o MenuData.o Image.o image_filters.o NumberGrid.o ColorTable.o ComplexFractal.o JuliaSet.o MandelbrotSet.o ThreadedGrid.o

#executable programs
all: hello questions_3 ascii_image image_file four_square simple_squares_ascii hero ppm_menu

homework: hello questions_3 ascii_image image_file ppm_menu

exams: four_square simple_squares_ascii hero

hello: hello.o
	g++ $(CXXFLAGS) -o hello hello.o

questions_3: questions_3.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o questions_3 questions_3.o $(DEPENDENCIES) $(LDFLAGS)

ascii_image: ascii_image.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o ascii_image ascii_image.o $(DEPENDENCIES) $(LDFLAGS)

image_file: image_file.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o image_file image_file.o $(DEPENDENCIES) $(LDFLAGS)

ppm_menu: ppm_menu.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o ppm_menu ppm_menu.o $(DEPENDENCIES) $(LDFLAGS)

#exam programs
four_square: four_square.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o four_square four_square.o $(DEPENDENCIES)

simple_squares_ascii: simple_squares_ascii.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o simple_squares_ascii simple_squares_ascii.o $(DEPENDENCIES)

hero: hero.o $(DEPENDENCIES)
	g++ $(CXXFLAGS) -o hero hero.o $(DEPENDENCIES)

#.o files
image_file.o: image_file.cpp
	g++ $(CXXFLAGS) -c -o image_file.o image_file.cpp

controllers.o: controllers.cpp
	g++ $(CXXFLAGS) -c -o controllers.o controllers.cpp

PPM.o: PPM.cpp PPM.h Image.o
	g++ $(CXXFLAGS) -c -o PPM.o PPM.cpp

Image.o: Image.cpp Image.h
	g++ $(CXXFLAGS) -c -o Image.o Image.cpp

image_drawing.o: image_drawing.cpp
	g++ $(CXXFLAGS) -c -o image_drawing.o image_drawing.cpp

image_output.o: image_output.cpp
	g++ $(CXXFLAGS) -c -o image_output.o image_output.cpp

ascii_image.o: ascii_image.cpp
	g++ $(CXXFLAGS) -c -o ascii_image.o ascii_image.cpp

hello.o: hello.cpp
	g++ $(CXXFLAGS) -c -o hello.o hello.cpp

questions_3.o: questions_3.cpp
	g++ $(CXXFLAGS) -c -o questions_3.o questions_3.cpp

user_io.o: user_io.cpp
	g++ $(CXXFLAGS) -c -o user_io.o user_io.cpp

four_square.o: four_square.cpp
	g++ $(CXXFLAGS) -c -o four_square.o four_square.cpp

simple_squares_ascii.o: simple_squares_ascii.cpp
	g++ $(CXXFLAGS) -c -o simple_squares_ascii.o simple_squares_ascii.cpp

hero.o: hero.cpp
	g++ $(CXXFLAGS) -c -o hero.o hero.cpp

ActionData.o: ActionData.cpp
	g++ $(CXXFLAGS) -c -o ActionData.o ActionData.cpp

MenuData.o: MenuData.cpp
	g++ $(CXXFLAGS) -c -o MenuData.o MenuData.cpp

ppm_menu.o: ppm_menu.cpp
	g++ $(CXXFLAGS) -c -o ppm_menu.o ppm_menu.cpp

image_filters.o: image_filters.cpp
	g++ $(CXXFLAGS) -c -o image_filters.o image_filters.cpp

NumberGrid.o: NumberGrid.cpp NumberGrid.h
	g++ $(CXXFLAGS) -c -o NumberGrid.o NumberGrid.cpp

ColorTable.o: ColorTable.cpp ColorTable.h
	g++ $(CXXFLAGS) -c -o ColorTable.o ColorTable.cpp

ComplexFractal.o: ComplexFractal.cpp ComplexFractal.h
	g++ $(CXXFLAGS) -c -o ComplexFractal.o ComplexFractal.cpp

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	g++ $(CXXFLAGS) -c -o JuliaSet.o JuliaSet.cpp

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h
	g++ $(CXXFLAGS) -c -o MandelbrotSet.o MandelbrotSet.cpp

ThreadedGrid.o: ThreadedGrid.cpp ThreadedGrid.h
	g++ $(CXXFLAGS) -c -o ThreadedGrid.o ThreadedGrid.cpp

clean:
	rm -f *.o
	rm -f *.ppm
	rm -f questions_3 hello ascii_image image_file four_square simple_squares_ascii hero ppm_menu
