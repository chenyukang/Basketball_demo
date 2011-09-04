#ifndef BALL_TEAM_H__
#define BALL_TEAM_H__
#include <vector>
#include <string>
#include <stdio.h>
#include "StateMachine.h"

class Game;
class Goal;
class PlayerBase;

class BallTeam
{
public:
    enum team_color{red, blue};
    
private:
    team_color                m_Color;
    std::vector<PlayerBase*>  m_Players;

    Game*                     m_pGame;
    Goal*                     m_pOpponentsGoal;
    Goal*                     m_pHomeGoal;

    //a pointer to the opposing team
    BallTeam*                 m_pOpponents;
    StateMachine<BallTeam>*    m_pStateMachine;
   
    //pointers to 'key' players
    PlayerBase*               m_pControllingPlayer;
    PlayerBase*               m_pSupportingPlayer;
    PlayerBase*               m_pReceivingPlayer;
    PlayerBase*               m_pPlayerClosestToBall;

    //the squared distance the closest player is from the ball
    double                     m_dDistSqToBallOfClosestPlayer;

    void CreatePlayers();//初始化时创造成员

public:
    BallTeam(Goal*        home_goal,
             Goal*        opponents_goal,
             Game*        p_game,
             team_color   color);

    ~BallTeam();

    //the usual suspects
    void        Render()const;
    void        Update();
    team_color  Color() const {return m_Color;}
    std::string Name()const{if (m_Color == blue) return "Blue"; return "Red";}
    Game*       GetGame() const { return m_pGame;}
    void        SetPlayerHomeRegion(int player, int region) const;
    void        UpdateTargetsOfWaitingPlayers() const;
    bool        InControl()const{if(m_pControllingPlayer)return true; else return false;}
    void        DetermineBestSupportingPosition();
    void        SetSupportingPlayer(PlayerBase*);
    void        SetControllingPlayer(PlayerBase*);
    void        SetReceiver(PlayerBase*);
    void        SetPlayerClosestToBall(PlayerBase*);
    void        ReturnAllFieldPlayersToHome();
    bool        AllPlayersAtHome() const { return false; }
    BallTeam*   Opponents() const { return m_pOpponents; }
    
    StateMachine<BallTeam>*  GetFSM() const { return m_pStateMachine; }
};

#endif
