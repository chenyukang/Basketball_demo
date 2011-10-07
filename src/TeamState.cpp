
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
}


void Attacking::Execute(BallTeam* team)
{
  //if this team is no longer in control change states
  if (!team->InControl())
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
  if (team->InControl())
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

void PrepareForKickOff::Enter(BallTeam* team)
{
  //reset key player pointers
  team->SetControllingPlayer(NULL);
  team->SetSupportingPlayer(NULL);
  team->SetReceiver(NULL);
  team->SetPlayerClosestToBall(NULL);

  //send Msg_GoHome to each player.
  team->ReturnAllFieldPlayersToHome();
}

void PrepareForKickOff::Execute(BallTeam* team)
{
  //if both teams in position, start the game
  if (team->AllPlayersAtHome() && team->Opponents()->AllPlayersAtHome())
  {
    team->GetFSM()->ChangeState(Defending::Instance());
  }
}

void PrepareForKickOff::Exit(BallTeam* team)
{
  team->GetGame()->SetGameOn();
}


