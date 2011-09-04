// @Name   : TEAMSTATE_H 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-04 15:51:19
//
// @Brief  :

#if !defined(TEAMSTATE_H)
#define TEAMSTATE_H

#include <string>

#include "State.h"
#include "Telegram.h"


class BallTeam;


//------------------------------------------------------------------------
class Attacking : public State<BallTeam>
{ 
private:
  
  Attacking(){}

public:

  //this is a singleton
  static Attacking* Instance();

  void Enter(BallTeam* team);

  void Execute(BallTeam* team);

  void Exit(BallTeam* team);

  bool OnMessage(BallTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class Defending : public State<BallTeam>
{ 
private:
  
  Defending(){}

public:

    //this is a singleton
  static Defending* Instance();

  void Enter(BallTeam* team);

  void Execute(BallTeam* team);

  void Exit(BallTeam* team);

  bool OnMessage(BallTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class PrepareForKickOff : public State<BallTeam>
{ 
private:
  
  PrepareForKickOff(){}

public:

    //this is a singleton
  static PrepareForKickOff* Instance();
  
  void Enter(BallTeam* team);

  void Execute(BallTeam* team);

  void Exit(BallTeam* team);

  bool OnMessage(BallTeam*, const Telegram&){return false;}
};
#endif

