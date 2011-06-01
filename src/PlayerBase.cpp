#include "PlayerBase.h"
#include "Vec2D.h"

PlayerBase::PlayerBase(BallTeam* home_team,
                       Vector2D    pos,
                       player_role role):MovingEntity(pos,
                                                      0.3,
                                                      Vector2D(0,0),
                                                      0.5,
                                                      Vector2D(1,0),
                                                      0.5,
                                                      Vector2D(1,1),
                                                      0.5,
                                                      0.5)
{
    
}
    
PlayerBase::~PlayerBase()
{
    
}
