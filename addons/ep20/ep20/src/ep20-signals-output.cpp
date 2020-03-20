#include    "ep20.h"

void EP20::stepSignals()
{
    analogSignal[STRELKA_pTM] = static_cast<float>(pTM / 1.0);
    analogSignal[STRELKA_pGR] = static_cast<float>(main_reservoir->getPressure() / 1.6);
    analogSignal[STRELKA_pTC] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure() / 1.6);
    analogSignal[STRELKA_pUR] = static_cast<float>(krm->getEqReservoirPressure() / 1.0);

    analogSignal[RUK_KRM130] = krm->getHandlePosition();
    analogSignal[RUK_KVT224] = static_cast<float>(kvt->getHandlePosition());

    analogSignal[KMB2_Real] = kmb2->getTractionPosition();
    analogSignal[KMB2_Fake] = kmb2->getVelocityPosition();

    analogSignal[KeyCard_Fake] = kmb2->getTurn();
    analogSignal[KeyCard_Low] = kmb2->getS3();

    analogSignal[Key] = mpcs->getKeyPosition();

    analogSignal[BLOK_TC_PRESS] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    analogSignal[BLOK_TM_PRESS] = static_cast<float>(pTM);
    analogSignal[BLOK_UR_PRESS] = static_cast<float>(krm->getEqReservoirPressure());

    analogSignal[BLOK_RAILWAY_COORD] = static_cast<float>(railway_coord / 1000.0);
    analogSignal[BLOK_VELOCITY] = static_cast<float>(velocity * Physics::kmh);
    analogSignal[BLOK_VELOCITY_CURRENT_LIMIT] = 200.0f;
    analogSignal[BLOK_VELOCITY_NEXT_LIMIT] = 200.0f;

    analogSignal[PANTOGRAPH_AC1] = static_cast<float>(pantograph[PANT_AC1]->getHeight());
    analogSignal[PANTOGRAPH_DC1] = static_cast<float>(pantograph[PANT_DC1]->getHeight());
    analogSignal[PANTOGRAPH_AC2] = static_cast<float>(pantograph[PANT_AC2]->getHeight());
    analogSignal[PANTOGRAPH_DC2] = static_cast<float>(pantograph[PANT_DC2]->getHeight());

    analogSignal[sigLight_Pant_fwd] = 1;
    analogSignal[sigLight_Pant_bwd] = 1;
    analogSignal[sigLight_GV] = 1;
    analogSignal[sigLight_Train_heating] = 1;
    analogSignal[sigLight_Recap_disable] = 1;
    analogSignal[sigLight_AutoDriver] = 1;
    analogSignal[sigLight_SpeedControl] = 1;
    analogSignal[sigLight_VZ] = 1;
    analogSignal[sigLight_EPT] = 1;
    analogSignal[sigLight_GS] = 1;
    analogSignal[sigLight_PV] = 1;
    analogSignal[sigLight_Whell_clean] = 1;
    analogSignal[sigLight_Saund1] = 1;
    analogSignal[sigLight_Brake_release] = 1;
    analogSignal[sigLight_Test] = 1;
    analogSignal[sigLight_Res_Purge] = 1;

    analogSignal[LS_G4] = 1;
    analogSignal[LS_G3] = 1;
    analogSignal[LS_G2] = 1;
    analogSignal[LS_G1] = 1;
    analogSignal[LS_Y] = 1;
    analogSignal[LS_RY] = 1;
    analogSignal[LS_R] = 1;
    analogSignal[LS_W] = 1;

    analogSignal[WHEEL_1] = static_cast<float>(dir * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEEL_2] = static_cast<float>(dir * wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEEL_3] = static_cast<float>(dir * wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEEL_4] = static_cast<float>(dir * wheel_rotation_angle[3] / 2.0 / Physics::PI);
    analogSignal[WHEEL_5] = static_cast<float>(dir * wheel_rotation_angle[4] / 2.0 / Physics::PI);
    analogSignal[WHEEL_6] = static_cast<float>(dir * wheel_rotation_angle[5] / 2.0 / Physics::PI);

}
