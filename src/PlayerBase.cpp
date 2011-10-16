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
                       double    maxSpeed,
                       Vector2D    pos,
                       player_role role):MovingEntity(pos,
                                                      Vector2D(0,0),
                                                      Vector2D(1,0),
                                                      Vector2D(1,1),
                                                      0.3,
                                                      maxSpeed,
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


bool PlayerBase::BallWithinReceivingRange() const
{
    return (Vec2DDistanceSq(Pos(), Ball()->Pos()) < 0.3);
}

bool PlayerBase::InHomeRegion() const
{
    return GetGame()->GetRegionFromIndex(m_iHomeRegion)->Inside(Pos(), Region::normal);
}

bool PlayerBase::BallWithinPassRange() const
{
    return true;
}
bool PlayerBase::BallWithinControlRange() const
{
    double dist = Vec2DDistanceSq(this->Ball()->Pos(), Pos());
    return (Vec2DDistanceSq(this->Ball()->Pos(), Pos()) < 0.4);
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
    Vector2D target = Vector2D(GetTeam()->OpponentsGoal()->Center().x,
                               GetTeam()->OpponentsGoal()->Center().y);
    double dist_a = target.Distance(Pos());
    double dist_b = target.Distance(GetTeam()->ControllingPlayer()->Pos());
    return dist_a < dist_b;
    
//  return fabs(Pos().y - GetTeam()->OpponentsGoal()->Center().y) <
//         fabs(GetTeam()->ControllingPlayer()->Pos().y - GetTeam()->OpponentsGoal()->Center().y);
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
    if(m_regulator == NULL)
        return true;
    return m_regulator->isReady();
}


double PlayerBase::getRegulatorTime() const
{
    assert(m_regulator!=NULL && "regulator is null");
    return m_regulator->getElapseTime();
}
    
