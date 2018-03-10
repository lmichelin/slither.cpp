/*
 * TimeModule class for the server
 * Handles time for example disconnection times and speeds of the snakes
*/

#ifndef TIME_MODULE
#define TIME_MODULE

#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

class TimeModule {
	public:

		//////////////////
		// Main Methods //
		//////////////////

		// Update elapsed time by getting the difference between new time and registered time
		void updateElapsedTime() {
			if (!_started) {
				_started = true;
				_registered_time = Time::now();
			}
		
			fsec fs = Time::now() - _registered_time;
			_elapsed_time += std::chrono::duration_cast<ms>(fs);
			_registered_time = Time::now();
		}

		// Reset elapsed time to zero
		void reset() {
			_elapsed_time = std::chrono::milliseconds::zero();
		}

		// Stop and reset
		void stopAndReset() {
			_started = false;
			reset();
		}

		/////////////
		// Getters //
		/////////////
		
		// Get elapsed time
		ms getElapsedTime() {
			return _elapsed_time;
		}

		/////////////////
		// Constructor //
		/////////////////

		// Initialize all times to zero milliseconds
		TimeModule() : _started(false), _elapsed_time(std::chrono::milliseconds::zero()) {}
		~TimeModule() {}


	private:

		// Started status
		bool _started;

		// Time register to know last time measure
		Time::time_point _registered_time; 

		// Elapsed time register
		ms _elapsed_time;

};

#endif
