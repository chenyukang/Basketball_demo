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
    Vector2D   m_vFacing;
    double     m_radius;
    int        m_iNumGoalsScored;
    int        m_isScored;
public:

    Goal(Vector2D pos, Vector2D face, double radius):
        m_vPos(pos),
        m_vFacing(face),
        m_radius(radius),
        m_iNumGoalsScored(0),
        m_isScored(0)
        {
        }


    void Render()
        {
            gdi->Circle(m_vPos.x,m_vPos.y,m_radius);
        }
    
    //Given the current ball position and the previous ball position,
    //this method returns true if the ball has crossed the goal line 
    //and increments m_iNumGoalsScored
    inline bool Scored(const Vector2D& ballpos);

    //-----------------------------------------------------accessor methods
    Vector2D Center() const {return m_vPos;}
    Vector2D Facing() const {return m_vFacing;}
    int      NumGoalsScored()const{return m_iNumGoalsScored;}
    void     ResetGoalsScored(){m_iNumGoalsScored = 0;}
    int       isScored() const { return m_isScored;}
    void      UnScored() { m_isScored = 0;}
};


/////////////////////////////////////////////////////////////////////////
bool Goal::Scored(const Vector2D&  ball_pos)
{
    //Vector2D ball_pos = ball->Pos();
    //printf("ball:%.3f %.3f\n", ball_pos.x, ball_pos.y);
    //printf("goal:%.3f %.3f\n", m_vPos.x, m_vPos.y);
    float dist = ball_pos.Distance(m_vPos);
    //printf("done\n");
    if(dist<=m_radius)
    {
        ++m_iNumGoalsScored;
        m_isScored = 2;
        return true;
    }
    return false;
}

#endif
