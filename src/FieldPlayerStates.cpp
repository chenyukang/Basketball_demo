
// @Name   : FieldPlayerStates.cpp 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-17 23:26:21
//
// @Brief  :

#include <stdio.h>
#include "Goal.h"
#include "Game.h"
#include "Region.h"
#include "BallTeam.h"
#include "FieldPlayer.h"
#include "BasketBall.h"
#include "FieldPlayerStates.h"
#include "SteeringBehavior.h"
#include "Messages.h"
#include "MessageDispatcher.h"
//#define PLAYER_STATE_INFO_ON

std::string StateToStr(StateMachine<FieldPlayer>* machine)
{
    if(machine->isInState(*ChaseBall::Instance()))
        return "ChaseBall";
    if(machine->isInState(*ControlBall::Instance()))
        return "ControlBall";
    if(machine->isInState(*ReceiveBall::Instance()))
        return "ReceiveBall";
    if(machine->isInState(*Wait::Instance()))
        return "Wait";
    if(machine->isInState(*Dummpy::Instance()))
        return "Dummpy";
    if(machine->isInState(*ReturnToHomeRegion::Instance()))
        return "Return";
    return "Nodefine";
}

GlobalPlayerState* GlobalPlayerState::Instance()
{
    static GlobalPlayerState instance;
    return &instance;
}

void GlobalPlayerState::Execute(FieldPlayer* player)
{
    //printf("\n now in GlobalPlayerState::Execute\n");
    ///player->SetMaxSpeed(player->Get);
}

bool GlobalPlayerState::OnMessage(FieldPlayer* player, const Telegram& telegram)
{
    switch(telegram.Msg){
    case Msg_ReceiveBall:
    {
        //set the target
        player->Steering()->SetTarget(*(static_cast<Vector2D*>(telegram.ExtraInfo)));
        //change state 
        player->GetFSM()->ChangeState(ReceiveBall::Instance());
        return true;
    }

    break;
    
    case Msg_GiveMeBall:
        //get the position of the player requesting the pass 
        FieldPlayer* receiver = static_cast<FieldPlayer*>(telegram.ExtraInfo);

#ifdef PLAYER_STATE_INFO_ON
        debug_con << "Player " << player->ID() << " received request from " <<
            receiver->ID() << " to make pass" << "";
#endif

        //if the ball is not within kicking range or their is already a 
        //receiving player, this player cannot pass the ball to the player
        //making the request.
        if (player->GetTeam()->Receiver() != NULL ||
            !player->BallWithinPassRange() )
        {
#ifdef PLAYER_STATE_INFO_ON
            debug_con << "Player " << player->ID() << " cannot make requested pass <cannot kick ball>" << "";
#endif
            return true;
        }
      
        //make the pass   
        player->Ball()->Kick(receiver->Pos() - player->Ball()->Pos(),
                             2.0);
        printf("I have passed\n");
          
#ifdef PLAYER_STATE_INFO_ON
        debug_con << "Player " << player->ID() << " Passed ball to requesting player" << "";
#endif
        
        //let the receiver know a pass is coming
        Vector2D pos = receiver->Pos();
        Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                                player->ID(),
                                receiver->ID(),
                                Msg_ReceiveBall,
                                &pos);

        

        //change state   
        player->GetFSM()->ChangeState(Dummpy::Instance());

        return true;
    }
    return false;
}

ChaseBall* ChaseBall::Instance()
{
    static ChaseBall instance;
    return &instance;
}

void ChaseBall::Enter(FieldPlayer* player)
{
#ifdef PLAYER_STATE_INFO_ON
    cout<<"Player "<<player->ID()<<" Enter ChaseBall"<<endl;
#endif
    player->Steering()->SeekOn();
}

void ChaseBall::Execute(FieldPlayer* player)
{
    if (player->Ball()->isCanControl() &&
        player->BallWithinControlRange())
    {
        player->GetFSM()->ChangeState(ControlBall::Instance());
        return;
    }
    
    if (player->isClosestTeamMemberToBall()){
        player->Steering()->SetTarget(player->Ball()->Pos());
    }
    else{
#ifdef PLAYER_STATE_INFO_ON
        cout<<player->ID()<<" ChaseBall ==> ReturnToHomeRegion"<<endl;
#endif
        player->GetFSM()->ChangeState(ReturnToHomeRegion::Instance());
    }
}

void ChaseBall::Exit(FieldPlayer* player)
{
    player->Steering()->SeekOff();
}

ReturnToHomeRegion* ReturnToHomeRegion::Instance()
{
    static ReturnToHomeRegion instance;
    return &instance;
}

void ReturnToHomeRegion::Enter(FieldPlayer* player)
{
#ifdef PLAYER_STATE_INFO_ON
    cout<<player->ID()<<" Enter ReturnToHomeRegion"<<endl;
#endif
    
    player->Steering()->ArriveOn();
    if (!player->HomeRegion()->Inside(player->Steering()->Target(), Region::halfsize))
    {
        player->Steering()->SetTarget(player->HomeRegion()->Center());
    }
    
#ifdef PLAYER_STATE_INFO_ON
    cout << "Player " << player->ID() << " enters ReturnToHome state" << ""<<endl;
#endif
}

void ReturnToHomeRegion::Execute(FieldPlayer* player)
{
    if (player->GetGame()->GameOn())
    {
        //if the ball is nearer this player than any other team member  &&
        //there is not an assigned receiver && the goalkeeper does not gave
        //the ball, go chase it
        if ( player->isClosestTeamMemberToBall() &&
             (player->GetTeam()->Receiver() == NULL))
        {
            //printf("returnhome ==> Chaseball\n");
            player->GetFSM()->ChangeState(ChaseBall::Instance());
            return;
        }
    }
    double r = RandInRange(0,1.0);
    if ( r < 0.2 &&  player->GetTeam()->InControl()    &&
         (!player->isControllingPlayer()) &&
         player->isAheadOfAttacker() &&
         player->GetTeam()->Receiver()==NULL)
    {
        player->GetTeam()->RequestPass(player);
        printf("Player %d request Pass\n", player->ID());
        return;
    }

    if (player->GetGame()->GameOn() && player->HomeRegion()->Inside(player->Pos(),
                                                                    Region::halfsize))
    {
        player->Steering()->SetTarget(player->Pos());
        player->GetFSM()->ChangeState(Wait::Instance());
    }
    //if game is not on the player must return much closer to the center of his
    //home region
    else if(!player->GetGame()->GameOn() && player->AtTarget())
    {
        player->GetFSM()->ChangeState(Wait::Instance());
    }
}

void ReturnToHomeRegion::Exit(FieldPlayer* player)
{
    player->Steering()->ArriveOff();
}


ControlBall* ControlBall::Instance()
{
    static ControlBall instance;
    return &instance;
}


void ControlBall::Enter(FieldPlayer* player)
{
    //let the team know this player is controlling
    player->GetTeam()->SetControllingPlayer(player);
    player->Ball()->SetControllingPlayer(player);
    player->Steering()->SeekOn();
    Vector2D target  = Vector2D((player->GetTeam()->OpponentsGoal()->Center().x + RandInRange(-1.0,1.0)),
                                player->GetTeam()->OpponentsGoal()->Center().y + RandInRange(-1.0, 1.0));
    player->Steering()->SetTarget(target);
                                  
#ifdef PLAYER_STATE_INFO_ON
    cout<< "Player " << player->ID() << " enters ControlBall state" <<endl;
#endif
    
}


void ControlBall::Execute(FieldPlayer* player)
{

    double r = RandInRange(0.0,1.0);
    if(r < 0.1 && 
       player->GetTeam()->Opponents()->GetClosestDistToBall() < 1.0){
        player->Ball()->Kick(player->GetTeam()->HomeGoal()->Facing(),
                             2.0);
        player->GetFSM()->ChangeState(Dummpy::Instance()); //lose ball
    }

    float power = RandInRange(2.0f,3.0f); //try to shot the ball
    if ( player->GetTeam()->Opponents()->GetClosestDistToBall()>2.5 && 
         player->GetTeam()->CanShoot(player->Ball()->Pos()) &&
         RandInRange(0.0, 1.0) < 0.2 ) {
        #ifdef PLAYER_STATE_INFO_ON
        cout<<"Player "<<player->ID() << "attempts a shot "<<endl;
        #endif
        Vector2D target = player->GetTeam()->OpponentsGoal()->Center();
        target = AddNoiseToShot(player->Ball()->Pos(), target);

        Vector2D ShotDirection = target - player->Ball()->Pos();
        player->Ball()->Shot(ShotDirection, power, player->GetTeam()->OpponentsGoal());
        //change state
        player->GetFSM()->ChangeState(Dummpy::Instance());
        return;
    }

}


void ControlBall::Exit(FieldPlayer* player)
{
    player->Ball()->SetUnControl();
}

Dummpy* Dummpy::Instance()
{
    static Dummpy instance;
    return &instance;
}


void Dummpy::Enter(FieldPlayer* player)
{
    #ifdef PLAYER_STATE_INFO_ON
    cout<<"Player "<< player->ID() << " enters dummpy state" <<endl;
    #endif

    player->SetVelocity(Vector2D(0,0));
    player->Steering()->SteeringClear();
    player->setWaitTimeRegulator(RandInRange(0.5f,1.0f));
}

void Dummpy::Execute(FieldPlayer* player)
{
    if(player->isRegulatorReady()){
        player->GetFSM()->ChangeState(Wait::Instance());
    }
    else{
        //player->DecreaseVel();
    } 
}

void Dummpy::Exit(FieldPlayer* player)
{
    
}


ReceiveBall* ReceiveBall::Instance()
{
    static ReceiveBall instance;
    return &instance;
}

void ReceiveBall::Enter(FieldPlayer* player)
{
    //doto
    printf("Player %d enter ReceiveBall\n",player->ID());
    player->GetTeam()->SetReceiver(player);
    player->Steering()->PursuitOn();
    player->setWaitTimeRegulator(RandInRange(1.0,2.0));
}

void ReceiveBall::Execute(FieldPlayer* player)
{
    if (player->BallWithinReceivingRange())
    {
        player->GetFSM()->ChangeState(ControlBall::Instance());
        return;
    }  

    if (player->Steering()->PursuitIsOn())
    {
        player->Steering()->SetTarget(player->Ball()->Pos());
    }

    //if the player has 'arrived' at the steering target he should wait and
    //turn to face the ball
    if (player->AtTarget())
    {
        player->Steering()->ArriveOff();
        player->Steering()->PursuitOff();
        player->TrackBall();    
        player->SetVelocity(Vector2D(0,0));
    }

    if(player->isRegulatorReady())
    {
        player->GetFSM()->ChangeState(Wait::Instance());
    }
}

void ReceiveBall::Exit(FieldPlayer* player)
{
    player->Steering()->PursuitOff();
    player->GetTeam()->SetReceiver(NULL);
}

Wait* Wait::Instance()
{
    static Wait instance;
    return &instance;
}

void Wait::Enter(FieldPlayer* player)
{
#ifdef PLAYER_STATE_INFO_ON
    cout << "Player " << player->ID() << " enters wait state" << endl;
#endif

    //if the game is not on make sure the target is the center of the player's
    //home region. This is ensure all the players are in the correct positions
    //ready for kick off
    if (player->GetGame()->GameOn())
    {
        player->Steering()->SetTarget(player->HomeRegion()->Center());
    }
}

void Wait::Execute(FieldPlayer* player)
{    
    //if the player has been jostled out of position, get back in position  
    if (!player->AtTarget())
    {
        player->Steering()->ArriveOn();
        return;
    }
    else
    {
        player->Steering()->ArriveOff();
        //player->SetVelocity(Vector2D(0,0));
        //the player should keep his eyes on the ball!
        player->TrackBall();
    }

    //if this player's team is controlling AND this player is not the attacker
    //AND is further up the field than the attacker he should request a pass.
    double r  = RandInRange(0.0,1.0);
        if ( r < 0.1 && player->GetTeam()->InControl()    &&
             (!player->isControllingPlayer()) &&
             player->isAheadOfAttacker() &&
             player->GetTeam()->Receiver()==NULL)
    {
        player->GetTeam()->RequestPass(player);
        printf("Player %d request Pass\n", player->ID());
        return;
    }

    if (player->GetGame()->GameOn())
    {
        if (player->isClosestTeamMemberToBall() &&
            player->GetTeam()->Receiver() == NULL)
        {
            player->GetFSM()->ChangeState(ChaseBall::Instance());
            return;
        }
    } 
}

void Wait::Exit(FieldPlayer* player){}


