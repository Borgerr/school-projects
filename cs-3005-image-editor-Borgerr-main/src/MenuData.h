#ifndef __MENUDATA_H_
#define __MENUDATA_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ActionData.h"

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:
	MenuData();
	void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
	const std::vector<std::string>& getNames() const;
	ActionFunctionType getFunction(const std::string& name);
	const std::string& getDescription(const std::string& name);
protected:
	std::vector<std::string> mCommands;
	std::map<std::string, ActionFunctionType> commandToFunction;
	std::map<std::string, std::string> commandToDesc;
};

#endif //__MENUDATA_H_
