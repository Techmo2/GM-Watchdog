/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 ---------------------------------
 
 This is the main code for my gmod utility collection. This set of functions 
 and utilities intended to be used consistently across many different modules.
 These functions provide useful functionality without the need to rewrite the 
 the same code for each use.
*/

#include "utils.h"
#include "colors.h"
#include <cstdarg>

CreateInterfaceFn engineInterface;
IVEngineServer* engine;

void Utils::init() {
	engineInterface = Sys_GetFactory("engine.dll");
	engine = (IVEngineServer*)engineInterface(VENGINESERVER_INTERFACEVERSION_21, NULL);
}



/*
 Author - Bradly Tillmann (Techmo)
 Update - 6/30/18
 Function - 
	These function(s) is designed to take any arbritrary amounf of values as
	arguments, and combine them all into a single std::string. Currently, 
	only values with the types 'const char*' and 'char*' can be used, but
	support for values such as 'int', 'double', 'float', and 'char' is
	in progress.

 Example -
	std::string message = Utils::formstring("Setting health for player ", player_name, " to ", std::to_string(player_health + heal_amount));
*/
template<typename T>
std::string Utils::formstring(T t) {
	return std::string(t);
}

template<typename T, typename... Others>
std::string Utils::formstring(T t, Others... others) {
	return std::string(t) + formstring(others...);
}



/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 Function -
	This function prints a given message to the console.

 Example - 
	Utils::PrintC("Friendly fire enabled");
*/
void Utils::PrintC(const char* msg, ...) {
	Msg(msg);
}



/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 Function -
	This function prints a given message to the console in the specified color.

 Example - 
	Utils::PrintC(Color(0, 0, 255, 255), "The door has opened");
*/
void Utils::PrintC(Color& c, const char* msg, ...) {
	ConColorMsg(c, msg);
}



/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 Function -
	This function logs messages to the console with the title of the module it
	came from to make it easier to know where the message came from.

 Example -
	Utils::LogC("Configuration file loaded");
*/
void Utils::LogC(const char* msg, ...) {
	std::string out = formstring("[", MODULE_TITLE, "]| ", msg, "\n");
	Msg(out.c_str());
}



/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 Function -
	This function logs messages to the console with the title of the module it
	came from to make it easier to know where the message came from. The log 
	made is in the specified color.

 Example -
	Utils::LogC(Color(150, 90, 0, 200), "Configuration file loaded");
*/
void Utils::LogC(Color& c, const char* msg, ...) {
	std::string out = formstring("[", MODULE_TITLE, "]| ", msg, "\n");
	ConColorMsg(c, out.c_str());
}



/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 Function -
	This function simply prints the module's title, version, and author to the console.

 Example -
	Utils::PrintVersion();
*/
void Utils::PrintVersion() {
	std::string out = formstring(MODULE_TITLE, " ", MODULE_VERSION, " (written in c by ", AUTHOR_USERNAME, ")", "\n");
	ConColorMsg(COLOR_LOG, out.c_str());
}



/*
Author - Bradly Tillmann (Techmo)
Last Update - 7/1/18
Function -
	This function sends a command to the server console.

Example -
	Utils::RunCommand("say hello");
*/
void Utils::RunCommand(const char* cmd, ...) {
	engine->GMOD_RawServerCommand(cmd);
}