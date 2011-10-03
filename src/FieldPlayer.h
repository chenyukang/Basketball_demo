#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include <vector>
#include <string>
#include <cassert>
#include "Vec2D.h"
#include "PlayerBase.h"
#include "FieldPlayerStates.h"
#include "StateMachine.h"

class SteeringBehavior;
class BallTeam;
class Game;
class Goal;
struct Telegram;


class FieldPlayer : public PlayerBase
{
private:
    StateMachine<FieldPlayer>*           m_pStateMachine;  //the State Machine of this player
    
public:
    FieldPlayer(BallTeam*      home_team,
                State<FieldPlayer>* start_state,
                int            home_region, //the default area player stand
                Vector2D       heading,
                Vector2D       velocity,
                double         mass,
                double         max_force,
                double         max_speed,
                double         max_turn_rate,
                double         scale,
                player_role    role);   
  
    ~FieldPlayer();

    //call this to update the player's position and orientation
    void        Update();   
    void        Render();
    StateMachine<FieldPlayer>* GetFSM()const{return m_pStateMachine;}

};

#endif
