#include "PlayerBase.h"
#include "BallTeam.h"
#include "Vec2D.h"
#include "SteeringBehavior.h"
#include "Game.h"

PlayerBase::PlayerBase(BallTeam* home_team,
                       Vector2D    pos,
                       player_role role):MovingEntity(pos,
                                                      Vector2D(0,0),
                                                      Vector2D(1,0),
                                                      Vector2D(1,1),
                                                      0.3,
                                                      0.5,
                                                      0.5,
                                                      0.5,
                                                      0.5),
                                         m_pTeam(home_team),
                                         m_PlayerRole(role)
{
    m_pSteering = new SteeringBehaviors(this, GetTeam()->GetGame()->GetBall());
}
    
PlayerBase::~PlayerBase()
{
    delete m_pSteering;
}
