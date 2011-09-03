// @Name   : Messages.cpp 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @date   : 2011-08-20 18:17:38
//
// @Brief  : 

#include "Messages.h"

inline std::string MsgToStr(int msgType)
{
    switch(msgType)
    {
    case Msg_ReceiveBall:
        return "Msg_ReceiveBall";
    case Msg_GiveMeBall:
        return "Msg_GiveMeBall";
    case Msg_SupportAttack:
        return "Msg_SupportAttack";
    case Msg_GoDefensePos:
        return "Msg_GoDefensePos";
    case Msg_GoOffensePos:
        return "Msg_GoOffensePos";
    case Msg_ChaseBall:
        return "Msg_ChaseBall";
    case Msg_ShotBall:
        return "Msg_ShotBall";
    default:
        return "Msg_error";
    }
}
