#ifndef MPCS_DATA_H
#define MPCS_DATA_H

#include    <array>
#include    "pant-description.h"

//------------------------------------------------------------------------------
// Структура входных сигналов
//------------------------------------------------------------------------------
struct mpcs_input_t
{
    /// Род тока
    int current_kind;

    /// Поднятые ТП
    std::array<bool, NUM_PANTOGRAPHS> pant_up;

    /// Опущеные ТП
    std::array<bool, NUM_PANTOGRAPHS> pant_down;

    /// Отключен ли БВ
    bool isOff_fs;

    /// ПРТ
    int current_kind_switch_state;

    /// Входное напряжение на ГВ
    double Uin_ms;

    /// Отключен ли ГВ
    bool isOff_ms;

    /// Входное напряжение на БВ
    double Uin_fs;

    std::array<double, 4> aux_const_U;

    // принимать данные давление в ГР
    /// Входное давление с главного резервуара
    double PressMR;

    mpcs_input_t()
    {
        current_kind = 0;
        std::fill(pant_up.begin(), pant_up.end(), false);
        std::fill(pant_down.begin(), pant_down.end(), false);

        isOff_fs = false;
        current_kind_switch_state = 0;
        Uin_ms = 0;

        isOff_ms = false;
        Uin_fs = 0;

        std::fill(aux_const_U.begin(), aux_const_U.end(), 0);
    }
};

//------------------------------------------------------------------------------
//  Состояние ламп сенсорных кнопок
//------------------------------------------------------------------------------
struct lamps_state_t
{
    float pant_fwd;
    float pant_bwd;
    float gv;
    float train_heating;
    float recup_disable;
    float auto_driver;
    float speed_control;
    float vz;

    float ept;
    float gs;
    float pv;
    float wheel_clean;
    float saund1;
    float brake_release;
    float test;
    float res_purge;

    lamps_state_t()
        : pant_fwd(0.0)
        , pant_bwd(0.0)
        , gv(0.0)
        , train_heating(0.0)
        , recup_disable(0.0)
        , auto_driver(0.0)
        , speed_control(0.0)
        , vz(0.0)

        , ept(0.0)
        , gs(0.0)
        , pv(0.0)
        , wheel_clean(0.0)
        , saund1(0.0)
        , brake_release(0.0)
        , test(0.0)
        , res_purge(0.0)
    {

    }
};

//------------------------------------------------------------------------------
// Структура выходных сигналов
//------------------------------------------------------------------------------
struct mpcs_output_t
{
    /// Состояние ТП
    std::array<bool, NUM_PANTOGRAPHS> pant_state;

    /// Включение ГВ
    bool turn_on_ms = false;

    /// Включение БВ
    bool turn_on_fs = false;

    /// Тумблеры управления мотор-компрессорами
    std::array<bool, 2> toggleSwitchMK;

    double MKstate;

    lamps_state_t lamps_state;

    mpcs_output_t()
    {
        std::fill(pant_state.begin(), pant_state.end(), false);
        std::fill(toggleSwitchMK.begin(), toggleSwitchMK.end(), false);
    }
};

#endif // MPCS_DATA_H
