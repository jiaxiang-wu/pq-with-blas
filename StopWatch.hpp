/*
  File Name: StopWatch.hpp
  Author: Jiaxiang Wu
  E-mail: jiaxiang.wu.90@gmail.com
  Created Time: Thu 28 Jan 2016 04:15:21 PM CST
 */

#ifndef STOPWATCH_HPP_INCLUDED
#define STOPWATCH_HPP_INCLUDED

#include <ctime>

class StopWatch {
public:
  // start timing
  void Start(void);
  // pause timing
  void Pause(void);
  // resume timing
  void Resume(void);
  // stop timing and return the elapsed time (in second)
  float Stop(void);

private:
  // indicator for whether the stop-watch is on
  bool isRun;
  // timestamp when the stop-watch starts
  time_t timeBeg;
  // timestamp when the stop-watch ends
  time_t timeEnd;
  // the elapsed time (in second)
  float timeElps;
};

// Following are the implementations of the <StopWatch> class

inline void StopWatch::Start(void) {
  isRun = true;
  timeBeg = clock();
  timeElps = 0.0;
}

inline void StopWatch::Pause(void) {
  if (isRun) {
    isRun = false;
    timeEnd = clock();
    timeElps += static_cast<float>(timeEnd - timeBeg) / CLOCKS_PER_SEC;
  } // ENDIF: isRun
}

inline void StopWatch::Resume(void) {
  if (!isRun) {
    isRun = true;
    timeBeg = clock();
  } // ENDIF: isRun
}

inline float StopWatch::Stop(void) {
  Pause(); // this does the main job
  return timeElps;
}

#endif // STOPWATCH_HPP_INCLUDED

