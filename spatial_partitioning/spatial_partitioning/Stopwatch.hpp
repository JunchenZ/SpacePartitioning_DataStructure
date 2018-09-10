#pragma once
#include <chrono>


/*
  Simple timing class.  Gives the number of seconds as a double

Stopwatch sw;

sw.start();
doTheThing();
double elapsedSeconds = sw.stop();

The stopwatch keeps running.  Call start() again to reset it.

 */

class Stopwatch{

public:

  void start(){
	startTime = std::chrono::high_resolution_clock::now();
  }

  double stop(){
	return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
  }
private:
  
  std::chrono::high_resolution_clock::time_point startTime;
};
