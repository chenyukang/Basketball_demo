/**
 * @file   Game.h
 * @author moorekang <moorekang@gmail.com>
 * @date   Sun Jul 18 15:30:25 2010
 * 
 * @brief  Game class def
 * 
 * 
 */
#ifndef _GAME_H__
#define _GAME_H__
#include "Region.h"
#include <stdio.h>
#include <vector>

#define GAME Game::Instance()

class BasketBall;
class BallTeam;
class Goal;
class Regulator;
class Wall2D;
class Game
{
private:
    Game();
    ~Game();

    BasketBall*  m_pBall;
    bool         m_bPause;
    bool         m_bRenderRegions;
    Region*      m_pPlayingArea; 
    std::vector<Region*> m_Regions;

    BallTeam*    m_pRedTeam;
    BallTeam*    m_pBlueTeam;
    Goal*        m_pBlueGoal;
    Goal*        m_pRedGoal;
    Regulator*   m_pRegulator;
    std::vector<Wall2D>  m_vecWalls;
    void         CreateRegions(double,double);
    
public:
    void Render();
    void Update();
    static Game* Instance();

    void         ChangePauseFlag() { m_bPause=!m_bPause;}
    void         ChangeRenderRegionFlag() { m_bRenderRegions=!m_bRenderRegions;}
    const Region*const  PlayingArea()const{return m_pPlayingArea;}
    BasketBall*  GetBall() const { return m_pBall; }
    void         SetGameOn() const { /*TODO*/ };
    bool         GameOn() { return true; }
    const Region* const GetRegionFromIndex(int idx)                                
        {
            assert ( (idx >= 0) && (idx < (int)m_Regions.size()) );
            
            return m_Regions[idx];
        }

};

#endif
