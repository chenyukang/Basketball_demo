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
    BallTeam*               m_pTeam;         //pointer to this player's team
    SteeringBehaviors*      m_pSteering;     //pointer to the steering behaviors
    int                     m_iHomeRegion;    //the region that this player is assigned to.
    int                     m_iDefaultRegion; //the region this player moves to before kickoff
    double                  m_dDistSqToBall; //distance to the ball, queried frequently

public:


    PlayerBase(BallTeam*      home_team,
               Vector2D       pos,
               player_role    role);

    virtual ~PlayerBase();

};

#endif
