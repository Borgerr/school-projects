#include <string>
#include <vector>
#include <map> // change if necessary
#include "MenuData.h"

MenuData::MenuData() {
	// deez nuts
}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
	mCommands.push_back(name);
	commandToFunction[name] = func;
	commandToDesc[name] = description;
}

const std::vector<std::string>& MenuData::getNames() const {
	return mCommands;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
	// if name is a key in the action function map, return associated function
	// else return 0.
	if (commandToFunction.find(name) != commandToFunction.end()) {
		return commandToFunction[name];
	}else {
		return 0;
	}
}

const std::string& MenuData::getDescription(const std::string& name) {
	if (commandToDesc.find(name) != commandToDesc.end()) {
		return commandToDesc[name];
	}else {
		static std::string returned = "";
		return returned;
	}
}
