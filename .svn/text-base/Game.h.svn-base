/**
 * @file   Game.h
 * @author moorekang <moorekang@gmail.com>
 * @date   Sun Jul 18 15:30:25 2010
 * 
 * @brief  球场类 主逻辑控制类
 * 
 * 
 */
#ifndef _GAME_H__
#define _GAME_H__
#include "Region.h"
#include <vector>

#define GAME Game::Instance()

class BasketBall;
class BallTeam;
class Goal;

class Game
{
private:
    Game();
    ~Game();

    BasketBall*  m_pBall;
    bool         m_bPause;
    bool         m_bRenderRegions;
    Region*      m_pPlayingArea; //球场的矩形范围
    std::vector<Region*> m_Regions;

    BallTeam*    m_pRedTeam;
    BallTeam*    m_pBlueTeam;
    Goal*        m_pBlueGoal;
    Goal*        m_pRedGoal;
    
    void         CreateRegions(double,double);
    
public:
    void Render();
    void Update();
    static Game* Instance();

    void         ChangePauseFlag() { m_bPause=!m_bPause;}
    void         ChangeRenderRegionFlag() { m_bRenderRegions=!m_bRenderRegions;}
    const Region*const  PlayingArea()const{return m_pPlayingArea;}
};

#endif
