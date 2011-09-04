#ifndef PRECISION_TIMER_H
#define PRECISION_TIMER_H
#include "utils.h"
#include <sys/time.h>
#include <time.h>
#include <cassert>
#include <math.h>


#define TIMER Timer::Instance()

class Timer
{
private:
    timeval start_time;
    timeval prev_time;
    timeval now_time;
    float   real_time;
    float   elapsed_time;
    float   fps_timediff;
    float   fps_escapetime;
    bool    pause;

public:

    static Timer* Instance();
    //ctors
    Timer();
    
    //whatdayaknow, this starts the timer
    void Start();
    void Update();
    void Reset(double);
    //determines if enough time has passed to move onto next frame
    bool    ReadyForNextFrame();

    //only use this after a call to the above.
    //double  GetTimeElapsed(){return m_TimeElapsed;}
    double  TimeElapsed() const;
    double  RealTime() const;
    float   TimeDiff( struct timeval*, struct timeval*);
};
#endif
