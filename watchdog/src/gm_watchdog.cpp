/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 ---------------------------------

 This is the main file for the watchdog module. The watchdog module is designed
 to detect when a server crashes, and stops code execution. The server process doesn't necessarily
 have to completely close for it to be detected because of the use of a watchdog timer. The timer
 runs in a thread that is separate from the main server thread to avoid interruption. Under normal
 operation, the server thread resets the watchdog timer every tick before it runs out. If the timer
 runs out, it indicates that the server thread is no longer running, and action can be taken.
*/

#include "GarrysMod/Lua/Interface.h"
#include "watchdog.h"
#include "module.h"
#include "utils.h"
#include <convar.h>
#include <cdll_int.h>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace GarrysMod::Lua;
Watchdog* dog;
char* batchFilePath;


// This makes pushing C functions to the lua global stack much cleaner
int pushFunction(lua_State* state, const char* name, GarrysMod::Lua::CFunc func) {
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushString(name);
	LUA->PushCFunction(func);
	LUA->SetTable(-3);

	return 0;
}

// Starts the watchdog timer with the appropriate timeout value (in milliseconds)
int WatchdogStart(lua_State* state) {
	if (LUA->GetType(1) == Type::NUMBER) {

		// Ensure file exists
		std::ofstream file("../../watchdog.cfg", std::ios::app);
		file.close();

		// Read config
		std::string path;
		std::ifstream rfile("../../watchdog.cfg");
		if (rfile.is_open()) {
			std::getline(rfile, path);
			rfile.close();
		}

		// Ensure a batch file is specified
		if (!std::strcmp(path.c_str(), "")) {
			int timeout = LUA->GetNumber(1);
			dog = new Watchdog(timeout, path.c_str());
			dog->Start();
			Utils::LogC(Color(255, 83, 13, 200), Utils::formstring("Watchdog timer started with timeout of ", std::to_string(timeout).c_str(), " milliseconds").c_str());
		}
		else {
			Utils::LogC(Color(255, 83, 13, 200), "No batch file specified in watchdog.cfg, stopping server");
			exit(1);
		}
		
	}
	return 1;
}

// Resets the watchdog timer. Needs to be called before the timer runs out.
int KickDog(lua_State* state) {
	dog->KickDog();
	//Utils::LogC(Color(0, 100, 255, 200), "Dog kicked");
	return 1;
}

// Called by Garry's Mod when this module is loaded
GMOD_MODULE_OPEN()
{
	Utils::init();
	Utils::PrintVersion();

	Utils::LogC(Color(255, 83, 13, 200), "Loading timer functions");
	pushFunction(state, "WatchdogStart", WatchdogStart);
	pushFunction(state, "KickDog", KickDog);

	Utils::LogC(Color(255, 83, 13, 200), "Enabling hooks without players");
	Utils::RunCommand("sv_hibernate_think 1"); // Run the "Tick" hook even when nobody is online

	Utils::LogC(Color(255, 83, 13, 200), "done");
	return 0;
}

// Called by Garry's Mod when this module is unloaded
GMOD_MODULE_CLOSE()
{
	return 0;
}