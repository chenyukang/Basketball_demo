#ifndef SOCCERBALL_H
#define SOCCERBALL_H
#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name: SoccerBall.h
//
//  Desc: Class to implement a Baketball. This class inherits from
//        MovingEntity and provides further functionality for collision
//        testing and position prediction.
//
//  Author: Yukang Chen(moorekang@gmail.com)
//
//------------------------------------------------------------------------
#include <vector>
#include "MovingEntity.h"
#include "constants.h"
#include "Wall2D.h"

class PlayerBase;
class Goal;
typedef enum {
    inUndefined,
    inControl,
    inAir,
    inGround,
    inPrepareBegin,
    inPassing,
}BallState;
    
class BasketBall : public MovingEntity
{
private:

    //keeps a record of the ball's position at the last update
    Vector2D                  m_vOldPos;
    std::vector<Wall2D>&      m_CourtBoundary;
    PlayerBase*               m_pControllingPlayer;
    BallState                 m_state;
    Goal*                     m_pGoal;

public:

    BasketBall(Vector2D             pos,            
               double               BallSize,
               double               mass,
               std::vector<Wall2D>&       walls)
        //set up the base class
        :MovingEntity(pos,
                      Vector2D(0.05,0.0),     
                      Vector2D(0,1),
                      Vector2D(1.0,1.0),  //scale     - unused
                      BallSize,
                      0.2,                //max speed - unused
                      mass,
                      0,                   //turn rate - unused
                      0),                  //max force - unused
         m_CourtBoundary(walls),
         m_pControllingPlayer(NULL),
         m_state(inGround)
        {}
  
    //implement base class Update
    void      Update();

    //implement base class Render
    void      Render();

    //a soccer ball doesn't need to handle messages
    bool      HandleMessage(const Telegram& msg){return false;}

    //this method applies a directional force to the ball (kicks it!)
    void      Pass(Vector2D direction, double force);
    void      Kick(Vector2D direction, double force);
    void      Shot(Vector2D direction, double force, Goal* goal);
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
    void      TestCollisionWithWalls(const std::vector<Wall2D>& walls);
    void      SetControllingPlayer(PlayerBase* player);
    PlayerBase* GetControlPlayer() const { return m_pControllingPlayer;}
    void      SetUnControl() { m_pControllingPlayer=NULL; if(m_state!=inAir) m_state = inGround;}
    bool      isCanControl() { if (m_state == inAir) {return false;}
                                return m_state != inControl && m_pControllingPlayer == NULL;}
    bool      TestGetGoal();

};

//this can be used to vary the accuracy of a player's kick.
Vector2D AddNoiseToShot(Vector2D BallPos, Vector2D BallTarget);

#endif
