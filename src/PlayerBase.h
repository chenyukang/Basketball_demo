#ifndef PLAYER_BASE_H
#define PLAYER_BASE_H

#include <vector>
#include <string>
#include <cassert>
#include "autolist.h"
#include "Vec2D.h"
#include "MovingEntity.h"

class BallTeam;
class Game;
class BaseketBall;
class SteeringBehaviors;
class Region;

class PlayerBase : public MovingEntity,
                   public AutoList<PlayerBase>
{

public:
  
    enum player_role{PointGuard,ShootingGuard,SmallForward,
                     PowerForward,Center};

protected:
    player_role             m_PlayerRole;    //this player's role in the team
    BallTeam*               m_pTeam;    //a pointer to this player's team
    SteeringBehaviors*      m_pSteering;    //the steering behaviors
    int                     m_iHomeRegion;    //the region that this player is assigned to.
    int                     m_iDefaultRegion;    //the region this player moves to before kickoff

    //the distance to the ball (in squared-space). This value is queried 
    //a lot so it's calculated once each time-step and stored here.
    double                   m_dDistSqToBall;

public:


    PlayerBase(BallTeam*      home_team,
               Vector2D       pos,
               player_role    role);

    virtual ~PlayerBase();

};

#endif
