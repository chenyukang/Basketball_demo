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
class BasketBall;
class SteeringBehaviors;
class Region;
class Regulator;

class PlayerBase : public MovingEntity,
                   public AutoList<PlayerBase>
{

public:
  
    enum player_role{PointGuard,ShootingGuard,SmallForward,
                     PowerForward,Center};

protected:
    player_role             m_PlayerRole;     //this player's role in the team
    BallTeam*               m_pTeam;          //pointer to this player's team
    SteeringBehaviors*      m_pSteering;      //pointer to the steering behaviors
    int                     m_iHomeRegion;    //the region that this player is assigned to.
    int                     m_iDefaultRegion; //the region this player moves to before kickoff
    double                  m_dDistSqToBall;  //distance to the ball, queried frequently
    Regulator*              m_regulator;      //this is used to regulator a player's time

public:
    PlayerBase(BallTeam*      home_team,
               int            home_region,
               Vector2D       pos,
               player_role    role);

    SteeringBehaviors* const  Steering() const{return m_pSteering;}
    BallTeam*   GetTeam()  const { return m_pTeam; }
    Game*       GetGame()  const ;
    void        SetHomeRegion(int region) { m_iHomeRegion = region; }
    BasketBall* Ball() const;
    bool        isClosestTeamMemberToBall() const;
    void        SetDistSqToBall(double val) { m_dDistSqToBall = val; }
    const Region* HomeRegion() const;
    bool        BallWithinControlRange() const;
    bool        AtTarget()const;
    void        TrackBall();
    bool        isAheadOfAttacker()const;
    bool        isControllingPlayer() const;
    void        setWaitTimeRegulator(double);
    bool        isRegulatorReady();
    virtual     ~PlayerBase();
};

#endif
