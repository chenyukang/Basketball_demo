#include "Game.h"
#include "Goal.h"
#include "Grapic.h"
#include "BasketBall.h"
#include "BallTeam.h"
#include "FrameCounter.h"
#include "PrecisionTimer.h"
#include "Regulator.h"
#include "Region.h"
#include "Wall2D.h"
#include <time.h>
#include <iostream>
using namespace std;

const int NumRegionsHorizontal = 6; 
const int NumRegionsVertical   = 4;

Game* Game::Instance()
{
    static Game game;
    return &game;
}

Game::Game():m_bPause(false),m_bRenderRegions(false),
             m_Regions(NumRegionsHorizontal*NumRegionsVertical)
{
    m_pPlayingArea = new Region(14, 7.5, -14, - 7.5);

    m_pBall = new BasketBall(Vector2D(0.0, 0.0), 0.123, 2.0, m_vecWalls);
    
    CreateRegions(PlayingArea()->Width() / (double)NumRegionsHorizontal,
                  PlayingArea()->Height() / (double)NumRegionsVertical);

    m_pBlueGoal = new Goal(Vector2D(-12.43,0), Vector2D(1,0), 0.225);
    m_pRedGoal = new Goal(Vector2D(12.43,0), Vector2D(-1,0), 0.225);

    m_pRedTeam = new BallTeam(m_pRedGoal, m_pBlueGoal,this,BallTeam::red);
    m_pBlueTeam = new BallTeam(m_pBlueGoal,m_pRedGoal,this,BallTeam::blue);

    m_pRedTeam->SetOpponents(m_pBlueTeam);
    m_pBlueTeam->SetOpponents(m_pRedTeam); 

    m_pRegulator = new Regulator(10.0);
    Vector2D TopLeft(m_pPlayingArea->Left(), m_pPlayingArea->Top());
    Vector2D TopRight(m_pPlayingArea->Right(), m_pPlayingArea->Top());
    Vector2D BottomRight(m_pPlayingArea->Right(), m_pPlayingArea->Bottom());
    Vector2D BottomLeft(m_pPlayingArea->Left(), m_pPlayingArea->Bottom());
                                      
    m_vecWalls.push_back(Wall2D(BottomLeft, TopLeft));
    m_vecWalls.push_back(Wall2D(TopLeft, TopRight));
    m_vecWalls.push_back(Wall2D(TopRight, BottomRight));
    m_vecWalls.push_back(Wall2D(BottomRight, BottomLeft));

    srand(time(NULL));
    TIMER->Reset(60);
}

Game::~Game()
{
    printf("Game destructor\n");
    delete m_pBall;
    delete m_pPlayingArea;
    delete m_pBlueGoal;
    delete m_pRedGoal;
    delete m_pBlueTeam;
    delete m_pRedTeam;
    delete m_pRegulator;
    for (unsigned int i=0; i<m_Regions.size(); ++i)
    {
        delete m_Regions[i];
    }
}

void Game::Update()
{
    if(m_bPause)
        return;

    TIMER->Update();
    if(!TIMER->ReadyForNextFrame())
        return;
    
    m_pBall->Update();
    //if(m_pRedGoal->Scored(m_pBall))
//    {
        //m_pBall->ChangePosition(Vector2D(0,0));
        //m_pBall->SetVelocity(m_pBall->Velocity().GetReverse());
    //  }
//    else if(m_pBlueGoal->Scored(m_pBall))
//    {
        ///m_pBall->ChangePosition(Vector2D(0,0));
        //m_pBall->SetVelocity(m_pBall->Velocity().GetReverse());
//    }
    m_pBlueTeam->Update();
    m_pRedTeam->Update();
    TickCounter->Update();

//   if(m_pRegulator->isReady()){
//       cout<<"Yes ready"<<endl;
//       getchar();
//   }
    
    //cout<<TIMER->TimeElapsed()<<endl;
    //cout<<TickCounter->GetCurrentFrame()<<endl;
}

void Game::CreateRegions(double width,double height)
{
    //index into the vector
    int idx = m_Regions.size()-1;
    for (int col=0; col<NumRegionsHorizontal; ++col)
    {
        for (int row=0; row<NumRegionsVertical; ++row)
        {
            m_Regions[idx--] = new Region(PlayingArea()->Left()-col*width,
                                          PlayingArea()->Top()-row*height,
                                          PlayingArea()->Left()-(col+1)*width,
                                          PlayingArea()->Top()-(row+1)*height,
                                          idx+1);
        }
    }
}

void Game::Render()
{
    gdi->StartDrawing();
    gdi->SetPen(yellow);
    m_pPlayingArea->Render(); //边框
    if(m_bRenderRegions)
    {
        for(int i=0;i<m_Regions.size();i++)
            m_Regions[i]->Render();
    }
    
    //中线
    gdi->Line((m_pPlayingArea->Left() + m_pPlayingArea->Right()) / 2,
              m_pPlayingArea->Top(),
              (m_pPlayingArea->Left() + m_pPlayingArea->Right()) / 2,
              m_pPlayingArea->Bottom());
    //中圈
    gdi->Circle(0.0, 0.0, 1.8);

    //圈角线
    gdi->Line(14, 6.25, 12.43, 6.25);
    gdi->Line(14, -6.25, 12.43, -6.25);
    gdi->Line(-14, 6.25, -12.43, 6.25);
    gdi->Line(-14, - 6.25, - 12.43, - 6.25);

    //---------------半场弧线-------------//
    float x, y,angle,radius;
    x = -12.43;
    y = 0;
    angle = (PI/2);
    radius = 6.25;
    glBegin(GL_POINTS);
    while(angle > (-PI / 2))
    {
        glVertex2f(x + radius * cos(angle),
                   y + radius * sin(angle));
        angle-=0.01;
    }
    glEnd();
    x = 12.43;
    y = 0;
    angle = (PI / 2);
    glBegin(GL_POINTS);
    while(angle > (-PI / 2))
    {
        glVertex2f(x - radius * cos(angle),
                   y + radius * sin(angle));
        angle -= 0.01;
    }
    glEnd();
    
    //------------------------------------//

    //--------------禁区弧线----------------//
    gdi->Circle(-8.2, 0, 1.8);
    gdi->Circle(8.2, 0, 1.8);
    gdi->Line(-8.2, 1.8, - 8.2, - 1.8);
    gdi->Line(8.2, 1.8, 8.2, - 1.8);
    gdi->Line(-8.2, 1.8, - 14, 3.0);
    gdi->Line(-8.2, - 1.8, - 14, - 3.0);
    gdi->Line(8.2, 1.8, 14, 3.0);
    gdi->Line(8.2, - 1.8, 14, - 3.0);

    gdi->Line(-12.655,0,-14,0);
    gdi->Line(12.655,0,14,0);
    gdi->Line(-12.655,0.9,-12.655,-0.9);
    gdi->Line(12.655,0.9,12.655,-0.9);
    
    //------------------------------------//
    
    gdi->glPrint(7,m_pPlayingArea->Top()+0.5,"LAL %d",m_pBlueGoal->NumGoalsScored());
    gdi->glPrint(-7,m_pPlayingArea->Top()+0.5,"HOU %d",m_pRedGoal->NumGoalsScored());

    //篮球
    m_pBall->Render();
    //球筐
    m_pRedGoal->Render();
    m_pBlueGoal->Render();

    m_pBlueTeam->Render();
    m_pRedTeam->Render();
    gdi->StopDrawing();
    
}
