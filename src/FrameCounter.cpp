
// @Name   : FrameCounter.cpp 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-03 22:33:14
//
// @Brief  :

#include "FrameCounter.h"


FrameCounter* FrameCounter::Instance()
{
  static FrameCounter instance;

  return &instance;
}
