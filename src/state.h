
// @Name   : STATE_H 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-03 21:40:45
//
// @Brief  : the base definition of State, used by StateMchine.

#if !defined(STATE_H)
#define STATE_H


struct Telegram;

template <class obj_type>

class State{
public:
    virtual ~State() {};

    virtual void Enter(obj_type*)=0;
    virtual void Execute(obj_type*)=0;
    virtual void Exit(obj_type*)=0;
    virtual bool OnMessage(obj_type*, struct Telegram&)=0;
};
    

#endif

