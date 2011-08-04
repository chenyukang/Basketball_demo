#ifndef MOVING_ENTITY
#define MOVING_ENTITY
//------------------------------------------------------------------------
//
//  Name:   MovingEntity.h
//
//  Desc:   A base class defining an entity that moves. The entity has 
//          a local coordinate system and members for defining its
//          mass and velocity.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//          changed by Yukang Chen (moorekang@gmail.com)
//
//------------------------------------------------------------------------

#include <cassert>

#include "Vec2D.h"
#include "BaseGameEntity.h"
#include "Transformations.h"
#include <iostream>


class MovingEntity : public BaseGameEntity
{
public:
    MovingEntity(Vector2D position,
                 Vector2D velocity,
                 Vector2D heading,
                 Vector2D scale,
                 double   radius,
                 double   maxspeed,
                 double   mass,
                 double   turnrate,
                 double   maxforce):BaseGameEntity(BaseGameEntity::GetNextValidID()),
                                    m_vVelocity(velocity),
                                    m_vHeading(heading),
                                    m_dMaxSpeed(maxspeed),
                                    m_dMass(mass),
                                    m_vSide(m_vHeading.Perp()),
                                    m_dMaxTurnRate(turnrate),
                                    m_dMaxForce(maxforce)
        {
            m_vPosition = position;
            m_vSide = m_vHeading.Perp();
            m_dBoundingRadius = radius;
        }


    virtual ~MovingEntity(){}

    //accessors
    Vector2D  Velocity()const{return m_vVelocity;}
    void      SetVelocity(const Vector2D& NewVel){m_vVelocity = NewVel;}
  
    double    Mass()const{return m_dMass;}
  
    Vector2D  Side()const{return m_vSide;}

    double    MaxSpeed()const{return m_dMaxSpeed;}                       
    void      SetMaxSpeed(double new_speed){m_dMaxSpeed = new_speed;}
  
    double    MaxForce()const{return m_dMaxForce;}
    void      SetMaxForce(double mf){m_dMaxForce = mf;}

    bool      IsSpeedMaxedOut()const{return m_dMaxSpeed*m_dMaxSpeed >= m_vVelocity.LengthSq();}
    double    Speed()const{return m_vVelocity.Length();}
    double    SpeedSq()const{return m_vVelocity.LengthSq();}
  
    Vector2D  Heading()const{return m_vHeading;}
    void      SetHeading(Vector2D new_heading);
    bool      RotateHeadingToFacePosition(Vector2D target);

    double    MaxTurnRate()const{return m_dMaxTurnRate;}
    void      SetMaxTurnRate(double val){m_dMaxTurnRate = val;}
    
protected:
  
    Vector2D    m_vVelocity;
    Vector2D    m_vHeading; //heading direction
    Vector2D    m_vSide;   //a vector perpendicular to the heading vector
    double      m_dMass;  
    double      m_dMaxSpeed;     //the maximum speed this entity may travel at.
    double      m_dMaxForce; //the maxforce produced
    double      m_dMaxTurnRate; //the MaxTurnRate per second


};




/* @target : the target position will faceing to */
inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
    Vector2D toTarget = Vec2DNormalize(target - m_vPosition);

    double dot = m_vHeading.Dot(toTarget);

    Clamp(dot, -1, 1); //make sure dot is in range -1~1

    double angle = acos(dot);

    if (angle < 0.00001) return true;

    if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;
  
    C2DMatrix RotationMatrix;
  
    RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));	
    RotationMatrix.TransformVector2Ds(m_vHeading);
    RotationMatrix.TransformVector2Ds(m_vVelocity);

    //finally recreate m_vSide
    m_vSide = m_vHeading.Perp();

    return false;
}


/* @new_heading : the new Vector2D this should point to*/
inline void MovingEntity::SetHeading(Vector2D new_heading)
{
  assert( (new_heading.LengthSq() - 1.0) < 0.00001 &&
          "SetHeading new_heading can not be zero");
  
  m_vHeading = new_heading;

  m_vSide = m_vHeading.Perp();
}

#endif
