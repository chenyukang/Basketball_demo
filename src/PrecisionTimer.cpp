#include "PrecisionTimer.h"
#include <iostream>
#include <math.h>
using namespace std;

//singleton instance 
Timer* Timer::Instance()
{
  static Timer instance; 
  return &instance;
}

//fps_cnt: the frame count every 1 second
void Timer::Reset(double fps_cnt)
{
    printf("Reset Timer:%.3f Frames per second\n",fps_cnt);
    fps_timediff = (1000.0/fps_cnt);
    real_time = 0.0;
    elapsed_time = 0.0;
    fps_escapetime = 0.0;
    pause = false;
    gettimeofday(&now_time, NULL);
    start_time=prev_time=now_time;
}
    
Timer::Timer()
{
    real_time = 0.0;
    elapsed_time = 0.0;
    fps_escapetime = 0.0;
    pause = false;
}

float Timer::TimeDiff(struct timeval* tv1, struct timeval* tv2)
{
    return abs((tv1->tv_sec*1000.0 + tv1->tv_usec/1000.0) -
               (tv2->tv_sec*1000.0 + tv2->tv_usec/1000.0));
}

bool Timer::ReadyForNextFrame()
{
    if(fps_escapetime > fps_timediff)
    {
        real_time+=(fps_timediff/1000);
        fps_escapetime = 0.0;
        return true;
    }
    return false;
}

//--------------------------- TimeElapsed --------------------------------
//
//  returns time elapsed since last call to this function.
//-------------------------------------------------------------------------
double Timer::TimeElapsed() const
{
    return elapsed_time/1000;
}

double Timer::RealTime() const
{
    return real_time;
}

void Timer::Update()
{
    gettimeofday(&now_time, NULL);
    elapsed_time = TimeDiff(&now_time, &prev_time);
    prev_time = now_time;
    if(pause)
        elapsed_time = 0;
//    real_time = timeval_diff(&now_time,&start_time)/1000;
    fps_escapetime += elapsed_time;
}
