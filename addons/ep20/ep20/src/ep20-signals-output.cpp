#include    "ep20.h"



void EP20::stepSignals(double t, double dt)
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

    // Левая панель сенсорных клавиш
    analogSignal[sigLight_Pant_fwd] = mpcsOutput.lamps_state.pant_fwd.state;
    analogSignal[sigLight_Pant_bwd] = mpcsOutput.lamps_state.pant_bwd.state;
    analogSignal[sigLight_GV] = mpcsOutput.lamps_state.gv.state;
    analogSignal[sigLight_Train_heating] = mpcsOutput.lamps_state.train_heating.state;
    analogSignal[sigLight_Recap_disable] = mpcsOutput.lamps_state.recup_disable.state;
    analogSignal[sigLight_AutoDriver] = mpcsOutput.lamps_state.auto_driver.state;
    analogSignal[sigLight_SpeedControl] = mpcsOutput.lamps_state.speed_control.state;
    analogSignal[sigLight_VZ] = mpcsOutput.lamps_state.vz.state;

    // Правая панель сенсорных клавиш
    analogSignal[sigLight_EPT] = mpcsOutput.lamps_state.ept.state;
    analogSignal[sigLight_GS] = mpcsOutput.lamps_state.gs.state;
    analogSignal[sigLight_PV] = mpcsOutput.lamps_state.pv.state;
    analogSignal[sigLight_Whell_clean] = mpcsOutput.lamps_state.wheel_clean.state;
    analogSignal[sigLight_Saund1] = mpcsOutput.lamps_state.saund1.state;
    analogSignal[sigLight_Brake_release] = mpcsOutput.lamps_state.brake_release.state;
    analogSignal[sigLight_Test] = mpcsOutput.lamps_state.test.state;
    analogSignal[sigLight_Res_Purge] = mpcsOutput.lamps_state.res_purge.state;

    analogSignal[LS_G4] = 0;
    analogSignal[LS_G3] = 0;
    analogSignal[LS_G2] = 0;
    analogSignal[LS_G1] = 1;
    analogSignal[LS_Y] = 0;
    analogSignal[LS_RY] = 0;
    analogSignal[LS_R] = 0;
    analogSignal[LS_W] = 0;

    analogSignal[CU] = mpcsOutput.control_switch;
    analogSignal[EPK] = 0;

    analogSignal[WHEEL_1] = static_cast<float>(dir * wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[WHEEL_2] = static_cast<float>(dir * wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[WHEEL_3] = static_cast<float>(dir * wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[WHEEL_4] = static_cast<float>(dir * wheel_rotation_angle[3] / 2.0 / Physics::PI);
    analogSignal[WHEEL_5] = static_cast<float>(dir * wheel_rotation_angle[4] / 2.0 / Physics::PI);
    analogSignal[WHEEL_6] = static_cast<float>(dir * wheel_rotation_angle[5] / 2.0 / Physics::PI);

    analogSignal[MPSU_CURRENT_SPEED] = analogSignal[BLOK_VELOCITY];
    analogSignal[MPSU_CURRENT_SPEED_LIMIT] = analogSignal[BLOK_VELOCITY_CURRENT_LIMIT];
    analogSignal[MPSU_NEXT_SPEED_LIMIT] = analogSignal [BLOK_VELOCITY_NEXT_LIMIT];


    //Пробег электровоза
    analogSignal[MPSU_sTrinPos] = analogSignal[BLOK_RAILWAY_COORD];


    //Треугольник
    analogSignal[MPSU_sSeptoinSpeed] = static_cast<float>(kmb2->getVelocityLevel() * 100);


    analogSignal[MPSU_TM] = analogSignal[BLOK_TM_PRESS];
    analogSignal[MPSU_UR] = analogSignal[BLOK_UR_PRESS];
    analogSignal[MPSU_PM] = static_cast<float>(main_reservoir->getPressure());
    analogSignal[MPSU_TC] = analogSignal[BLOK_TC_PRESS];
    analogSignal[MPSU_VR] = static_cast<float>(spareReservoir->getPressure());


    //давление в КТО
//    analogSignal[MPSU_AST] = 1;


    //Сигнализаторы неотпуска в тормозных цилиндрах
    analogSignal[MPSU_TC1] = static_cast<float>(brake_mech[FWD_TROLLEY]->getBrakeCylinderPressure());
    analogSignal[MPSU_TC2] = static_cast<float>(brake_mech[MDL_TROLLEY]->getBrakeCylinderPressure());
    analogSignal[MPSU_TC3] = static_cast<float>(brake_mech[BWD_TROLLEY]->getBrakeCylinderPressure());


    //???  пренадлежит индикации состояния ЭПТ(кружочкам)
//    analogSignal[MPSU_I];

    //??? возможно пренадлежит индикации состояния ЭПТ(кружочкам)
    //analogSignal[MPSU_U] = ;

//    analogSignal[MPSU_EPT_ON_OFF] = static_cast<float>(ept_switch.getState());

    //род тока
    int cur_type = 0;
    for (auto pant = pantograph.begin(); pant != pantograph.end(); ++pant)
    {
        cur_type += ( (*pant) -> getCurrentKindOut()) ;
    }

    analogSignal[MPSU_CURRENT_TYPE] = cur_type;

    //??? уровень давления в АСТ
    //analogSignal[MPSU_P];


    //нагрузка ТПр
//    double pant_U;
//    for (auto td = pantograph.begin(); td != pantograph.end(); ++td)
//    {
//        pant_U = (*td)->getUout();
//    }

//    analogSignal[MPSU_ltct] = pant_U;


    // I и U в состоянии ЭПТ
    analogSignal[MPSU_outputI] = 0.2;
    analogSignal[MPSU_outputU] = 110;


       // Сигнал СОПТ!
    int pos_krm;

    if(krm->getHandlePosition() * 6.0f == 0)
    {
        pos_krm = 0;
    }
    else if (krm->getHandlePosition() * 6.0f == 1)
    {
        pos_krm = 1;
    }
    else if (krm->getHandlePosition() * 6.0f == 2 or krm->getHandlePosition() * 6.0f == 3)
    {
        pos_krm = 2;
    }
    else if (krm->getHandlePosition() * 6.0f == 4 or krm->getHandlePosition() * 6.0f == 5 or krm->getHandlePosition() * 6.0f == 6)
    {
        pos_krm = 3;
    }
    analogSignal[MPSU_numSwitch] = pos_krm;


    //???
//    analogSignal[MPSU_reversorDir] = ;

    // Напряжение U цу (индикация напряжения в цепи управления и АБ;)
    analogSignal[MPSU_controlVoltage] = 2;



    //индикатор состояния мотор-компрессора
    analogSignal[MPSU_motorCompressor1] = mpcsOutput.toggleSwitchMK[0] ? 1 : 2;
    analogSignal[MPSU_motorCompressor2] = mpcsOutput.toggleSwitchMK[1] ? 1 : 2;


    // Уровни тяги!
    //Фактическая
    double trac_force = 0.0;
    double max_force = 0.0;
    for (auto td = tractionDrive.begin(); td != tractionDrive.end(); ++td)
    {
        trac_force += ( (*td)->getTorque(0) + (*td)->getTorque(1) ) * 2.0 / wheel_diameter;
        max_force += 4.0 * (*td)->getMotorMaxTorque() / wheel_diameter;
    }
    analogSignal[MPSU_scaleSetTraction] = static_cast<float>(trac_force * 100.0 / max_force);
    //заданная
    analogSignal[MPSU_scaleActualTraction] = static_cast<float>(kmb2->getTractionLevel() * 100);

    //режим управления
    analogSignal[MPSU_CONTROL_MODE] = mpcsOutput.control_mode;

    //направление движения
    int rev_dir;
    if (kmb2->getReverseState() < 0)
    {
        rev_dir = 1;
    }

    if (kmb2->getReverseState() > 0)
    {
        rev_dir = 0;
    }

    analogSignal[MPSU_DIRECTION_TRAVEL] = rev_dir;


    //напряжение контактной сети
    analogSignal[MPSU_CONTACT_VOLTAGE] = static_cast<float>(Ukr_in / 1000.0);

    //Вентилятор
    analogSignal[MPSU_FAN_ANGLE] += static_cast<float>(10.0 * dt);





    //???
    //    analogSignal[MPSU_forces] = static_cast<float>(trac_force * 100.0 / max_force);
    //    analogSignal[MPSU_refForces] = static_cast<float>(kmb2->getTractionLevel() * 100);
}
