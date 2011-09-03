
// @Name   : MESSAGES_H 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-08-20 18:11:57
//
// @Brief  : the message def in all Game

#if !defined(MESSAGES_H)
#define MESSAGES_H


#include <string>
enum MsgType{
    Msg_ReceiveBall,
    Msg_GiveMeBall,
    Msg_SupportAttack,
    Msg_GoDefensePos,
    Msg_GoOffensePos,
    Msg_ChaseBall,
    Msg_ShotBall
};

inline std::string MsgToStr(int msgType);
    
#endif
