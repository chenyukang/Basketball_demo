
// @Name   : TeamState.cpp 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-04 15:53:41
//
// @Brief  :

#include "TeamState.h"
#include "BallTeam.h"
#include "PlayerBase.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "constants.h"
#include "Game.h"
#include "Debug.h"
#include "BasketBall.h"
#include "FieldPlayer.h"
#include "FieldPlayerStates.h"

#define DEBUG_TEAM_STATES

#define TeamSize 5

void ChangePlayerHomeRegions(BallTeam* team, const int NewRegions[TeamSize])
{
  for (int plyr=0; plyr<TeamSize; ++plyr)
  {
    team->SetPlayerHomeRegion(plyr, NewRegions[plyr]);
  }
}

Attacking* Attacking::Instance()
{
  static Attacking instance;

  return &instance;
}


void Attacking::Enter(BallTeam* team)
{
#ifdef DEBUG_TEAM_STATES
    debug_con << team->Name() << " entering Attacking state" << "\n";
#endif

  //these define the home regions for this state of each of the players
//  const int BlueRegions[TeamSize] = {1,12,14,6,4};
  const int BlueRegions[TeamSize] = {16,20,23,21,13};
  const int RedRegions[TeamSize] = {1,6,8,3,5};

  //set up the player's home regions
  if (team->Color() == BallTeam::blue)
  {
    ChangePlayerHomeRegions(team, BlueRegions);
  }
  else
  {
    ChangePlayerHomeRegions(team, RedRegions);
  }

  //if a player is in either the Wait or ReturnToHomeRegion states, its
  //steering target must be updated to that of its new home region to enable
  //it to move into the correct position.
  team->UpdateTargetsOfWaitingPlayers();
  //team->CallPlayerGoHome();
}


void Attacking::Execute(BallTeam* team)
{
    //if this team is no longer in control change states
    if (!team->InControl() && team->GetGame()->GameOn())
    {
        team->GetFSM()->ChangeState(Defending::Instance()); return;
    }

    //calculate the best position for any supporting attacker to move to
    team->DetermineBestSupportingPosition();
}

void Attacking::Exit(BallTeam* team)
{
  //there is no supporting player for defense
  team->SetSupportingPlayer(NULL);
}



//************************************************************************ DEFENDING

Defending* Defending::Instance()
{
  static Defending instance;

  return &instance;
}

void Defending::Enter(BallTeam* team)
{
#ifdef DEBUG_TEAM_STATES
    debug_con << team->Name() << " entering Defending state" << "\n";
#endif

  //these define the home regions for this state of each of the players
  const int RedRegions[TeamSize] = {16,20,23,21,13};
//  const int RedRegions[TeamSize] = {16,9,11,12,14};
  const int BlueRegions[TeamSize] = {1,6,8,3,5};

  //set up the player's home regions
  if (team->Color() == BallTeam::blue)
  {
      ChangePlayerHomeRegions(team, BlueRegions);
  }
  else
  {
      ChangePlayerHomeRegions(team, RedRegions);
  }
  
  //if a player is in either the Wait or ReturnToHomeRegion states, its
  //steering target must be updated to that of its new home region
  team->UpdateTargetsOfWaitingPlayers();
}

void Defending::Execute(BallTeam* team)
{
    //if in control change states
    if (team->InControl() && team->GetGame()->GameOn())
    {
        team->GetFSM()->ChangeState(Attacking::Instance()); return;
    }
}


void Defending::Exit(BallTeam* team){}


//************************************************************************ KICKOFF
PrepareForKickOff* PrepareForKickOff::Instance()
{
  static PrepareForKickOff instance;

  return &instance;
}

// PrepareDefanding* PrepareDefanding::Instance()
// {
//     static PrepareDefanding instance;
//     return &instance;
// }

// PrepareDefanding::Enter(BallTeam* team)
// {
//     const int BlueRegions[TeamSize] = {1,6,8,3,5};
//     ChangePlayerHomeRegions(team, BlueRegions);
// }

// PrepareDefanding::Exit(BallTeam* team)
// {
    
// }

// PrepareAttacking* PrepareAttacking::Instance()
// {
//     static PrepareAttacking instance;
//     return &instance;
// }

// PrepareAttacking*

void PrepareForKickOff::Enter(BallTeam* team)
{
    //reset key player pointers
    team->SetControllingPlayer(NULL);
    team->SetSupportingPlayer(NULL);
    team->SetReceiver(NULL);
    team->SetPlayerClosestToBall(NULL);

    int color = team->GetGame()->GetScored();
    if(color == BallTeam::blue)
        printf("blue get scored\n");
    else
        printf("red get scored\n");
    if(team->Color() == BallTeam::blue){
        if(team->GetGame()->GetScored() == BallTeam::blue){
            const int BlueRegions[TeamSize] = {1,6,8,3,5};
            ChangePlayerHomeRegions(team, BlueRegions);
        }
        else {//red team get score
            const int BlueRegions[TeamSize] = {16,20,23,21,13};
            ChangePlayerHomeRegions(team, BlueRegions);
        }
    }
    else //red team
    {
        if(team->GetGame()->GetScored() == BallTeam::red){
            const int RedRegions[TeamSize] = {16,20,23,21,13};
            ChangePlayerHomeRegions(team, RedRegions);
        }
        else{
            const int RedRegions[TeamSize] = {1,6,8,3,5};
            ChangePlayerHomeRegions(team, RedRegions);
        }
    }
    team->UpdateTargetsOfWaitingPlayers();
    if(team->GetGame()->GetScored() == BallTeam::blue) {
        double x = team->GetGame()->PlayingArea()->Left();
        double top = team->GetGame()->PlayingArea()->Top();
        double y = RandInRange(-top, top);
        team->GetGame()->GetBall()->PlaceAtPosition(Vector2D(x,y));
    }
    else if(team->GetGame()->GetScored() == BallTeam::red) 
    {
        double x = team->GetGame()->PlayingArea()->Right();
        double top = team->GetGame()->PlayingArea()->Top();
        double y = RandInRange(-top, top);
        team->GetGame()->GetBall()->PlaceAtPosition(Vector2D(x,y));
    }

    if(team->GetGame()->GetScored() != team->Color()){
        PlayerBase* it = team->GetPreparePlayer();
        FieldPlayer* plyr = static_cast<FieldPlayer*>(it);
        plyr->GetFSM()->ChangeState(ChaseBall::Instance());
        printf("I let player:%d to get ball\n",plyr->ID());
        //getchar();
    }

}

void PrepareForKickOff::Execute(BallTeam* team)
{
    if(team->GetGame()->GetScored() != team->Color())
    {
        if(team->InControl()){
            if(team->Opponents()->AllPlayersAtHome())
                team->GetFSM()->ChangeState(Attacking::Instance());
        }
    }
    else {
        if(team->AllPlayersAtHome()) {
            team->GetFSM()->ChangeState(Defending::Instance());
        }
    }
    
    // if (team->AllPlayersAtHome() && team->Opponents()->AllPlayersAtHome())
    // {
    //     printf("now in PrepareForKickOff\n");
    //    team->GetFSM()->ChangeState(Defending::Instance());
    //    //getchar();
    //  }
    
}

void PrepareForKickOff::Exit(BallTeam* team)
{
    if(team->GetGame()->GetScored() != team->Color()){
        team->GetGame()->SetGameOn();
        team->GetGame()->UnScored();
    }
}


