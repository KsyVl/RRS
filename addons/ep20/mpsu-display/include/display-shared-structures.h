//17/01/2018
#ifndef DISPLAY_SHARED_STRUCTURES_H
#define DISPLAY_SHARED_STRUCTURES_H

#include <QByteArray>

#include <qglobal.h>
#include <cstring>

#include "sapsan-shared-data.h"
#include "sapsan-shared-structures.h"
#include "display-shared-data.h"
#include "small-bitset.h"


// ---------------------------------------------------------------------------
//
//      Базовая структура для структур экранов
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct screen_data_t
 * \brief Базовая структура всех структур для экранов
 */
struct screen_data_t
{
    screen_data_t()
    {

    }
};  // screen_data_t
#pragma pack(pop)





//-----------------------------------------------------------------------------
//  Перечислители для верхней строки состояния
//-----------------------------------------------------------------------------
/*!
 * \enum cabinNumEnum
 * \brief Перечислитель для активной кабины
 */
enum CabinNumEnum
{
    first,
    last
};

/*!
 * \enum DirectionTravelEnum
 * \brief Перечислитель для направления движения
 */
enum DirectionTravelEnum
{
    forwardDT,
    backwardDT
};

/*!
 * \enum ControlModeEnum
 * \brief Перечислитель для режима управления
 */
enum ControlModeEnum
{
    manualControl,
    automaticControl,
    autoDrive
};

/*!
 * \enum TractionModeIndicationEnum
 * \brief Перечислитель для индикации задания режима тяги или ЭТ
 */
enum TractionModeIndicationEnum
{
    traction,
    recuperation,
    reostat,
    disassembled
};

/*!
 * \enum TypeBrakeEnum
 * \brief Перечислитель для основного типа тормоза
 */
enum TypeBrakeEnum
{
    PT,
    EPT
};

/*!
 * \enum CurrentTypeEnum
 * \brief Род тока
 */
enum CurrentTypeEnum
{
    notDetermined,   // не определен
    AC,              // переменный ток
    DC               // постоянный ток
};


// ---------------------------------------------------------------------------
//
//      Стркутура данных верхней строки состояния
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct status_bar_data_t
 * \brief Стркутура данных верхней строки состояния
 */
struct status_bar_data_t
{
    CabinNumEnum cabinNum;                             // номер активной кабины
    DirectionTravelEnum directionTravel;                // направление движения
    ControlModeEnum controlMode;                        // режим управления
    TractionModeIndicationEnum tractionModeIndication;  // индикация задания режима тяги или ЭТ
    TypeBrakeEnum typeBrake;                            // тип основного тормоза
    CurrentTypeEnum currentType;                        // род тока
    double contactVoltage;                              // напряжение контактной сети

    status_bar_data_t()
        : cabinNum(CabinNumEnum::first)
        , directionTravel(DirectionTravelEnum::forwardDT)
        , controlMode(ControlModeEnum::manualControl)
        , tractionModeIndication(TractionModeIndicationEnum::disassembled)
        , typeBrake(TypeBrakeEnum::PT)
        , currentType(CurrentTypeEnum::notDetermined)
        , contactVoltage(0.0)
    {

    }

};  // status_bar_data_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура данных статусной строки кадра
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct status_bar_bottom_data_t
 * \brief Стркутура данных статусной строки кадра
 */
struct status_bar_bottom_data_t
{
    int fanAngle;           // угол "вентилятора"
    bool AST;               //
    bool TC;                //
    char curModelData[9];   // текущая модельная дата
    char curModelTime[9];   // текущее модельное время

    status_bar_bottom_data_t()
        : fanAngle(0)
        , AST(false)
        , TC(false)
    {
        strcpy(curModelData, "00.00.00");
        strcpy(curModelTime, "00:00:00");
    }

};  // status_bar_bottom_data_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура для передачи значений в информационную строку
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct condition_t
 * \brief Структура для передачи значений в информационную строку
 */
struct condition_t
{
    /// Активность АУДиТ
    bool auditActive;

    /// Скорость для вывода в ячейку 1 (Аудит)
    quint16 refSpeed;

    /// Индексы картинок в информационной строке
    ConditionLine::CellsIndexes cells;

    /// Индекс неисправной системы
    quint16 brokenSysIndex;


    condition_t()
        : auditActive(false)
        , refSpeed(0)
        , cells{}
        , brokenSysIndex(0)
    {

    }

};  // condition_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура тяговых/тормозных показателей Основного экрана
//
// ---------------------------------------------------------------------------


enum stateWorkTC
{
    notConnectChanel, // отсутствие связи с каналом (белый цвет)
    chanelOutage, // выход канала из строя (красный)
    block, // перегрев тягового двигателя, либо ЭТ или блокировано электрическое торможение (желтый)
    norm
};


enum PantographNumEnum
{
    forward,
    backward
};

// номера индикаторов положения переключателей крана машиниста
enum NumIndicatorSwitchPosEnum
{
    overcharging = 0,
    release = 1,
    overlap = 2,
    braking = 3,
    outPosition = -1
};

// состояние мотор-компрессора
enum MotorCompressorEnum
{
    isolated,
    on,
    off
};


#pragma pack(push, 1)
struct pantograph_t
{
    PantographNumEnum num;
    bool ready;
    bool active;

    pantograph_t()
        : num(PantographNumEnum::forward)
        , ready(false)
        , active(false)
    {

    }
};
#pragma pack(pop)


#pragma pack(push, 1)
struct load_traction_converter_t
{
    bool stateGVBV;
    CurrentTypeEnum currentType;
    pantograph_t pantograph[2];
    stateWorkTC stateTC[3];
    bool stateMotor[6];
    int motorVal[6];

    load_traction_converter_t()
        : stateGVBV(false)
        , currentType(CurrentTypeEnum::notDetermined)
        , pantograph{}
        , stateTC{stateWorkTC::norm, stateWorkTC::norm, stateWorkTC::norm}
        , stateMotor{false, false, false, false, false, false}
        , motorVal{0}
    {

    }
};
#pragma pack(pop)


#pragma pack(push, 1)
/*!
 * \struct force_values_t
 * \brief Стркутура тяговых/тормозных показателей Основного экрана
 */
struct screen_main_t : screen_data_t
{
    // спидометр
    double  sCurSpeed;
    int     sCurSpeedLimit;
    int     sNextSpeedLimit;
    int     sSetpointSpeed;
    double  sTrainPos;

    // шкала тяги
    int scaleSetTraction;
    int scaleActualTraction;

    // напряжение в цепи управления и АБ
    int controlVoltage;

    // ток и напряжение на выходе источника питания ЭПТ
    double  outputI;
    int     outputU;
    bool updateStateEPT_light1;
    bool updateStateEPT_light2;
    bool updateStateEPT_light3;

    //
    load_traction_converter_t ltct;

    //
    NumIndicatorSwitchPosEnum numSwitch;

    //
    bool TC1;
    bool TC2;
    bool TC3;
    double pressureUR;
    double pressureTM;
    double pressurePM;
    double pressureTC;
    double pressureVR;
    double pressureAST;
    MotorCompressorEnum motorCompressor1;
    MotorCompressorEnum motorCompressor2;




    double U;               ///< Напряжение
    double I;               ///< Ток
    double P;               ///< Мощность

    qint8  refForces[4];    ///< Заданные усилия
    qint8  forces[4];       ///< Реальные усилия

    qint8 reversorDir;      ///< Направление реверсора

    screen_main_t()
        : sCurSpeed(0.0)
        , sCurSpeedLimit(0)
        , sNextSpeedLimit(0)
        , sSetpointSpeed(0)
        , sTrainPos(0.0)
        , scaleSetTraction(0)
        , scaleActualTraction(0)
        , controlVoltage(0)
        , outputI(0)
        , outputU(0)
        , ltct()
        , numSwitch(NumIndicatorSwitchPosEnum::outPosition)
        , TC1(false)
        , TC2(false)
        , TC3(false)
        , pressureUR(0.0)
        , pressureTM(0.0)
        , pressurePM(0.0)
        , pressureTC(0.0)
        , pressureVR(0.0)
        , pressureAST(0.0)
        , motorCompressor1(MotorCompressorEnum::isolated)
        , motorCompressor2(MotorCompressorEnum::isolated)


        , U(0.0)
        , I(0.0)
        , P(0.0)
        , refForces{}
        , forces{}
        , reversorDir(0)

    {

    }

};  // screen_main_t
#pragma pack(pop)



// цвет оборудования
enum ColorDeviceEnum
{
    green,
    gray,
    red,
    orange
};

enum FanStateEnum
{
    fsOn,       // вкл
    fsOff,      // выкл
    fsDefect    // неисправен
};


struct fan_t
{
    FanStateEnum state;
    //int angle/speed
    int speed;

    fan_t()
        : state(FanStateEnum::fsOff)
        , speed(0)
    {

    }
};

#pragma pack(push, 1)
/*!
 * \struct screen_diagnostics_t
 * \brief Стркутура для экрана диагностики
 */
struct screen_diagnostics_t : screen_data_t
{
    pantograph_t pantograph[4];

    ColorDeviceEnum deviceBTR[6];
    ColorDeviceEnum deviceCab1;
    ColorDeviceEnum deviceCab2;
    ColorDeviceEnum deviceBUGS;
    ColorDeviceEnum deviceTPr1;
    ColorDeviceEnum deviceTPr2;
    ColorDeviceEnum deviceTPr3;
    ColorDeviceEnum deviceBUE;
    ColorDeviceEnum deviceBARS;
    ColorDeviceEnum deviceMK1;
    ColorDeviceEnum deviceMK2;
    ColorDeviceEnum deviceBD;
    ColorDeviceEnum deviceAB;
    ColorDeviceEnum deviceVPr;
    ColorDeviceEnum deviceIPCU;
    ColorDeviceEnum deviceTTr;
    ColorDeviceEnum deviceKTO;

    fan_t fanMV11;
    fan_t fanMV12;
    fan_t fanMV13;
    fan_t fanMV14;
    fan_t fanMV15;
    fan_t fanMV16;
    fan_t fanMV21;
    fan_t fanMV22;
    fan_t fanMV23;
    fan_t fanMV31;
    fan_t fanMV32;

    screen_diagnostics_t()
        : pantograph{}

        , deviceBTR{ColorDeviceEnum::gray}
        , deviceCab1(ColorDeviceEnum::gray)
        , deviceCab2(ColorDeviceEnum::gray)
        , deviceBUGS(ColorDeviceEnum::gray)
        , deviceTPr1(ColorDeviceEnum::gray)
        , deviceTPr2(ColorDeviceEnum::gray)
        , deviceTPr3(ColorDeviceEnum::gray)
        , deviceBUE(ColorDeviceEnum::gray)
        , deviceBARS(ColorDeviceEnum::gray)
        , deviceMK1(ColorDeviceEnum::gray)
        , deviceMK2(ColorDeviceEnum::gray)
        , deviceBD(ColorDeviceEnum::gray)
        , deviceAB(ColorDeviceEnum::gray)
        , deviceVPr(ColorDeviceEnum::gray)
        , deviceIPCU(ColorDeviceEnum::gray)
        , deviceTTr(ColorDeviceEnum::gray)
        , deviceKTO(ColorDeviceEnum::gray)

        , fanMV11{}
        , fanMV12{}
        , fanMV13{}
        , fanMV14{}
        , fanMV15{}
        , fanMV16{}
        , fanMV21{}
        , fanMV22{}
        , fanMV23{}
        , fanMV31{}
        , fanMV32{}
    {

    }

};  // screen_diagnostics_t
#pragma pack(pop)



// состояние крышевого разъединителя
enum DisconnectorEnum
{
    open,       ///< разомкнут
    closed,     ///< замкнут
    undefined   ///< неопределенное
};

// состояние переключателя
enum KeyStateEnum
{
    ks_open,        ///< разомкнут
    ks_closed,      ///< замкнут
    ks_readyClosed, ///< готов к замыканию
    ks_fail         ///< состояние сбоя
};



#pragma pack(push, 1)
/*!
 * \struct screen_power_circuit_t
 * \brief Стркутура для экрана силовой схемы
 */
struct screen_power_circuit_t : screen_data_t
{
    double I;
    double U;
    pantograph_t pantograph[4];
    DisconnectorEnum roofKeyQS1;
    DisconnectorEnum roofKeyQS2;
    DisconnectorEnum prt;
    DisconnectorEnum depo;
    KeyStateEnum GV;
    KeyStateEnum BV;
    bool groundingGV;

    screen_power_circuit_t()
        : I(0.0)
        , U(0.0)
        , pantograph{}
        , roofKeyQS1(DisconnectorEnum::undefined)
        , roofKeyQS2(DisconnectorEnum::undefined)
        , prt(DisconnectorEnum::undefined)
        , depo(DisconnectorEnum::undefined)
        , GV(KeyStateEnum::ks_open)
        , BV(KeyStateEnum::ks_open)
        , groundingGV(false)
    {

    }

};  // screen_power_circuit_t
#pragma pack(pop)



#pragma pack(push, 1)
/*!
 * \struct screen_pneumatics_t
 * \brief Стркутура для экрана пневматики (КТО)
 */
struct screen_pneumatics_t : screen_data_t
{
    double UR;
    double DD;
    double DD1_BTO;
    double DD2_BTO;
    double DD3_BTO;
    double DD4_BTO;
    double DD5_BTO;
    double DD6_BTO;
    double DD1_BIO;
    double DD2_BIO;
    double DD3_BIO;
    double DD4_BIO;
    double DD5_BIO;
    MotorCompressorEnum motorCompressor1;
    MotorCompressorEnum motorCompressor2;

    screen_pneumatics_t()
        : UR(0.0)
        , DD(0.0)
        , DD1_BTO(0.0)
        , DD2_BTO(0.0)
        , DD3_BTO(0.0)
        , DD4_BTO(0.0)
        , DD5_BTO(0.0)
        , DD6_BTO(0.0)
        , DD1_BIO(0.0)
        , DD2_BIO(0.0)
        , DD3_BIO(0.0)
        , DD4_BIO(0.0)
        , DD5_BIO(0.0)
        , motorCompressor1(MotorCompressorEnum::isolated)
        , motorCompressor2(MotorCompressorEnum::isolated)
    {

    }

};  // screen_pneumatics_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура данных экрана переключения системы питания
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct screen_change_system_t
 * \brief Стркутура
 */
struct screen_change_system_t : screen_data_t
{
    bool canChangeSystem;   ///< Возможность смены типа силовой схемы
    quint8 reqPowerType;    ///< Заданный тип силовой схемы

    screen_change_system_t()
        : canChangeSystem(false)
        , reqPowerType(PowerSystemData::PT_DC)
    {

    }

};  // screen_change_system_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура данных экрана переключения системы питания
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct screen_change_system_t
 * \brief Стркутура
 */
struct screen_audit_t : screen_data_t
{
    ///
    SpeedRegulatorData::SpeedRegulatorMode curMode;

    ///
    SpeedRegulatorData::SpeedRegulatorMode refMode;


    ///
    screen_audit_t()
    {

    }

};  // screen_audit_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct screen_battery_t
 * \brief Стркутура напряжений в аккумуляторных батареях
 */
struct screen_battery_t : screen_data_t
{
    quint8 U1;  ///< Напряжение в батарее главной секции
    quint8 U2;  ///< Напряжение в батарее второстепенной секции

    screen_battery_t()
        : U1(60u)
        , U2(60u)
    {

    }
};  // screen_battery_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Стркутура данных экрана состояния тормозной системы
//
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
/*!
 * \struct brakes_status_t
 * \brief Стркутура данных экрана состояния тормозной системы поезда
 */
struct brakes_status_t : screen_data_t
{
    struct table_t
    {
        bits_t<24> workingBrakes;
        bits_t<24> readyBrakes;
        bits_t<2> kompressors;

        inline bool operator ==(table_t &b)
        {
            return ( (this->workingBrakes == b.workingBrakes) &&
                     (this->readyBrakes == b.readyBrakes) &&
                     (this->kompressors == b.kompressors) );
        }
    };

    double pressureTM1;
    double pressureTM10;
    double pressurePM1;
    double pressurePM10;
    table_t table;

    brakes_status_t()
        : pressureTM1(0.0)
        , pressureTM10(0.0)
        , pressurePM1(0.0)
        , pressurePM10(0.0)
    {

    }

};  // brakes_status_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура значений давления в тормозных цилиндрах
//
// ---------------------------------------------------------------------------

constexpr int CYLINDERS_COUNT = 40; // FIXME - количество цилиндров должно быть суперглобальным для всего проекта

#pragma pack(push, 1)
/*!
 * \struct cylinders_pressure_t
 * \brief Структура значений давления в тормозных цилиндрах
 */
struct cylinders_pressure_t : screen_data_t
{
    double pressures[CYLINDERS_COUNT];  ///< Давление в торм. цилиндрах

    cylinders_pressure_t()
        : pressures{}
    {

    }
};
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура состояния силовой схемы всего состава
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct power_system_t
 * \brief Структура состояния силовой схемы
 */
struct power_system_t : screen_data_t
{
    /*!
     * \name Флаги состояний и блокировки устройств секций
     * бит 0  - Токопр. постоянного тока 1
     * бит 1  - Токопр. постоянного тока 2
     * бит 2  - Токопр. переменного тока
     * бит 3  - Быстродейсвтующий выключатель
     * бит 4  - Главный выключатель
     * бит 5  - Крышевой разъединитель
     * бит 6  - Тяговый преобразователь 1
     * бит 7  - Тяговый преобразователь 2
     * бит 8  - ПСН
     * бит 9  - Первый ПСН сдвоенного контейнера
     * бит 10 - Второй ПСН сдвоенного контейнера
     */
    ///@{
    status_feedback_t primary;
    status_feedback_t secondary;
    ///@}

};  // power_system_t
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура данных панели
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct panel_k_diagnostic_t
 * \brief Структура диагностических данных от панелей
 */
template<size_t flagsCount, size_t uintCount, size_t intCount>
struct panel_diagnostic_t : screen_data_t
{
    bits_t<flagsCount> flags; ///< Биты состояния

    quint32 uintFields[uintCount]; ///< Массив беззнаковых данных
    qint32  intFields[intCount]; ///< Массив знаковых данных

    panel_diagnostic_t()
        : uintFields{}
        , intFields{}
    {

    }
};
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура всех диагностических данных
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct all_diagnostic_data_t
 * \brief Структура всех диагностических данных
 */
struct diagnostic_screen_t : screen_data_t
{
    double modelTime; ///< Модельное время


    /*!
      \name Параметры контроллера тяги/торможения
      бит 0  - connected
      бит 1  - ready
      бит 2  - isEmergencyBrake
      бит 3  - isPropBrake
      бит 4  - isZero
      intFields[0] - getPosition
      intFields[1] - getEncoderPulses
      */
    ///@{
    panel_diagnostic_t<5,1,2> traction_controller;
    ///@}


    /*!
      \name Параметры котроллера пневматического тормоза
      бит 0  - connected
      бит 1  - ready
      бит 2  - isRelease
      бит 3  - isEmergencyBrake
      uintFields[0] - getPosition
      uintFields[1] - getEncoderPulses
      */
    ///@{
    panel_diagnostic_t<4,2,1> brake_controller;
    ///@}


    /*!
      \name Параметры панели G
      бит 0  - connected
      бит 1  - ready
      бит 2  - isDetachTrains
      бит 3  - isBufferLights1
      бит 4  - isBufferLights3
      бит 5  - isNeutralInsert
      бит 6  - isBatteryOff
      бит 7  - isCabineUnlock
      */
    ///@{
    panel_diagnostic_t<8,1,1> panel_g;
    ///@}


    /*!
      \name Параметры панели I
      бит 0  - connected
      бит 1  - ready
      бит 2  - isVigilanceButton
      бит 3  - isWhistle
      бит 4  - isTiphoid
      бит 5  - isPassAnswer
      бит 6  - isAnswerCall
      бит 7  - isAlarm
      бит 8  - isCabineLink
      */
    ///@{
    panel_diagnostic_t<9,1,1> panel_i;
    ///@}


    /*!
      \name Параметры панели J входы
      бит 0  - connected
      бит 1  - ready
      бит 2  - isParkingBrakeRelease
      бит 3  - isParkingBrakeBrake
      бит 4  - isRightDoorsUnlock
      бит 5  - isLeftDoorsUnlock
      бит 6  - CloseDoors
      бит 7  - isHighPlatform
      бит 8  - isLowPlatform
      бит 9  - isDriverHeat
      бит 10 - isDriverAssistentHeat
      бит 11 - isAirConditionOff
      бит 12 - isEmergencyStop
      */
    ///@{
    panel_diagnostic_t<13,1,1> panel_j_in;
    ///@}


    /*!
      \name Параметры панели J выходы
      бит 0  - connected
      бит 1  - ready
      */
    ///@{
    panel_diagnostic_t<2,1,1> panel_j_out;
    ///@}


    /*!
      \name Параметры панели K
      бит 0  - connected
      бит 1  - ready
      бит 2  - isPantographTop
      бит 3  - isPantographDown
      бит 4  - isMainSwitchOn
      бит 5  - isMainSwitchOff
      бит 6  - isReversorForward
      бит 7  - isReversorBackward
      бит 8  - isMotionUnlock
      intFields[0] - направление реверсора
      */
    ///@{
    panel_diagnostic_t<9,1,1> panel_k;
    ///@}


    /*!
      \name Параметры панели L
      бит 0  - connected
      бит 1  - ready
      бит 2  - isBrakeDiskClearing
      бит 3  - isEmergencyBrakeLock
      бит 4  - isIndicatorsCheck
      бит 5  - isCabineLightLow
      бит 6  - isCabineLightHigh
      */
    ///@{
    panel_diagnostic_t<7,1,1> panel_l;
    ///@}


    /*!
      \name Параметры панели m
      бит 0  - connected
      бит 1  - ready
      бит 2  - isWhistle
      бит 3  - isTiphoid
      бит 4  - isSpotLightLow
      бит 5  - isSpotLightHigh
      бит 6  - isVigilanceButton
      бит 7  - isWasherOn
      бит 8  - isWiperSpeed1
      бит 9  - isWiperSpeed3
      бит 10 - isWiperReg1
      бит 11 - isWiperReg3
      бит 12 - isWindshieldHeatingOn
      */
    ///@{
    panel_diagnostic_t<13,1,1> panel_m;
    ///@}


    /*!
      \name Параметры локомотивных светофоров
      бит 0  - connected
      бит 1  - ready
      uintFields[0] - число шагов ШД красной стрелки
      uintFields[1] - число шагов ШД черной стрелки
      */
    ///@{
    panel_diagnostic_t<2,1,1> traffic_light;
    ///@}


    /*!
      \name Параметры манометра ТЦ1/ТЦ2
      бит 0  - connected
      бит 1  - ready
      uintFields[0] - число шагов ШД красной стрелки
      uintFields[1] - число шагов ШД черной стрелки
      */
    ///@{
    panel_diagnostic_t<2,2,1> manometer_tpm;
    panel_diagnostic_t<2,2,1> manometer_tc12;
    ///@}


    diagnostic_screen_t()
        : modelTime(0.0)
    {

    }
};
#pragma pack(pop)



// ---------------------------------------------------------------------------
//
//      Структура для передачи всех данных от сервера
//
// ---------------------------------------------------------------------------

#pragma pack(push, 1)
/*!
 * \struct all_data_t
 * \brief Структура для передачи всех данных от сервера
 */
struct display_data_t
{
    /// Текущий тип силовой схемы
    PowerSystemData::PowerType  powerType;

    /// Данные строки состояния
    status_bar_data_t           status_bar;

    /// Данные статусной строки кадра
    status_bar_bottom_data_t    status_bar_bottom;

    /// Даные информациооной строки
    condition_t                 condition_line;

    /// Данные главного экрана
    screen_main_t               screen_main;

    /// Даные для экрана диагностики
    screen_diagnostics_t        screen_diagnostics;

    /// Данные для экрана силовой схемы
    screen_power_circuit_t      screen_power_circuit;

    /// Данные для экрана пневматики (КТО)
    screen_pneumatics_t         screen_pneumatics;

    /// Данные экрана смены типа силовой схемы
    screen_change_system_t      screen_change_system;

    ///
    screen_audit_t              screen_audit;

    /// Данные экрана батарей
    screen_battery_t            screen_battery;

    /// Данные экрана тормозной системы
    brakes_status_t             brakes_status;

    /// Давления тормозных цилиндрах
    cylinders_pressure_t        cylinders_pressure;

    /// Данные силовой схемы
    power_system_t              power_system;

    /// Данные экрана диагностики
    diagnostic_screen_t         diagnostic;

    display_data_t()
        : powerType(PowerSystemData::PT_DC)
    {

    }

    /// Преобразовать "себя" в массив байт
    QByteArray toByteArray()
    {
        QByteArray tmpArr(sizeof(*this), Qt::Uninitialized);
        memcpy(tmpArr.data(), static_cast<void*>(this), sizeof(*this));
        return tmpArr;
    }

    /// Скопировтаь "в себя" данные из массива байт
    void fromByteArray(QByteArray arr)
    {
        if (static_cast<size_t>(arr.size()) == sizeof(*this))
        {
            memcpy(static_cast<void*>(this), arr.data(), sizeof(*this));
        }
    }
};
#pragma pack(pop)






// ---------------------------------------------------------------------------
//
//      Стркутура
//
// ---------------------------------------------------------------------------
//#pragma pack(push, 1)
///*!
// * \struct
// * \brief Стркутура
// */
//struct  : screen_data_t
//{

//};  //
//#pragma pack(pop)


#endif // DISPLAY_SHARED_STRUCTURES_H
