
#ifndef _CONSTANT_H__
#define _CONSTANT_H__

#define PRM  Prm::Instance()
class Prm
{
private:
    Prm();

public:
    static Prm* Instance();
    double PlayerMass;
    double PlayerMaxForce;
    double PlayerMaxSpeedWithoutBall;
    double PlayerMaxTurnRate;
    double PlayerScale;
    int    NumRegionsHorizontal;
    int    NumRegionsVertical;
};

#endif
