#include "BallTeam.h"
#include "PlayerBase.h"
#include "FieldPlayer.h"
#include "Goal.h"
#include "Game.h"
#include "EntityManager.h"
#include "StateMachine.h"
#include "TeamState.h"

BallTeam::BallTeam(Goal* home_goal,
                   Goal* opponents_goal,
                   Game* p_game,
                   team_color color):m_pHomeGoal(home_goal),
                                     m_pOpponentsGoal(opponents_goal),
                                     m_pGame(p_game),
                                     m_Color(color)
{
    m_pStateMachine = new StateMachine<BallTeam>(this);

    m_pStateMachine->SetCurrentState(Defending::Instance());
    m_pStateMachine->SetPreviousState(Defending::Instance());
    m_pStateMachine->SetGlobalState(NULL);

    CreatePlayers();
}

BallTeam::~BallTeam()
{
    std::vector<PlayerBase*>::iterator it = m_Players.begin();
    for (it; it != m_Players.end(); ++it)
    {
        delete *it;
    }
}

void BallTeam::Update()
{
  
    //now update each player
    std::vector<PlayerBase*>::iterator it = m_Players.begin();
    for (it; it != m_Players.end(); ++it)
    {
        (*it)->Update();
    }

}

void BallTeam::Render() const
{
    std::vector<PlayerBase*>::const_iterator it = m_Players.begin();
    for (it; it != m_Players.end(); ++it)
    {
        (*it)->Render();
    }
}

void BallTeam::CreatePlayers()
{
    if (Color() == blue)
    {
        //goalkeeper
        m_Players.push_back(new FieldPlayer(this,
                                            1,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::Center));
 
        //create the players
        m_Players.push_back(new FieldPlayer(this,
                                            6,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PointGuard));



        m_Players.push_back(new FieldPlayer(this,
                                            8,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::ShootingGuard));


        m_Players.push_back(new FieldPlayer(this,
                                            3,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::SmallForward));


        m_Players.push_back(new FieldPlayer(this,
                                            5,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PowerForward));

    }

    else
    {
        //goalkeeper
        m_Players.push_back(new FieldPlayer(this,
                                            1,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::Center));
 
        //create the players
        m_Players.push_back(new FieldPlayer(this,
                                            6,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PointGuard));



        m_Players.push_back(new FieldPlayer(this,
                                            8,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::ShootingGuard));


        m_Players.push_back(new FieldPlayer(this,
                                            3,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::SmallForward));


        m_Players.push_back(new FieldPlayer(this,
                                            5,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.5,//Prm.PlayerMaxForce,
                                            0.5,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PowerForward));
    }

    //register the players with the entity manager
    std::vector<PlayerBase*>::iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {
        EntityMgr->RegisterEntity(*it);
    }
}


void BallTeam::SetPlayerHomeRegion(int player, int region) const
{
    assert(player>0 && player<m_Players.size() && "invalid player number");
    m_Players[player]->SetHomeRegion(region);
}


void BallTeam::UpdateTargetsOfWaitingPlayers() const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {  
      //cast to a field player
        //FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
      
      // if ( plyr->GetFSM()->isInState(*Wait::Instance()) ||
      //      plyr->GetFSM()->isInState(*ReturnToHomeRegion::Instance()) )
      // {
      //   plyr->Steering()->SetTarget(plyr->HomeRegion()->Center());
      // }
  }
}


void BallTeam::DetermineBestSupportingPosition()
{
    //TODO
}


void BallTeam::SetSupportingPlayer(PlayerBase* player)
{
    //TODO
}

void BallTeam::SetControllingPlayer(PlayerBase* player)
{
    //TODO;
}

void BallTeam::SetReceiver(PlayerBase* player)
{
    //TODO;
}

void BallTeam::SetPlayerClosestToBall(PlayerBase* player)
{
    //TODO;
}

void BallTeam::ReturnAllFieldPlayersToHome()
{
    //TODO;
}

