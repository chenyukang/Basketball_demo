
// @Name   : REGULATOR_H 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-04 21:56:19
//
// @Brief  : this is defination of Regulator,
//         : be used by those requested more time distance computations

#if !defined(REGULATOR_H)
#define REGULATOR_H

#include "PrecisionTimer.h"

class Regulator
{
private:
    double  m_UpdatePeriod; //the time diff requested
    double  m_ElapseTime; //the time have elapsed
    timeval prevTime;
    
public:
    //@ countPerSecond: counts in one seconds
    Regulator(int countPerSecond)
        {
            assert(countPerSecond > 0 && "countPerSecond>0");
            m_ElapseTime = 0.0;
            gettimeofday(&prevTime, NULL);
            if (countPerSecond > 0){
                m_UpdatePeriod = 1000.0 / countPerSecond;
            }
            else if (isEqual(0.0, countPerSecond)){
                m_UpdatePeriod = 0.0;
            }
        }

    Regulator(double periodTime)//in seconds
        {
            assert(periodTime>0 && "periodTime must larger than 0");
            m_ElapseTime = 0.0;
            gettimeofday(&prevTime, NULL);
            m_UpdatePeriod = 1000.0*periodTime;
            
        }

    //return true iff elapsed time is more than m_dUpdatePeriod
    //reset elapsed time to zero
    bool isReady()
        {
            if( m_ElapseTime > m_UpdatePeriod ){
                m_ElapseTime = 0;
                return true;
            }

            timeval nowTime;
            gettimeofday(&nowTime, NULL);
            m_ElapseTime += TIMER->TimeDiff(&prevTime, &nowTime);
            //prevTime = nowTime;
            gettimeofday(&prevTime, NULL);
            return false;
        }
};


#endif

