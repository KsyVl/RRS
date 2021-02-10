//-----------------------------------------------------------------------------
//
//      Класс "Основной экран"
//      (c) РГУПС, ВЖД 10/08/2019
//      Разработал: Даглдиян Б.Д.
//
//-----------------------------------------------------------------------------
/*!
 *  \file
 *  \brief Класс "Основной экран"
 *  \copyright РГУПС, ВЖД
 *  \author Даглдиян Б.Д.
 *  \date 10/08/2019
 */

#include "screen-main.h"

#include "Speedometer.h"
#include "scale-traction.h"
#include "scale-traction-val.h"
#include "load-traction-converter.h"
#include "indicator-switch-position.h"
#include "pressures.h"
#include "brake-release-indicators.h"

#include "display-shared-structures.h"



//-----------------------------------------------------------------------------
//  КОНСТРУКТОР
//-----------------------------------------------------------------------------
ScreenMain::ScreenMain(const QString &config_dir, QString scrName, QRect scrGeo, QWidget *parent)
    : AbstractScreen(scrName, scrGeo, parent)
{
    //
    this->setVisible(false);
//    this->setAutoFillBackground(true);
//    this->setPalette(QPalette(QColor(150,255,150)));
//    this->setStyleSheet("border: 5px solid blue;"
//                        "background-color: #C00000");

    config_dir_ = config_dir;


    buttonsNames_ = QStringList{"Главный\nкадр", "Авто-\nведение", "Диагнос-\nтика",
                                "Архив", "Обслужива-\nние", "", "", "",
                                "Видео-\nнаблюд.", "БЛОК"};
    buttonSelectedIdx_ = 0;

    this->createAllChildren_();
}



//-----------------------------------------------------------------------------
//  ДЕСТРУКТОР
//-----------------------------------------------------------------------------
ScreenMain::~ScreenMain()
{

}



//-----------------------------------------------------------------------------
//  Обработка нажатия кнопок
//-----------------------------------------------------------------------------
void ScreenMain::receiveOtherButton(Local::ButtonId id)
{

}



//-----------------------------------------------------------------------------
//  Обновление данных экрана
//-----------------------------------------------------------------------------
void ScreenMain::updateScreen(screen_data_t* data)
{
    screen_main_t* smt = static_cast<screen_main_t*>(data);

    // спидометр
    speedometer_->setVals(smt->sCurSpeed,
                          smt->sSetpointSpeed,
                          smt->sCurSpeedLimit,
                          smt->sNextSpeedLimit);
    speedometer_->setTrainPos(smt->sTrainPos);

    // шкала тяги
    scaleTractionVal_->setVal(smt->scaleSetTraction, smt->scaleActualTraction);

    // контроль напряжения
    labControlVoltage_->setText(QString::number(smt->controlVoltage/100) +
                                QString::number((smt->controlVoltage % 100)/10) +
                                QString::number(smt->controlVoltage % 10) +
                                " В");

    // состояние ЭПТ
    updateStateEPT_(smt->outputI, smt->outputU, false, false, false);

    // нагрузка ТПр
    loadTC_->setValues(smt->ltct);

    // индикатор положения переключателей крана машиниста
    iSwitchPos_->setSelect(smt->numSwitch);

    // сигнализаторы неотпуска тормоза (ТЦ1, ТЦ2, ТЦ3)
    brIndicators_->setVals(smt->TC1, smt->TC2, smt->TC3);
    // значения давлений
    pressureUR_->setVal(smt->pressureUR);
    pressureTM_->setVal(smt->pressureTM);
    pressurePM_->setVal(smt->pressurePM);
    pressureTC_->setVal(smt->pressureTC);
    pressureVR_->setVal(smt->pressureVR);
    pressureAST_->setVal(smt->pressureAST);
    // мотор-компрессоры
    labMotorCompressor1_->setPixmap(getMotorCompressorImgName_(smt->motorCompressor1));
    labMotorCompressor2_->setPixmap(getMotorCompressorImgName_(smt->motorCompressor2));

    //

}



//-----------------------------------------------------------------------------
//  Создать все дочерние виджеты
//-----------------------------------------------------------------------------
void ScreenMain::createAllChildren_()
{
    // устанавливаем СПИДОМЕТР
    speedometer_ = new SPeedometer(config_dir_, QSize(300,300), this );
    speedometer_->move(-1, 0);

    // шкала тяги
    ScaleTraction *scaleTraction = new ScaleTraction(QSize(180, 268), this);
    scaleTraction->move(speedometer_->width() - 1, 0);
    scaleTractionVal_ = new ScaleTractionVal(scaleTraction->size(), this);
    scaleTractionVal_->move(scaleTraction->pos());

    // строка подсказки
    createLineHelp_();
    // напряжение в цепи управления и АБ
    createVoltageIndication_();
    // состояние ЭПТ
    createStateEPT_();

    // нагрузка ТПр
    int loadTC_w = speedometer_->width() + scaleTraction->width();
    //loadTC_w = 480;
    loadTC_ = new LoadTractionConverter(QSize(loadTC_w, 186), this);
    loadTC_->move(-1, scaleTraction->height());



    //
    iSwitchPos_ = new IndicatorSwitchPosition(QSize(75, 200), this);
    iSwitchPos_->move(loadTC_->x() + loadTC_->width(), 254);



    int fooX = iSwitchPos_->x() + iSwitchPos_->width();

    QLabel* fooLabel = new QLabel(this);
    fooLabel->resize(245, 40);
    fooLabel->move(fooX, 254);
    fooLabel->setStyleSheet("border: 1px solid black;"
                            "color: black;"
                            "font: 11pt Arial;"
                            "font-weight: 600;");

    labUOB_ = new QLabel("УОБ", fooLabel);
    labUOB_->resize(70, 32);
    labUOB_->move(8, 4);
    labUOB_->setStyleSheet("border: none;"
                           "background-color: white;");
    labUOB_->setAlignment(Qt::AlignCenter);

    labBrakeRelease_ = new QLabel("Отпуск тор.", fooLabel);
    labBrakeRelease_->resize(140, 32);
    labBrakeRelease_->move(92, 4);
    labBrakeRelease_->setStyleSheet("border: none;"
                                    "background-color: white;");
    labBrakeRelease_->setAlignment(Qt::AlignCenter);



    // ТЦ + давления + мотор-компрессоры
    createPressures_(fooLabel->x(), fooLabel->y() + fooLabel->height());
}

//-----------------------------------------------------------------------------
//  Создание строки подсказки
//-----------------------------------------------------------------------------
void ScreenMain::createLineHelp_()
{
    int posX = speedometer_->width() + scaleTractionVal_->width();

    labLineHelp_ = new QLabel("Строка подсказки", this);
    labLineHelp_->resize(this->width() - posX + 2, 75);
    labLineHelp_->move(posX - 1, 0);
    labLineHelp_->setStyleSheet("border: 1px solid black;"
                                "color: white;");
    labLineHelp_->setAlignment(Qt::AlignCenter);
}

//-----------------------------------------------------------------------------
//  Создание индикации напряжения в цепи управления и АБ. Готовность к движению
//-----------------------------------------------------------------------------
void ScreenMain::createVoltageIndication_()
{
    int posX = speedometer_->width() + scaleTractionVal_->width();

    //
    QLabel* fooLabel = new QLabel(this);
    fooLabel->resize(75, 74);
    fooLabel->move(posX - 1, 75);
    fooLabel->setStyleSheet("border: 1px solid black;");

    QLabel* fooLabelU = new QLabel("U цу", this);
    fooLabelU->resize(fooLabel->width(), fooLabel->height()/2);
    fooLabelU->move(fooLabel->x(), fooLabel->y() + 5);
    fooLabelU->setStyleSheet("color: white;"
                             "font: 12pt Arial;"
                             "font-weight: 600;"
                             "background-color: #fb8d00;"
                             "margin: 5px;"
                             "padding-bottom: 2px;");
    fooLabelU->setAlignment(Qt::AlignCenter);


    //
    labControlVoltage_ = new QLabel("-", this);
    labControlVoltage_->resize(fooLabel->width(), fooLabel->height()/2);
    labControlVoltage_->move(fooLabel->x(), fooLabel->y() + fooLabel->height()/2 - 3);
    labControlVoltage_->setStyleSheet("color: #fb8d00;"
                                      "font: 14pt Arial;"
                                      "font-weight: 600;"
                                      "margin: 5px;");
    labControlVoltage_->setAlignment(Qt::AlignCenter);


    //
    QLabel* fooLabel2 = new QLabel(this);
    fooLabel2->resize(245, 74);
    fooLabel2->move(posX + fooLabel->width() - 1, 75);
    fooLabel2->setStyleSheet("border: 1px solid black;");

    QLabel* fooLabelReadyRun = new QLabel("Не готов к движению", this);
    fooLabelReadyRun->resize(fooLabel2->size());
    fooLabelReadyRun->move(fooLabel2->pos());
    fooLabelReadyRun->setStyleSheet("color: white;"
                                    "font: 12pt Arial;"
                                    "font-weight: 600;"
                                    "background-color: #fb8d00;"
                                    "margin: 10px 15px;");
    fooLabelReadyRun->setAlignment(Qt::AlignCenter);
}

//-----------------------------------------------------------------------------
//  Создание индикации состояния ЭПТ
//-----------------------------------------------------------------------------
void ScreenMain::createStateEPT_()
{
    int posX = speedometer_->width() + scaleTractionVal_->width();

    //
    QLabel* fooLabel = new QLabel("Состояние ЭПТ", this);
    fooLabel->resize(this->width() - posX + 2, 105);
    fooLabel->move(posX - 1, 149);
    fooLabel->setStyleSheet("border: 1px solid black;"
                            "color: white;"
                            "font: 12pt Arial;"
                            "font-weight: 600;"
                            "padding-top: 5px;");
    fooLabel->setAlignment(Qt::AlignHCenter);


    //
    QString styleSheet("color: white;"
                       "font: 14pt Arial;"
                       "font-weight: 600;");

    // ток
    QLabel* fooLabelI = new QLabel("I =", this);
    fooLabelI->move(fooLabel->x() + 16, fooLabel->y() + 40);
    fooLabelI->setStyleSheet(styleSheet);

    labOutputI_ = new QLabel("0.0 А", this);
    labOutputI_->resize(70, fooLabelI->height() - 5);
    labOutputI_->move(fooLabelI->x() + 22, fooLabelI->y());
    labOutputI_->setStyleSheet(styleSheet);
    labOutputI_->setAlignment(Qt::AlignRight);


    // напряжение
    QLabel* fooLabelU = new QLabel("U =", this);
    fooLabelU->move(fooLabel->x() + 12, fooLabel->y() + 70);
    fooLabelU->setStyleSheet(styleSheet);

    labOutputU_ = new QLabel("055 В", this);
    labOutputU_->resize(70, fooLabelU->height() - 5);
    labOutputU_->move(fooLabelU->x() + 26, fooLabelU->y());
    labOutputU_->setStyleSheet(styleSheet);
    labOutputU_->setAlignment(Qt::AlignRight);


    // индикатор состояния
    imgStateIndicator_ = QImage(QSize(182, 60), QImage::Format_ARGB32_Premultiplied);

    labStateIndicator_ = new QLabel(fooLabel);
    labStateIndicator_->resize(imgStateIndicator_.size());
    labStateIndicator_->move(126, 36);
    labStateIndicator_->setStyleSheet("border: none;"
                                      "padding-top: 0px;");

    //
    updateStateEPT_(0, 0, false, false, false);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenMain::updateStateEPT_(double I, int U, bool light1, bool light2, bool light3)
{
    // ток и напряжение
    labOutputI_->setText(QString::number(I, 'f', 1) + " А");
    labOutputU_->setText(QString::number(U/100) +
                         QString::number((U % 100)/10) +
                         QString::number(U % 10) +
                         " В");

    // индикатор (кружочки)
    imgStateIndicator_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(imgStateIndicator_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    int circleW = labStateIndicator_->height();
    drawCircleStatusIndicator_(paint, circleW/2, circleW, light1);
    drawCircleStatusIndicator_(paint, circleW/2*3 + 1, circleW, light2);
    drawCircleStatusIndicator_(paint, circleW/2*5 + 2, circleW, light3);

    paint.end();
    labStateIndicator_->setPixmap(pix);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenMain::drawCircleStatusIndicator_(QPainter &paint, int posX, int w, bool light)
{
    // внешний круг
    paint.setPen(QPen( Qt::white,
                       w,
                       Qt::SolidLine,
                       Qt::RoundCap ));
    paint.drawPoint(posX, w/2);

    if (light)
    {
        // внутренний круг
        paint.setPen(QPen( Qt::gray,
                           w - 8,
                           Qt::SolidLine,
                           Qt::RoundCap ));
        paint.drawPoint(posX, w/2);
    }
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenMain::createPressures_(int posX, int posY)
{
    QSize prSize(123, 40);

    brIndicators_ = new BrakeReleaseIndicators(prSize, this);
    brIndicators_->move(posX, posY);

    pressureTC_ = new Pressures(prSize, "ТЦ", this);
    pressureTC_->move(posX + 123, posY);

    posY += 40;

    pressureUR_ = new Pressures(prSize, "УР", this);
    pressureUR_->move(posX, posY);

    pressureVR_ = new Pressures(prSize, "ВР", this);
    pressureVR_->move(posX + 123, posY);

    posY += 40;

    pressureTM_ = new Pressures(prSize, "ТМ", this);
    pressureTM_->move(posX, posY);

    pressureAST_ = new Pressures(prSize, "АСТ", this);
    pressureAST_->move(posX + 123, posY);

    posY += 40;

    pressurePM_ = new Pressures(prSize, "ПМ", this);
    pressurePM_->move(posX, posY);


    // мотор-компрессоры
    createMotorCompressor_(labMotorCompressor1_, QPoint(posX + 123, posY));
    createMotorCompressor_(labMotorCompressor2_, QPoint(posX + 123 + 62, posY));
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void ScreenMain::createMotorCompressor_(QLabel *&lab, QPoint pos)
{
    lab = new QLabel(this);
    lab->setStyleSheet("border: 1px solid black;");
    lab->resize(62, 40);
    lab->move(pos);
    lab->setAlignment(Qt::AlignHCenter);

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
QString ScreenMain::getMotorCompressorImgName_(int motorCompressorState)
{
    QString foo("");
    switch (motorCompressorState)
    {
    case MotorCompressorEnum::isolated:
        foo = "isolted";
        break;
    case MotorCompressorEnum::on:
        foo = "on";
        break;
    case MotorCompressorEnum::off:
        foo = "off";
        break;
    }

    return MAIN_SCREEN_IMG_PREFIX_ + "motor-compressor-" + foo + ".png";
}

