#include "Grapic.h"
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
}

void FieldPlayer::Update()
{ 
    //printf("now FieldPlayer Update\n");

    
}

void FieldPlayer::Render()                                         
{
        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_POINTS);
        
        glVertex2f(rand()%(10),rand()%(10));
        glEnd();
}



