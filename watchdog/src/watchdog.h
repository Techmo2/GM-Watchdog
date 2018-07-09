/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 ---------------------------------
 
 This is the header file for the watchdog timer class.
 See the implementation (watchdog.cpp) for more information.
*/

#ifndef WATCHDOG_h
#define WATCHDOG_h

#include <iostream>
#include <boost\thread.hpp>
#include <boost\date_time.hpp>

class Watchdog {
private:
	boost::mutex mtx;
	long timer;
	int timeout;
	bool running;
	const char* path;
	boost::thread* wthread;

	void WatchdogThread();
public:
	Watchdog(int timeout, const char* exec);
	void KickDog();
	void Start();
};

#endif WATCHDOG_h