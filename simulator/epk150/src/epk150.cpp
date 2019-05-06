#include    "epk150.h"

/*
 *  Y[0] - усилие от катушки ЭПК
 *  Y[1] - давление в камере выдержки времени
 *  Y[2] - давление над срывным клапаном
 */

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AutoTrainStopEPK150::AutoTrainStopEPK150(QObject *parent)
    : AutoTrainStop(parent)
    , T1(0.1)
    , pd(0.2)
    , pk(0.4)
    , p_key(10.0)
    , ps1(0.15)
    , ps2(0.15)
    , V1(1e-4)
    , V2(1e-3)
    , emergencyRate(0.0)
    , p1_rate(0.0)
{
    std::fill(K.begin(), K.end(), 0.0);
    std::fill(k.begin(), k.end(), 0.0);

    DebugLog *log = new DebugLog("epk150.txt");
    connect(this, &AutoTrainStopEPK150::DebugPrint, log, &DebugLog::DebugPring);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
AutoTrainStopEPK150::~AutoTrainStopEPK150()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double AutoTrainStopEPK150::getEmergencyBrakeRate() const
{
    return emergencyRate;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTrainStopEPK150::ode_system(const state_vector_t &Y,
                                     state_vector_t &dYdt,
                                     double t)
{
    Q_UNUSED(t)

    double u1 = is_powered;

    double dp1 = Y[1] - ps2;

    double u2 = cut(pf(k[1] * dp1), 0.0, 1.0);

    double u3 = cut(nf(k[2] * dp1), 0.0, 1.0);

    double sum_p1 = Y[2] + ps1 - pTM;

    double u4 = cut(nf(k[3] * sum_p1), 0.0, 1.0);

    double sum_p2 = Y[0] + pk * (1.0 - is_key_on) - pd;

    double u5 = p1_rate = cut(nf(k[4] * sum_p2), 0.0, 1.0);

    double Q2 = K[4] * (pFL - Y[1]) - K[5] * Y[1] * u5;

    double Q1 = K[1] * (pTM - Y[2]) - K[2] * Y[2] * u3;

    dYdt[0] = ( pk * u1 * u2 - Y[0] ) / T1;

    dYdt[1] = Q2 / V2;

    dYdt[2] = Q1 / V1;

    emergencyRate = K[3] * pTM * u4;
}

void AutoTrainStopEPK150::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)

    emit soundSetVolume("EPK", static_cast<int>(p1_rate * 100.0));
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void AutoTrainStopEPK150::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }

    for (size_t i = 1; i < k.size(); ++i)
    {
        QString coeff = QString("k%1").arg(i);
        cfg.getDouble(secName, coeff, k[i]);
    }

    cfg.getDouble(secName, "ps1", ps1);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
GET_AUTO_TRAIN_STOP(AutoTrainStopEPK150)
