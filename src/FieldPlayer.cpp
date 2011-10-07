#include "Grapic.h"
#include "Game.h"
#include "FieldPlayer.h"
#include "PlayerBase.h"
#include "BasketBall.h"
#include "BallTeam.h"
#include "SteeringBehavior.h"
#include <limits>
#include <iostream>
using namespace std;
using std::vector;

//------------------------------- dtor ---------------------------------------
//----------------------------------------------------------------------------
FieldPlayer::~FieldPlayer()
{
    delete m_pStateMachine;
}

//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
FieldPlayer::FieldPlayer(BallTeam* home_team,
                         State<FieldPlayer>* start_state,
                         int       home_region,
                         Vector2D  heading,
                         Vector2D  velocity,
                         double    mass,
                         double    max_force,
                         double    max_speed,
                         double    max_turn_rate,
                         double    scale,
                         player_role role):PlayerBase(home_team,
                                                      home_region,
                                                      max_speed,
                                                      Vector2D(0,0),
                                                      role)
                                           
{
    m_vVelocity.x = RandInRange(-0.2, 0.2);
    m_vVelocity.y = RandInRange(-0.2, 0.2);
    m_vPosition.x = RandInRange(-4, 4);
    m_vPosition.y = RandInRange(-4, 4);
    m_pStateMachine = new StateMachine<FieldPlayer>(this);
    if(start_state){
        m_pStateMachine->SetCurrentState(start_state);
        m_pStateMachine->SetPreviousState(start_state);
        m_pStateMachine->SetGlobalState(GlobalPlayerState::Instance());
        m_pStateMachine->CurrentState()->Enter(this);
    }
}

void FieldPlayer::Update()
{

    m_pStateMachine->Update();
    
    Vector2D force = m_pSteering->Calculate();
    m_vPosition += m_vVelocity;

    if (m_pSteering->Force().isZero())//如果没有刺激力产生 减速
    {
        const double BrakingRate = 1.0; 
        m_vVelocity = m_vVelocity * BrakingRate;                                     
    }

    double TurningForce = m_pSteering->SideComponent();

    Clamp(TurningForce, -0.3, 0.3);
    Vec2DRotateAroundOrigin(m_vHeading, TurningForce);

    m_vVelocity = m_vHeading * m_vVelocity.Length();
    m_vSide = m_vHeading.Perp();

    //of the player's heading
    Vector2D accel = m_vHeading * m_pSteering->ForwardComponent() / m_dMass;

    m_vVelocity += accel;

    //make sure player does not exceed maximum velocity
    m_vVelocity.Truncate(m_dMaxSpeed);

    //update the position
    m_vPosition += m_vVelocity;
    if(m_vPosition.x <= GetGame()->PlayingArea()->Right()||
       m_vPosition.x >= GetGame()->PlayingArea()->Left())
        m_vVelocity.x = -m_vVelocity.x;
    if(m_vPosition.y >= GetGame()->PlayingArea()->Top()||
       m_vPosition.y <= GetGame()->PlayingArea()->Bottom())
        m_vVelocity.y = -m_vVelocity.y;
}

void FieldPlayer::Render()                                         
{
    if(GetTeam()->Name()=="Blue")
        gdi->SetColor(0.0f, 1.0f, 0.0f);
    else
        gdi->SetColor(1.0f, 0.0f, 0.0f);
    gdi->Circle(m_vPosition.x, m_vPosition.y, m_dBoundingRadius);
    //gdi->glPrint(m_vPosition.x-0.1, m_vPosition.y-0.5 ,"%d:%.1f, %.1f",ID(), Pos().x, Pos().y);
    gdi->glPrint(m_vPosition.x-0.1, m_vPosition.y-0.5 ,"%d:%s", ID(), StateToStr(this->GetFSM()).c_str());
    #ifdef DEBUG_STEERING_INFO
    m_pSteering->RenderAids();
    #endif
}

bool FieldPlayer::HandleMessage(const Telegram& msg)
{
    return m_pStateMachine->HandleMessage(msg);
}
