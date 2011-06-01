#ifndef SOCCERBALL_H
#define SOCCERBALL_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name: SoccerBall.h
//
//  Desc: Class to implement a soccer ball. This class inherits from
//        MovingEntity and provides further functionality for collision
//        testing and position prediction.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <vector>

#include "MovingEntity.h"
#include "constants.h"


class PlayerBase;

class BasketBall : public MovingEntity
{
private:

    //keeps a record of the ball's position at the last update
    Vector2D                  m_vOldPos;

public:

    BasketBall(Vector2D             pos,            
               double               BallSize,
               double               mass)
        //set up the base class
        :MovingEntity(pos,
                      BallSize,
                      Vector2D(0.05,0.0),     
                      -1.0,                //max speed - unused
                      Vector2D(0,1),
                      mass,
                      Vector2D(1.0,1.0),  //scale     - unused
                      0,                   //turn rate - unused
                      0)                  //max force - unused
        {}
  
    //implement base class Update
    void      Update();

    //implement base class Render
    void      Render();

    //a soccer ball doesn't need to handle messages
    bool      HandleMessage(const Telegram& msg){return false;}

    //this method applies a directional force to the ball (kicks it!)
    void      Pass(Vector2D direction, double force);

    //given a kicking force and a distance to traverse defined by start
    //and finish points, this method calculates how long it will take the
    //ball to cover the distance.
    double    TimeToCoverDistance(Vector2D from,
                                  Vector2D to,
                                  double     force)const;

    //this method calculates where the ball will in 'time' seconds
    Vector2D FuturePosition(double time)const;

    //this is used by players and goalkeepers to 'trap' a ball -- to stop
    //it dead. That player is then assumed to be in possession of the ball
    //and m_pOwner is adjusted accordingly
    void      Trap(){m_vVelocity.Zero();}  

    Vector2D  OldPos()const{return m_vOldPos;}
  
    //this places the ball at the desired location and sets its velocity to zero
    void      PlaceAtPosition(Vector2D NewPos);
    void      ChangePosition(Vector2D NewPos);
};



//this can be used to vary the accuracy of a player's kick.
Vector2D AddNoiseToKick(Vector2D BallPos, Vector2D BallTarget);



#endif
