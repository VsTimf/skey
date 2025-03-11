#pragma once

/* Use HAL library */
#include "stdint.h"
#include "stm32_cmsis.h" // .h file with CMSIS mcu specific header file (aka "stm32f1xx.h")
#include "skey_config.hpp"


typedef enum
{
    KEY_ACTIVE_LOW = 0,
    KEY_ACTIVE_HIGH = 1
} KEY_ACTIVE_LEVEL_T;


typedef enum
{
    KEY_IDLE,                                              
    KEY_CLICK,                                      // return 1 time after key clicked
    KEY_CLICK_NO_EVENT,                             // returned after user code get "KEY_CLICK" event and until "KEY_HOLD" event will occur
    KEY_HOLD,
    KEY_HOLD_NO_EVENT
} KeyState;


class TKey
{
    const GPIO_TypeDef *port;
    const uint16_t pin;
    const KEY_ACTIVE_LEVEL_T active_level;

    public:
    uint8_t pin_new_state;
    uint8_t pin_prv_state;
    uint8_t pin_state;

    uint16_t debounce_cnt;

    KeyState state;
    uint16_t state_cnt;

    uint8_t event_active;

     
    TKey(GPIO_TypeDef* _port, uint16_t _pin, KEY_ACTIVE_LEVEL_T _active_level) : port(_port), pin(_pin), active_level(_active_level) 
    {
        pin_state = 0;
        debounce_cnt = 0;

        state = KEY_IDLE;
        state_cnt = 0;

        event_active = 0;
    }

    uint8_t get_pin_state(void);
    void  debounce(void);
};

void key_process(void);
KeyState get_key(uint8_t idx);
bool check_key(uint8_t idx, KeyState check_state);
