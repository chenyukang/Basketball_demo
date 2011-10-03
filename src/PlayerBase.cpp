#include "PlayerBase.h"
#include "BallTeam.h"
#include "BasketBall.h"
#include "Vec2D.h"
#include "SteeringBehavior.h"
#include "Game.h"
#include "Goal.h"
#include "Regulator.h"

PlayerBase::PlayerBase(BallTeam* home_team,
                       int       home_region,
                       Vector2D    pos,
                       player_role role):MovingEntity(pos,
                                                      Vector2D(0,0),
                                                      Vector2D(1,0),
                                                      Vector2D(1,1),
                                                      0.3,
                                                      0.2,
                                                      0.5,
                                                      0.5,
                                                      0.2),
                                         m_pTeam(home_team),
                                         m_iHomeRegion(home_region),
                                         m_PlayerRole(role),
                                         m_regulator(NULL)
{
    m_pSteering = new SteeringBehaviors(this, GetTeam()->GetGame()->GetBall());
    m_pSteering->SeparationOn();
}
    
PlayerBase::~PlayerBase()
{
    delete m_pSteering;
    if(m_regulator)
        delete m_regulator;
}

BasketBall* PlayerBase::Ball() const
{
    return GetTeam()->GetGame()->GetBall();
}

bool PlayerBase::isClosestTeamMemberToBall() const
{
    return GetTeam()->PlayerClosestToBall() == this;
}

Game* PlayerBase::GetGame() const
{
    return m_pTeam->GetGame();
}

const Region* PlayerBase::HomeRegion() const
{
    return GetGame()->GetRegionFromIndex(m_iHomeRegion);
}

bool PlayerBase::BallWithinControlRange() const
{
  return (Vec2DDistanceSq(this->Ball()->Pos(), Pos()) < 0.5);
}

bool PlayerBase::AtTarget() const
{
    return (Vec2DDistanceSq(Pos(), Steering()->Target()) < 3.0);
}

void PlayerBase::TrackBall()
{
  RotateHeadingToFacePosition(Ball()->Pos());  
}

bool PlayerBase::isAheadOfAttacker() const
{
  return fabs(Pos().x - GetTeam()->OpponentsGoal()->Center().x) <
         fabs(GetTeam()->ControllingPlayer()->Pos().x - GetTeam()->OpponentsGoal()->Center().x);
}

bool PlayerBase::isControllingPlayer() const
{
    return GetTeam()->ControllingPlayer()==this;
}


void PlayerBase::setWaitTimeRegulator(double periodTime)
{
    if(m_regulator!=NULL)
        delete m_regulator;
    m_regulator = new Regulator(periodTime);
}

bool PlayerBase::isRegulatorReady()
{
    return m_regulator->isReady();
}
