/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 ---------------------------------

 This is the header file for my gmod utility collection.
 See the implementation (utils.cpp) for more information.
*/

#ifndef UTILS_h
#define UTILS_h

#include "cbase.h"
#include "icvar.h"
#include "Color.h"
#include "iserverplugin.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "module.h"
#include <Windows.h>
#include <GarrysMod\Lua\Interface.h>
//#include "public/cdll_int.h"
#include "eifaceV21.h"

// Easy way to load interfaces should we need to
#define LOADINTERFACE(_module_, _version_, _out_) Sys_LoadInterface(_module_, _version_, NULL, reinterpret_cast<void**>(& _out_))

namespace Utils {
	void init();

	void PrintC(const char* msg, ...);
	void PrintC(Color& c, const char* msg, ...);
	void LogC(const char* msg, ...);
	void LogC(Color& c, const char* msg, ...);
	void PrintVersion();

	template<typename T>
	std::string formstring(T t);

	template<typename T, typename... Others>
	std::string formstring(T t, Others... others);

	void RunCommand(const char* cmd, ...);
	
}

#endif UTILS_h