//------------------------------------------------------------------------------
//
//
//
//
//------------------------------------------------------------------------------

#include    "evr305.h"

#include    "filesystem.h"
#include    <QDir>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EVR305::EVR305(QObject *parent)
    : ElectroAirDistributor(parent)
    , A1(0.0)
    , Vpk(0.0)
    , Q1(0.0)
{
    zpk = new SwitchingValve();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
EVR305::~EVR305()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EVR305::ode_system(const state_vector_t &Y,
                                     state_vector_t &dYdt,
                                     double t)
{
    double s1 = abs(control_line[0]) * pf(control_line[0]) * ((p_ar - Y[0]) * K[1]);

    double s2 = (p_ar - P1) * K[4] * cut(pf((Y[0] - pbc_in) * A1) * k[1], 0.0, 1.0);

    P1 = zpk->getPressure1();

    zpk->setInputFlow2(Qbc_in);
    Qbc_out = zpk->getOutputFlow();

    zpk->setOutputPressure(pbc_in);
    pbc_out = zpk->getPressure2();

    Qar_out = Qar_in - s1 * K[3] - s2 * K[5];

    Q1 = s2 - (P1 * K[6] * cut(nf((Y[0] - pbc_in) * A1) * k[2], 0.0, 1.0));
    zpk->setInputFlow1(Q1);

    dYdt[0] = (s1 - (!static_cast<bool>(abs(control_line[0])) * Y[0] * K[2])) / Vpk;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EVR305::preStep(state_vector_t &Y, double t)
{
    Q_UNUSED(Y)
    Q_UNUSED(t)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EVR305::load_config(CfgReader &cfg)
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

    cfg.getDouble(secName, "A1", A1);

    cfg.getDouble(secName, "Vpk", Vpk);


    FileSystem &fs = FileSystem::getInstance();
    QString zpk_config(fs.combinePath(fs.getConfigDir(), "devices").c_str());
    zpk->read_custom_config(zpk_config + QDir::separator() + "zpk");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EVR305::stepKeysControl(double t, double dt)
{
    Q_UNUSED(t)
    Q_UNUSED(dt)
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void EVR305::step(double t, double dt)
{
    zpk->step(t, dt);

    ElectroAirDistributor::step(t, dt);
}

GET_ELECTRO_AIRDISTRIBUTOR(EVR305)
