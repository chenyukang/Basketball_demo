#include "Grapic.h"
#include "Game.h"
#include "FieldPlayer.h"
#include "PlayerBase.h"
#include "BasketBall.h"
#include "BallTeam.h"
#include <limits>

using std::vector;

//------------------------------- dtor ---------------------------------------
//----------------------------------------------------------------------------
FieldPlayer::~FieldPlayer()
{

}

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
FieldPlayer::FieldPlayer(BallTeam* home_team,
                         int       home_region,
                         Vector2D  heading,
                         Vector2D  velocity,
                         double    mass,
                         double    max_force,
                         double    max_speed,
                         double    max_turn_rate,
                         double    scale,
                         player_role role):PlayerBase(home_team,
                                                      Vector2D(0,0),
                                                      role)                                    
{
    m_vVelocity.x = RandInRange(-0.5, 0.5);
    m_vVelocity.y = RandInRange(-0.5, 0.5);
}

void FieldPlayer::Update()
{ 
    //m_vVelocity.x+=RandInRange(-0.5,0.5);
    //m_vVelocity.y+=RandInRange(-0.5,0.5);
    m_vPosition += m_vVelocity;
    const Region *play_area=GAME->PlayingArea();
    if(m_vPosition.x>play_area->Right()||
       m_vPosition.x<play_area->Left())
        m_vVelocity.x=-m_vVelocity.x;
    if(m_vPosition.y<play_area->Bottom()||
       m_vPosition.y>play_area->Top())
    m_vVelocity.y=-m_vVelocity.y;
    
}

void FieldPlayer::Render()                                         
{
    gdi->SetColor(1.0f,0.4f,0.4f);
    gdi->Circle(m_vPosition.x, m_vPosition.y, m_dBoundingRadius);
}



