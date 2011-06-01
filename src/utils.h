#ifndef UTILS_H
#define UTILS_H
/**
 * @file   utils.h
 * @author moorekang <moorekang@gmail.com>
 * @date   Sun Jul 18 14:31:12 2010
 * 
 * @brief  一些实用的函数 和 常用的变量定义
 * 
 * 
 */
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cassert>
#include <iomanip>
#include <stdio.h>

#define max(x, y) ((x) > (y)? (x) : (y))
#define min(x, y) ((x) < (y)? (x) : (y))
#define PI    3.1415926
#define abs(x)    (((x)<(0))? (-(x)): (x))
//a few useful constants
const int     MaxInt    = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

//returns true if the value is a NaN
template <typename T>
inline bool isNaN(T val)
{
    return val != val;
}

inline double DegsToRads(double degs)
{
    return TwoPi * (degs/360.0);
}



//returns true if the parameter is equal to zero
inline bool IsZero(double val)
{
    return ( (-MinDouble < val) && (val < MinDouble) );
}

//returns true is the third parameter is in the range described by the
//first two
inline bool InRange(double start, double end, double val)
{
    if (start < end)
    {
        if ( (val > start) && (val < end) ) return true;
        else return false;
    }

    else
    {
        if ( (val < start) && (val > end) ) return true;
        else return false;
    }
}

template <class T>
T Maximum(const T& v1, const T& v2)
{
    return v1 > v2 ? v1 : v2;
}



//----------------------------------------------------------------------------
//  some random number functions.
//----------------------------------------------------------------------------

//returns a random integer between x and y
inline int   RandInt(int x,int y)
{
    assert(y>=x && "<RandInt>: y is less than x");
    return rand()%(y-x+1)+x;
}

//returns a random double between zero and 1
inline double RandFloat()      {return ((rand())/(RAND_MAX+1.0));}

inline double RandInRange(double x, double y)
{
    return x + RandFloat()*(y-x);
}

//returns a random bool
inline bool   RandBool()
{
    if (RandFloat() > 0.5) return true;

    else return false;
}

//returns a random double in the range -1 < n < 1
inline double RandomClamped()    {return RandFloat() - RandFloat();}


//returns a random number with a normal distribution. See method at
//http://www.taygeta.com/random/gaussian.html
inline double RandGaussian(double mean = 0.0, double standard_deviation = 1.0)
{				        
    double x1, x2, w, y1;
    static double y2;
    static int use_last = 0;

    if (use_last)		        /* use value from previous call */
    {
        y1 = y2;
        use_last = 0;
    }
    else
    {
        do 
        {
            x1 = 2.0 * RandFloat() - 1.0;
            x2 = 2.0 * RandFloat() - 1.0;
            w = x1 * x1 + x2 * x2;
        }
        while ( w >= 1.0 );

        w = sqrt( (-2.0 * log( w ) ) / w );
        y1 = x1 * w;
        y2 = x2 * w;
        use_last = 1;
    }

    return( mean + y1 * standard_deviation );
}



//-----------------------------------------------------------------------
//  
//  some handy little functions
//-----------------------------------------------------------------------


inline double Sigmoid(double input, double response = 1.0)
{
    return ( 1.0 / ( 1.0 + exp(-input / response)));
}


//returns the maximum of two values
template <class T>
inline T MaxOf(const T& a, const T& b)
{
    if (a>b) return a; return b;
}

//returns the minimum of two values
template <class T>
inline T MinOf(const T& a, const T& b)
{
    if (a<b) return a; return b;
}


//clamps the first argument between the second two
template <class T, class U, class V>
inline void Clamp(T& arg, const U& minVal, const V& maxVal)
{
    assert ( ((double)minVal < (double)maxVal) && "<Clamp>MaxVal < MinVal!");

    if (arg < (T)minVal)
    {
        arg = (T)minVal;
    }

    if (arg > (T)maxVal)
    {
        arg = (T)maxVal;
    }
}


//rounds a double up or down depending on its value
inline int Rounded(double val)
{
    int    integral = (int)val;
    double mantissa = val - integral;

    if (mantissa < 0.5)
        return integral;
    else
        return integral + 1;
}

//rounds a double up or down depending on whether its 
//mantissa is higher or lower than offset
inline int RoundUnderOffset(double val, double offset)
{
    int    integral = (int)val;
    double mantissa = val - integral;

    if (mantissa < offset)
    {
        return integral;
    }

    else
    {
        return integral + 1;
    }
}

//compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
    if (fabs(a-b) < 1E-12)
    {
        return true;
    }

    return false;
}

inline bool isEqual(double a, double b)
{
    if (fabs(a-b) < 1E-12)
    {
        return true;
    }

    return false;
}


template <class T>
inline double Average(const std::vector<T>& v)
{
    double average = 0.0;
  
    for (unsigned int i=0; i < v.size(); ++i)
    {    
        average += (double)v[i];
    }

    return average / (double)v.size();
}


inline double StandardDeviation(const std::vector<double>& v)
{
    double sd      = 0.0;
    double average = Average(v);

    for (unsigned int i=0; i<v.size(); ++i)
    {     
        sd += (v[i] - average) * (v[i] - average);
    }

    sd = sd / v.size();

    return sqrt(sd);
}
#endif

