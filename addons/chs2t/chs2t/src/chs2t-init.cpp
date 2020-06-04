#include    "chs2t.h"

#include    <QDir>

#include    "Journal.h"

//------------------------------------------------------------------------------
// Инициализация токоприемников
//------------------------------------------------------------------------------
void CHS2T::initPantographs()
{
    Journal::instance()->info("Init pantographs");

    for (size_t i = 0; i < NUM_PANTOGRAPHS; ++i)
    {
        pantographs[i] = new Pantograph();
        pantographs[i]->read_custom_config(config_dir + QDir::separator() + "pantograph");
        pantographs[i]->setUks(Uks);
        connect(pantographs[i], &Pantograph::soundPlay, this, &CHS2T::soundPlay);
    }

    for (size_t i = 0; i < NUM_PANTOGRAPHS; ++i)
    {
        pantoSwitcher[i] = new Switcher(Q_NULLPTR, 0, 4);
    }

    pantoSwitcher[0]->setKeyCode(KEY_I);
    pantoSwitcher[1]->setKeyCode(KEY_O);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initBrakesMech()
{
    Journal::instance()->info("Init brake mechanics");

    brakesMech[0] = new CHS2tBrakeMech();
    brakesMech[0]->read_custom_config(config_dir + QDir::separator() + "brake-mech-front");

    brakesMech[1] = new CHS2tBrakeMech();
    brakesMech[1]->read_custom_config(config_dir + QDir::separator() + "brake-mech-back");
}

//------------------------------------------------------------------------------
// Инициализация быстродействующего выключателя
//------------------------------------------------------------------------------
void CHS2T::initFastSwitch()
{
    Journal::instance()->info("Init fast switch");

    bv = new ProtectiveDevice();
    bv->read_custom_config(config_dir + QDir::separator() + "bv");

    fastSwitchSw = new Switcher(Q_NULLPTR, KEY_P, 4);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initProtection()
{
    Journal::instance()->info("Init protection devices");

    overload_relay = new OverloadRelay();
    overload_relay->read_custom_config(config_dir + QDir::separator() + "1RPD6");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initBrakesControl(QString module_path)
{
    Journal::instance()->info("Init brake control devices");

    brakeCrane = loadBrakeCrane(module_path + QDir::separator() + "krm395");
    brakeCrane->read_config("krm395");
    connect(brakeCrane, &BrakeCrane::soundPlay, this, &CHS2T::soundPlay);
    connect(brakeCrane, &BrakeCrane::soundSetVolume, this, &CHS2T::soundSetVolume);

    locoCrane = loadLocoCrane(module_path + QDir::separator() + "kvt254");
    locoCrane->read_config("kvt254");

    handleEDT = new HandleEDT();
    handleEDT->read_custom_config(config_dir + QDir::separator() + "handle-edt");
    handleEDT->setBrakeKey(KEY_Period);
    handleEDT->setReleaseKey(KEY_Comma);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initAirSupplySubsystem()
{
    Journal::instance()->info("Init air suplly subsystem");

    mainReservoir = new Reservoir(1);
    spareReservoir = new Reservoir(0.078);
    brakeRefRes = new Reservoir(0.004);

    for (size_t i = 0; i < motor_compressor.size(); ++i)
    {
        motor_compressor[i] = new DCMotorCompressor();
        motor_compressor[i]->read_custom_config(config_dir + QDir::separator() + "motor-compressor");
        connect(motor_compressor[i], &DCMotorCompressor::soundSetPitch, this, &CHS2T::soundSetPitch);

        motor_compressor[i]->setSoundName(QString("Motor_Compressor%1").arg(i+1));

        mk_switcher[i] = new Switcher(Q_NULLPTR, 0, 4);
    }

    mk_switcher[0]->setKeyCode(KEY_7);
    mk_switcher[1]->setKeyCode(KEY_8);

    pressReg = new PressureRegulator();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initTractionControl()
{
    Journal::instance()->info("Init traction control");

    km21KR2 = new Km21KR2();

    stepSwitch = new StepSwitch();
    stepSwitch->read_custom_config(config_dir + QDir::separator() + "step-switch");

    motor = new Motor();
    motor->setCustomConfigDir(config_dir);
    motor->read_custom_config(config_dir + QDir::separator() + "AL-4846dT");
    connect(motor, &Motor::soundSetVolume, this, &CHS2T::soundSetVolume);
    connect(motor, &Motor::soundSetPitch, this, &CHS2T::soundSetPitch);

    puskRez = new PuskRez;
    puskRez->read_custom_config(config_dir + QDir::separator() + "puskrez");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initBrakesEquipment(QString module_path)
{
    Journal::instance()->info("Init brakes equipment");

    dako = new Dako();
    dako->read_custom_config(config_dir + QDir::separator() + "dako");

    electroAirDistr = loadElectroAirDistributor(module_path + QDir::separator() + "evr305");
    electroAirDistr->read_config("evr305");

    airDistr = loadAirDistributor(module_path + QDir::separator() + "vr242");
    airDistr->read_config("vr242");

    autoTrainStop = loadAutoTrainStop(module_path + QDir::separator() + "epk150");
    autoTrainStop->read_config("epk150");
    connect(autoTrainStop, &AutoTrainStop::soundSetVolume, this, &CHS2T::soundSetVolume);

    zpk = new SwitchingValve();
    zpk->read_config("zpk");

    rd304 = new PneumoReley();
    rd304->read_config("rd304");

    pnSplit = new PneumoSplitter();
    pnSplit->read_config("pneumo-splitter");

    airSplit = new PneumoSplitter();
    airSplit->read_config("pneumo-splitter");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initEDT()
{
    Journal::instance()->info("Init electrical brake system");

    generator = new Generator();
    generator->setCustomConfigDir(config_dir);
    generator->read_custom_config(config_dir + QDir::separator() + "AL-4846dT");
    connect(generator, &Generator::soundSetPitch, this, &CHS2T::soundSetPitch);
    connect(generator, &Generator::soundSetVolume, this, &CHS2T::soundSetVolume);

    pulseConv = new PulseConverter();

    BrakeReg = new BrakeRegulator();
    BrakeReg->read_custom_config(config_dir + QDir::separator() + "brake-regulator");

    EDT_timer.setTimeout(3.0);
    EDT_timer.firstProcess(false);
    connect(&EDT_timer, &Timer::process, this, &CHS2T::enableEDT);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initOtherEquipment()
{
    Journal::instance()->info("Init whistle and typhoid");

    horn = new CHS2tHorn();
    connect(horn, &CHS2tHorn::soundPlay, this, &CHS2T::soundPlay);
    connect(horn, &CHS2tHorn::soundStop, this, &CHS2T::soundStop);

    speed_meter = new SL2M();
    speed_meter->read_custom_config(config_dir + QDir::separator() + "3SL-2M");
    connect(speed_meter, &SL2M::soundSetVolume, this, &CHS2T::soundSetVolume);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initSupportEquipment()
{
    Journal::instance()->info("Init support equipment");

    relValve = new ReleaseValve();
    relValve->read_custom_config(config_dir + QDir::separator() + "release-valve");

    motor_fan_ptr = new DCMotorFan();
    motor_fan_ptr->read_custom_config(config_dir + QDir::separator() + "dc-motor-fan");
    motor_fan_ptr->setSoundName("PTR_fan");

    for (size_t i = 0; i < motor_fan.size(); ++i)
    {
        motor_fan[i] = new DCMotorFan();
        motor_fan[i]->read_custom_config(config_dir + QDir::separator() + "motor-fan");
        connect(motor_fan[i], &DCMotorFan::soundSetPitch, this, &CHS2T::soundSetPitch);
        motor_fan[i]->setSoundName(QString("Motor_Fan%1").arg(i+1));
    }

    motor_fan_switcher = new Switcher(Q_NULLPTR, KEY_F, 3);

    connect(motor_fan_ptr, &DCMotorFan::soundSetPitch, this, &CHS2T::soundSetPitch);

    blinds = new Blinds();
    blinds->read_custom_config(config_dir + QDir::separator() + "blinds");

    blindsSwitcher = new Switcher(Q_NULLPTR, KEY_G, 5);

    energy_counter = new EnergyCounter();
    energy_counter->read_custom_config(config_dir + QDir::separator() + "energy-counter");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initModbus()
{
    Journal::instance()->info("Init modbus");

    QString modbusCfgDir = config_dir + QDir::separator() + "modbus";

    TM_manometer = new PhysToModbus();
    TM_manometer->load((modbusCfgDir + QDir::separator() + "manometer-TM").toStdString());

    UR_manometer = new PhysToModbus();
    UR_manometer->load((modbusCfgDir + QDir::separator() + "manometer-UR").toStdString());

    ZT_manometer = new PhysToModbus();
    ZT_manometer->load((modbusCfgDir + QDir::separator() + "manometer-ZT").toStdString());

    GR_manometer = new PhysToModbus();
    GR_manometer->load((modbusCfgDir + QDir::separator() + "manometer-GR").toStdString());

    TC_manometer = new PhysToModbus();
    TC_manometer->load((modbusCfgDir + QDir::separator() + "manometer-TC").toStdString());

}

//------------------------------------------------------------------------------
// Инициализация регистратора
//------------------------------------------------------------------------------
void CHS2T::initRegistrator()
{
    Journal::instance()->info("Init registraion subsystem");

    reg = nullptr;
    reg = new Registrator("../charts/energy", 1.0, Q_NULLPTR);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CHS2T::initBrakeDevices(double p0, double pTM, double pFL)
{
    Journal::instance()->info("Init brake devices: callback form TrainEngine");

    charging_press = p0;

    mainReservoir->setY(0, pFL);
    spareReservoir->setY(0, charging_press);
    brakeCrane->init(pTM, pFL);
    locoCrane->init(pTM, pFL);
    airDistr->init(pTM, pFL);
    autoTrainStop->init(pTM, pFL);
}
