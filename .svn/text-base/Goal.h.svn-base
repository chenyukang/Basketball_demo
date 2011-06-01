#ifndef GOAL_H
#define GOAL_H
//------------------------------------------------------------------------
//
//Name:   Goal.h
//
//Desc:   class to define a goal for a soccer pitch. The goal is defined
//        by two 2D vectors representing the left and right posts.
//
//        Each time-step the method Scored should be called to determine
//        if a goal has been scored.
//
//Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "BasketBall.h"
#include "Vec2D.h"
#include "geometry.h"
#include "Grapic.h"

class Goal 
{

private:

    Vector2D   m_vPos;
    double     m_radius;
    int m_iNumGoalsScored;
public:

    Goal(Vector2D pos,double radius):
        m_vPos(pos),
        m_radius(radius),
        m_iNumGoalsScored(0)
        {
        }


    void Render()
        {
            gdi->Circle(m_vPos.x,m_vPos.y,m_radius);
        }
    
    //Given the current ball position and the previous ball position,
    //this method returns true if the ball has crossed the goal line 
    //and increments m_iNumGoalsScored
    inline bool Scored(const BasketBall*const ball);

    //-----------------------------------------------------accessor methods
    Vector2D Center() const {return m_vPos;}
    int      NumGoalsScored()const{return m_iNumGoalsScored;}
    void     ResetGoalsScored(){m_iNumGoalsScored = 0;}

    
};


/////////////////////////////////////////////////////////////////////////
bool Goal::Scored(const BasketBall*const ball)
{
    Vector2D ball_pos=ball->Pos();
    float dist=ball_pos.Distance(m_vPos);
    if(dist<=m_radius)
    {
        ++m_iNumGoalsScored;
        return true;
    }
    return false;
}


#endif
