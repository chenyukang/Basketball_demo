#include "BasketBall.h"
#include "Grapic.h"
#include "Region.h"
#include "Game.h"
#include "geometry.h"
#include "PlayerBase.h"
#include "Goal.h"
#include <iostream>


Vector2D AddNoiseToShot(Vector2D BallPos, Vector2D BallTarget)
{
    double displacement = (Pi*0.1) * RandomClamped();
    Vector2D toTarget = BallTarget - BallPos;
    Vec2DRotateAroundOrigin(toTarget, displacement);
    return toTarget + BallPos;
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

    if(m_state == inControl && m_pControllingPlayer!=NULL){
        this->PlaceAtPosition(m_pControllingPlayer->Pos());
        return;
    }
    
    
    //keep a record of the old position so the goal::scored method
    //can utilize it for goal testing
    m_vOldPos = m_vPosition;

    //Test for collision
    TestCollisionWithWalls(m_CourtBoundary);

    m_vHeading = Vec2DNormalize(m_vVelocity);
    //Simulate Prm.Friction. Make sure the speed is positive 
    //first though
    if ( m_state != inAir && m_state != inPassing &&
         m_vVelocity.LengthSq() > 0.03*0.03 )
    {
        m_vVelocity = 0.1*m_vHeading;
    }
    if ( m_state == inAir && m_vVelocity.LengthSq() > 0.05*0.05 )
    {
        m_vVelocity = 0.3*m_vHeading;
    }
    
    if ( m_state == inPassing )
    {
        m_vVelocity = 0.3*m_vHeading;
    }
    
    if(m_state == inAir)
        TestGetGoal();
    m_vPosition += m_vVelocity;
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

//-------------------------- Kick ----------------------------------------
//                                                                        
//  applys a force to the ball in the direction of heading. Truncates
//  the new velocity to make sure it doesn't exceed the max allowable.
//------------------------------------------------------------------------
void BasketBall::Kick(Vector2D direction, double force)
{
    m_pControllingPlayer = NULL;
    m_state = inPassing;

    //ensure direction is normalized
    direction.Normalize();
  
    //calculate the acceleration
    Vector2D acceleration = (direction * force) / m_dMass;

    //update the velocity
    m_vVelocity = acceleration;
}

void BasketBall::Shot(Vector2D direction, double force, Goal* goal)
{
    m_pControllingPlayer = NULL;
    m_state = inAir;
    //ensure direction is normalized
    direction.Normalize();
  
    //calculate the acceleration
    Vector2D acceleration = (direction * force) / m_dMass;

    //update the velocity
    m_vVelocity = acceleration;
    m_pGoal = goal;
    //getchar();
    //测试一下
}

void BasketBall::TestCollisionWithWalls(const std::vector<Wall2D>& walls)
{

  int idxClosest = -1;
  Vector2D VelNormal = Vec2DNormalize(m_vVelocity);
  Vector2D IntersectionPoint, CollisionPoint;
  double DistToIntersection = MaxFloat;


  for (unsigned int w=0; w<walls.size(); ++w)
  {
    Vector2D ThisCollisionPoint = Pos() - (walls[w].Normal() * BRadius());

    if (WhereIsPoint(ThisCollisionPoint,
                     walls[w].From(),
                     walls[w].Normal()) == plane_backside)
    {
      double DistToWall = DistanceToRayPlaneIntersection(ThisCollisionPoint,
                                                         walls[w].Normal(),
                                                         walls[w].From(),
                                                         walls[w].Normal());

      IntersectionPoint = ThisCollisionPoint + (DistToWall * walls[w].Normal());
      
    }

    else
    {
      double DistToWall = DistanceToRayPlaneIntersection(ThisCollisionPoint,
                                                         VelNormal,
                                                         walls[w].From(),
                                                         walls[w].Normal());

      IntersectionPoint = ThisCollisionPoint + (DistToWall * VelNormal);
    }
    
    //check to make sure the intersection point is actually on the line
    //segment
    bool OnLineSegment = false;

    if (LineIntersection2D(walls[w].From(), 
                           walls[w].To(),
                           ThisCollisionPoint - walls[w].Normal()*20.0,
                           ThisCollisionPoint + walls[w].Normal()*20.0))
    {

      OnLineSegment = true;                                               
    }

  
    //Note, there is no test for collision with the end of a line segment
    //now check to see if the collision point is within range of the
    //velocity vector. [work in distance squared to avoid sqrt] and if it
    //is the closest hit found so far. 

    //If it is that means the ball will collide with the wall sometime
    //between this time step and the next one.
    double distSq = Vec2DDistanceSq(ThisCollisionPoint, IntersectionPoint);

    if ((distSq <= m_vVelocity.LengthSq()) && (distSq < DistToIntersection) && OnLineSegment)            
    {        
      DistToIntersection = distSq;
      idxClosest = w;
      CollisionPoint = IntersectionPoint;
    }     
  }//next wall

    
  //to prevent having to calculate the exact time of collision we
  //can just check if the velocity is opposite to the wall normal
  //before reflecting it. This prevents the case where there is overshoot
  //and the ball gets reflected back over the line before it has completely
  //reentered the playing area.
  if ( (idxClosest >= 0 ) && VelNormal.Dot(walls[idxClosest].Normal()) < 0)
  {
    m_vVelocity.Reflect(walls[idxClosest].Normal());   
  }
}

void BasketBall::SetControllingPlayer(PlayerBase* player)
{
    m_pControllingPlayer = player;
    m_state = inControl;
    printf("player: %d get ball control\n", player->ID());
}


bool BasketBall::TestGetGoal()
{
    bool res = m_pGoal->Scored(m_vPosition);
    if( res )
    {
        m_vVelocity=Vector2D(0,0);
        m_state = inGround;
    }
    else
    {
        double x = m_pGoal->Center().x;
        if((m_vPosition.x>x && m_vVelocity.x>0) ||
           (m_vPosition.x<x && m_vVelocity.x<0))
        {
            m_state = inGround;
            m_vVelocity.x = -m_vVelocity.x;
        }
    }
}


