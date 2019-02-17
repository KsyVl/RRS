//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------
#ifndef     TEST_LOCO_H
#define     TEST_LOCO_H

#include    "vehicle.h"
#include    "brake-crane.h"
#include    "brake-mech.h"

class TestLoco : public Vehicle
{
public:

    TestLoco();
    ~TestLoco();

private:

    double traction_level;

    bool inc_loc;
    bool dec_loc;

    bool inc_crane_loc;
    bool dec_crane_loc;

    int crane_pos;

    double pz;
    bool inc_brake;
    bool dec_brake;

    QString brake_crane_module;
    BrakeCrane  *brake_crane;
    BrakeMech   *brake_mech;

    QString     brake_mech_module;
    QString     brake_mech_config;

    void step(double t, double dt);

    double traction_char(double V);

    void initialization();

    void loadConfig(QString cfg_path);

    void keyProcess();
};

#endif // TESTLOCO_H
