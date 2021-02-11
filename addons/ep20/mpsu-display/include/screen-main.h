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

#ifndef SCREENMAIN_H
#define SCREENMAIN_H


#include    "display.h"
#include "abstract-screen.h"

#include "image-widget.h"

class SPeedometer;
class ScaleTraction;
class ScaleTractionVal;
class LoadTractionConverter;
class IndicatorSwitchPosition;
class Pressures;
class BrakeReleaseIndicators;


/*!
 * \class ScreenMain
 * \brief Класс основного экрана дисплея ласточки
 */
class ScreenMain : public AbstractScreen
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор
     * \param scrName - имя экрана
     * \param scrGeo - геометрия
     */
    ScreenMain(const QString &config_dir, QString scrName, QRect scrGeo, QWidget* parent = Q_NULLPTR);
    /// Деструктор
    ~ScreenMain();


public slots:
    /// Обработка нажатия кнопок
    void receiveOtherButton(Local::ButtonId id) Q_DECL_OVERRIDE;

    /// Обновление данных экрана
    void updateScreen(screen_data_t* data) Q_DECL_OVERRIDE;


private:
    /// Спидометр
    SPeedometer* speedometer_;
    /// Шкала тяги
    ScaleTractionVal* scaleTractionVal_;
    /// Строка подсказки
    QLabel* labLineHelp_;
    //
    QLabel* labControlVoltage_;
    //
    QLabel* labOutputI_;
    QLabel* labOutputU_;
    //
    QImage imgStateIndicator_;
    QLabel* labStateIndicator_;
    //
    LoadTractionConverter* loadTC_;
    //
    IndicatorSwitchPosition* iSwitchPos_;
    //
    QLabel* labUOB_;
    QLabel* labBrakeRelease_;
    //
    BrakeReleaseIndicators* brIndicators_;
    //
    Pressures* pressureUR_;
    Pressures* pressureTM_;
    Pressures* pressurePM_;
    Pressures* pressureTC_;
    Pressures* pressureVR_;
    Pressures* pressureAST_;
    //
    QLabel* labMotorCompressor1_;
    QLabel* labMotorCompressor2_;

    QString config_dir_;


// ПРЕФИКС ДЛЯ ЗАГРУЗКИ ИЗ РЕСУРСОВ *******************************************
    /// Префикс нажатых клавиш
    const QString MAIN_SCREEN_IMG_PREFIX_ = ":/screen-imgs/images/screen-imgs/";


    /// Создать все дочерние виджеты
    void createAllChildren_() Q_DECL_OVERRIDE;

    /// Создание строки подсказки
    void createLineHelp_();

    // Создание индикации напряжения в цепи управления и АБ. Готовность к движению
    void createVoltageIndication_();

    // Создание индикации состояния ЭПТ
    void createStateEPT_();
    void updateStateEPT_(double I, int U, bool light1, bool light2, bool light3);

    void drawCircleStatusIndicator_(QPainter &paint, int posX, int w, bool light, QColor color);

    void createPressures_(int posX, int posY);

    void createMotorCompressor_(QLabel* &lab, QPoint pos);

    QString getMotorCompressorImgName_(int motorCompressorState);

};

#endif // SCREENMAIN_H
