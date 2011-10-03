
// @Name   : FIELDPLAYERSTATES_H 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-17 23:06:47
//
// @Brief  :

#if !defined(FIELDPLAYERSTATES_H)
#define FIELDPLAYERSTATES_H

#include "State.h"
#include "Telegram.h"
#include <string.h>

using namespace std;

class FieldPlayer;
class BaskeBall;

class GlobalPlayerState : public State<FieldPlayer>
{
private: //this is singleton instance
    GlobalPlayerState() {}
    
public:
    static GlobalPlayerState* Instance();
    void   Enter(FieldPlayer* player) {} //do nothing
    void   Execute(FieldPlayer* player);
    void   Exit(FieldPlayer* player) {} //do nothing
    bool   OnMessage(FieldPlayer* player, const Telegram& msg);
};

class ChaseBall : public State<FieldPlayer>
{
private:
    ChaseBall(){}  //this is a singleton

public:
    static ChaseBall* Instance();
    void Enter(FieldPlayer* player);
    void Execute(FieldPlayer* player);
    void Exit(FieldPlayer* player);
    bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class ReturnToHomeRegion: public State<FieldPlayer>
{
private:
  ReturnToHomeRegion(){}

public:

  //this is a singleton
  static ReturnToHomeRegion* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class ControlBall: public State<FieldPlayer>
{
private:
  ControlBall(){}

public:

  //this is a singleton
  static ControlBall* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class Wait: public State<FieldPlayer>
{
private:
  Wait(){}

public:

  //this is a singleton
  static Wait* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class Dummpy: public State<FieldPlayer>
{
private:
    Dummpy() {}

public:
    static Dummpy* Instance();
    void Enter(FieldPlayer* player);
    void Execute(FieldPlayer* player);
    void Exit(FieldPlayer* player);
    bool OnMessage(FieldPlayer*, const Telegram&) { return false;}
};

/*
//------------------------------------------------------------------------
class Dribble : public State<FieldPlayer>
{
private:
  
  Dribble(){}

public:

  //this is a singleton
  static Dribble* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player){}
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class ReturnToHomeRegion: public State<FieldPlayer>
{
private:
  ReturnToHomeRegion(){}

public:

  //this is a singleton
  static ReturnToHomeRegion* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class Wait: public State<FieldPlayer>
{
private:
  
  Wait(){}

public:

  //this is a singleton
  static Wait* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class KickBall: public State<FieldPlayer>
{
private:
  
  KickBall(){}

public:

  //this is a singleton
  static KickBall* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player){}
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class ReceiveBall: public State<FieldPlayer>
{
private:
  
  ReceiveBall(){}

public:

  //this is a singleton
  static ReceiveBall* Instance();
  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


//------------------------------------------------------------------------
class SupportAttacker: public State<FieldPlayer>
{
private:
  
  SupportAttacker(){}

public:

  //this is a singleton
  static SupportAttacker* Instance();

  void Enter(FieldPlayer* player);
  void Execute(FieldPlayer* player);
  void Exit(FieldPlayer* player);
  bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
*/
#endif

