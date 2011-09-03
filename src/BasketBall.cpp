#include "BasketBall.h"
//#include "geometry.h"
#include "Grapic.h"
#include "Region.h"
#include "Game.h"
#include <iostream>
//----------------------------- AddNoiseToKick --------------------------------
//
//  this can be used to vary the accuracy of a player's kick. Just call it 
//  prior to kicking the ball using the ball's position and the ball target as
//  parameters.
//-----------------------------------------------------------------------------
Vector2D AddNoiseToKick(Vector2D BallPos, Vector2D BallTarget)
{

}

  

//-------------------------- Kick ----------------------------------------
//                                                                        
//  applys a force to the ball in the direction of heading. Truncates
//  the new velocity to make sure it doesn't exceed the max allowable.
//------------------------------------------------------------------------
void BasketBall::Pass(Vector2D direction, double force)
{  
  //ensure direction is normalized
  direction.Normalize();
  
  //calculate the acceleration
  Vector2D acceleration = (direction * force) / m_dMass;

  //update the velocity
  m_vVelocity = acceleration;
}

//----------------------------- Update -----------------------------------
//
//  updates the ball physics, tests for any collisions and adjusts
//  the ball's velocity accordingly
//------------------------------------------------------------------------
void BasketBall::Update()
{
    m_vPosition += m_vVelocity;
    const Region *play_area=GAME->PlayingArea();
    if(m_vPosition.x>play_area->Right()||
       m_vPosition.x<play_area->Left())
        m_vVelocity.x=-m_vVelocity.x;
    if(m_vPosition.y<play_area->Bottom()||
       m_vPosition.y>play_area->Top())
        m_vVelocity.y=-m_vVelocity.y;
}

//---------------------- TimeToCoverDistance -----------------------------
//
//  Given a force and a distance to cover given by two vectors, this
//  method calculates how long it will take the ball to travel between
//  the two points
//------------------------------------------------------------------------
double BasketBall::TimeToCoverDistance(Vector2D A,
                                      Vector2D B,
                                      double force)const
{
}

//--------------------- FuturePosition -----------------------------------
//
//  given a time this method returns the ball position at that time in the
//  future
//------------------------------------------------------------------------
Vector2D BasketBall::FuturePosition(double time)const
{
  
}

//----------------------------- Render -----------------------------------
//
//  Renders the ball
//------------------------------------------------------------------------
void BasketBall::Render()
{
    gdi->SetPen(white);
    gdi->Circle(m_vPosition.x, m_vPosition.y, m_dBoundingRadius);

}


//----------------------- PlaceAtLocation -------------------------------------
//
//  positions the ball at the desired location and sets the ball's velocity to
//  zero
//-----------------------------------------------------------------------------
void BasketBall::PlaceAtPosition(Vector2D NewPos)
{
  m_vPosition = NewPos;
  m_vOldPos = m_vPosition;
  m_vVelocity.Zero();
}

void BasketBall::ChangePosition(Vector2D NewPos)
{
    m_vPosition=NewPos;
}

