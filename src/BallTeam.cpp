#include "BallTeam.h"
#include "PlayerBase.h"
#include "FieldPlayer.h"
#include "Goal.h"
#include "Game.h"
#include "EntityManager.h"
#include "StateMachine.h"
#include "TeamState.h"
#include "Regulator.h"
#include "FieldPlayerStates.h"
#include "SteeringBehavior.h"
#include "MessageDispatcher.h"
#include "Messages.h"

BallTeam::BallTeam(Goal* home_goal,
                   Goal* opponents_goal,
                   Game* p_game,
                   team_color color):m_pHomeGoal(home_goal),
                                     m_pOpponentsGoal(opponents_goal),
                                     m_pGame(p_game),
                                     m_Color(color),
                                     m_dDistSqToBallOfClosestPlayer(0.0),
                                     m_pSupportingPlayer(NULL),
                                     m_pReceivingPlayer(NULL),
                                     m_pControllingPlayer(NULL),
                                     m_pPlayerClosestToBall(NULL)
{
    m_pStateMachine = new StateMachine<BallTeam>(this);
    m_pStateMachine->SetCurrentState(Attacking::Instance());
    m_pStateMachine->SetPreviousState(Attacking::Instance());
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
    CalculateClosestPlayerToBall();
    m_pStateMachine->Update();
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
                                            Wait::Instance(),
                                            1,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::Center));
 
        //create the players
        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            6,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PointGuard));


        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            8,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::ShootingGuard));


        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            3,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::SmallForward));


        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            5,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PowerForward));

    }

    else
    {
        //goalkeeper
        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            1,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::Center));
 
        //create the players
        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            6,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::PointGuard));



        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            8,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::ShootingGuard));


        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            3,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
                                            0.5,//Prm.PlayerMaxTurnRate,
                                            0.5,//Prm.PlayerScale
                                            PlayerBase::SmallForward));


        m_Players.push_back(new FieldPlayer(this,
                                            Wait::Instance(),
                                            5,
                                            Vector2D(0,1),
                                            Vector2D(0.0, 0.0),
                                            0.5,//Prm.PlayerMass,
                                            0.15,//Prm.PlayerMaxForce,
                                            0.12,//Prm.PlayerMaxSpeedWithoutBall,
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
    assert(player>=0 && player<=m_Players.size() && "invalid player number");
    m_Players[player]->SetHomeRegion(region);
}


void BallTeam::CallPlayerGoHome() const
{
    std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {  
        FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
        int id = plyr->ID();
        //tell the player to make the pass
        //let the receiver know a pass is coming 
        Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                                -1,
                                id,
                                Msg_GoHome,
                                NULL);
    } 
}

void BallTeam::UpdateTargetsOfWaitingPlayers() const
{
  std::vector<PlayerBase*>::const_iterator it = m_Players.begin();

  for (it; it != m_Players.end(); ++it)
  {  
      FieldPlayer* plyr = static_cast<FieldPlayer*>(*it);
      
      if ( plyr->GetFSM()->isInState(*Wait::Instance()) ||
           plyr->GetFSM()->isInState(*Dummpy::Instance()) ||
           plyr->GetFSM()->isInState(*ReturnToHomeRegion::Instance())||
           plyr->GetFSM()->isInState(*ReceiveBall::Instance()))
      {
        plyr->Steering()->SetTarget(plyr->HomeRegion()->Center());
        //plyr->GetFSM()->ChangeState(ReturnToHomeRegion::Instance());
      }
      if( plyr == PlayerClosestToBall() && plyr != m_pControllingPlayer &&
          plyr->GetGame()->GameOn())
      {
          plyr->GetFSM()->ChangeState(ChaseBall::Instance());
      }
  }
}


void BallTeam::CalculateClosestPlayerToBall()
{
    double ClosestSoFar = MaxFloat;
    std::vector<PlayerBase*>::iterator it = m_Players.begin();

    for (it; it != m_Players.end(); ++it)
    {
        //calculate the dist. Use the squared value to avoid sqrt
        double dist = Vec2DDistanceSq((*it)->Pos(), GetGame()->GetBall()->Pos());

        //keep a record of this value for each player
        (*it)->SetDistSqToBall(dist);
    
        if (dist < ClosestSoFar)
        {
            ClosestSoFar = dist;

            m_pPlayerClosestToBall = *it;
        }
    }

    m_dDistSqToBallOfClosestPlayer = ClosestSoFar;
}

PlayerBase* BallTeam::GetPreparePlayer()
{
    CalculateClosestPlayerToBall();
    return m_pPlayerClosestToBall;
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
    m_pControllingPlayer = player;
    //rub it in the opponents faces!
    Opponents()->LostControl();
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
    std::vector<PlayerBase*>::const_iterator it = m_Players.begin();
      
    for (it; it != m_Players.end(); ++it)
    {
        Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                                1,
                                (*it)->ID(),
                                Msg_GoHome,
                                NULL);
    }
}


bool BallTeam::CanShoot(const Vector2D& pos)
{
    double distance = OpponentsGoal()->Center().Distance(pos);
    if( distance < 5.0 )
        return true;
    return false;
}

bool BallTeam::CanDunk(const Vector2D& pos)
{
    double distance = OpponentsGoal()->Center().Distance(pos);
    if( distance < 1.0 )
        return true;
    return false;
}

bool BallTeam::isPassSafeFromAllOpponents(const Vector2D& from,
                                          const Vector2D& topos,
                                          PlayerBase* receiver,
                                          double maxPassForce)
{
    return true;
                    
}

void BallTeam::RequestPass(PlayerBase* requester)
{
    Vector2D ball_pos = ControllingPlayer()->Ball()->Pos();
    Vector2D plyr_pos = requester->Pos();
    double dist  =plyr_pos.Distance(ball_pos);
    if(dist  > 5.0f)
        return;
    if(ControllingPlayer()->Ball()->GetState() == inPassing||
       ControllingPlayer()->Ball()->GetState() == inGround) //ball have been inpassing or inground
        return;
    if (isPassSafeFromAllOpponents(ControllingPlayer()->Pos(),
                                   requester->Pos(),
                                   requester,
                                   0.5))
    {

        //tell the player to make the pass
        //let the receiver know a pass is coming 
        Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                                requester->ID(),
                                ControllingPlayer()->ID(),
                                Msg_GiveMeBall,
                                requester);
    }
}

bool BallTeam::AllPlayersAtHome() const
{
    std::vector<PlayerBase*>::const_iterator it = m_Players.begin();
    int cnt = 0;
    for (it; it != m_Players.end(); ++it)
    {
        Vector2D center = (*it)->HomeRegion()->Center();
        if( (*it)->Pos().x * center.x > 0)
            cnt ++;
    }
    if(cnt>=4)
        return true;
    return false;
}
