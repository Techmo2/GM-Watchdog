/*
 Author - Bradly Tillmann (Techmo)
 Last Update - 6/30/18
 ---------------------------------

 This is the main code file for the watchdog timer class that contains the
 implementation of the code. The watchdog thread increments the timer every
 1000 microseconds (1 millisecond). If the timer's value makes it past
 1000 (1 second) before it it reset from the server thread, this indicates a 
 failure on the server thread. A mutex is used to prevent collisions when the
 timer's value is accessed from both threads.
 
 At the moment, the watchdog does nothing when a crash is detected. The action 
 taken has to be implemented based on the server's operation, and the desired 
 result.
*/

#include "watchdog.h"
#include "utils.h"

Watchdog::Watchdog(int timeout, const char* exec) {
	timer = 0;
	running = false;
	path = exec;
	this->timeout = timeout;
}

// The function that will be executed in a separate thread. It slowly increments the value
// of a counter and detects a crash if the counter is not reset by the server thread.
void Watchdog::WatchdogThread()
{
	boost::posix_time::microseconds interval(1000);

	while(running) {
		boost::this_thread::sleep(interval);

		// Lock variables in use by this thread to prevent collision with server thread.
		mtx.lock(); 

		if (timer >= timeout) {
			// Program has crashed, do shit here
			Utils::LogC(Color(255, 0, 0, 200), Utils::formstring("Watchdog exception, executing contigency batch file at \"", path, "\"").c_str());
			Utils::SystemCommand(Utils::formstring("start cmd.exe /c \"", path, "\"").c_str());
			exit(0);
		}
		else {
			timer++;
		}

		// Unlock variables, allow them to be used by the server thread.
		mtx.unlock(); 
	}
}

// Resets the watchdog timer
void Watchdog::KickDog()
{
	boost::mutex::scoped_lock lock(mtx);
	timer = 0;
}

// Enables the watchdog timer, and starts it in a new thread
void Watchdog::Start() {
	running = true;
	wthread = new boost::thread(&Watchdog::WatchdogThread, this);
}

