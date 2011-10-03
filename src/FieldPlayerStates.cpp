
// @Name   : FieldPlayerStates.cpp 
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2011-09-17 23:26:21
//
// @Brief  :

#include "FieldPlayerStates.h"
#include "FieldPlayer.h"
#include "SteeringBehavior.h"
#include "BasketBall.h"
#include "BallTeam.h"
#include "Region.h"
#include "Game.h"
#include "Goal.h"
#include <stdio.h>
#define PLAYER_STATE_INFO_ON


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

bool GlobalPlayerState::OnMessage(FieldPlayer* player, const Telegram& msg)
{
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
            printf("returnhome ==> Chaseball\n");
            player->GetFSM()->ChangeState(ChaseBall::Instance());
            return;
        }
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
    player->Steering()->SetTarget(player->GetTeam()->OpponentsGoal()->Center());
                                  
#ifdef PLAYER_STATE_INFO_ON
    cout<< "Player " << player->ID() << " enters ControlBall state" <<endl;
#endif
    
}


void ControlBall::Execute(FieldPlayer* player)
{

    double r = RandInRange(0.0,1.0);
    if(r < 0.02 && 
       player->GetTeam()->Opponents()->GetClosestDistToBall() < 3){
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
//    printf("center:%.3f, %.3f\n",player->HomeRegion()->Center().x,
//           player->HomeRegion()->Center().y);
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
    if ( player->GetTeam()->InControl()    &&
         (!player->isControllingPlayer()) &&
         player->isAheadOfAttacker() )
    {
//    player->GetTeam()->RequestPass(player);
//    return;
    }

    if (player->GetGame()->GameOn())
    {
        if (player->isClosestTeamMemberToBall() &&
            player->GetTeam()->Receiver() == NULL)
        {
            printf("wait to chaseball\n");
            player->GetFSM()->ChangeState(ChaseBall::Instance());
            return;
        }
    } 
}

void Wait::Exit(FieldPlayer* player){}

