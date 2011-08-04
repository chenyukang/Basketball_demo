#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include <vector>
#include <string>
#include <cassert>
#include "Vec2D.h"
#include "PlayerBase.h"

class SteeringBehavior;
class BallTeam;
class Game;
class Goal;
struct Telegram;


class FieldPlayer : public PlayerBase
{
private:
  
public:

    FieldPlayer(BallTeam*      home_team,
                int            home_region, //the default area player stand
                Vector2D       heading,
                Vector2D       velocity,
                double         mass,
                double         max_force,
                double         max_speed,
                double         max_turn_rate,
                double         scale,
                player_role    role);   
  
    ~FieldPlayer();

    //call this to update the player's position and orientation
    void        Update();   
    void        Render();
};

#endif
