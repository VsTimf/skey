#include "skey.hpp"

TKey key[KEY_QNT] = {KEY_LIST};


// Return 1 if pin state is active (ACTIVE_LOW or ACTIVE_HIGH)
uint8_t TKey::get_pin_state(void){
    return (active_level == KEY_ACTIVE_LOW) ? (port->IDR & pin) == 0 : (port->IDR & pin) != 0;
}



void TKey::debounce(void)
{
    pin_new_state = get_pin_state();

    debounce_cnt = pin_prv_state == pin_new_state ? debounce_cnt+1 : 0;
    pin_prv_state = pin_new_state;
    
    if(debounce_cnt == KEY_DEBOUNCE_MS)
        pin_state = pin_new_state;
}



void key_process()
{
    TKey* ck;        // curr key

    for (uint8_t idx = 0; idx < KEY_QNT; idx++)
    {
        ck = &key[idx];
        ck->debounce();
        
        switch (ck->state)
        {
        case KEY_IDLE:
            if (ck->pin_state)
            {
                ck->state = KEY_CLICK;
                ck->state_cnt = 0;

                ck->event_active = 1;
            }
            break;

        case KEY_CLICK:
            if (ck->pin_state)
            {
                if (++ck->state_cnt > KEY_HOLD_MS)
                {
                    ck->state = KEY_HOLD;
                    ck->state_cnt = 0;
                    ck->event_active = 1;
                }
            }
            else
                ck->state = KEY_IDLE;
            break;


        case KEY_HOLD:
            if (ck->pin_state)
            {
                if (++ck->state_cnt > KEY_HOLD_REPEAT_EVENT_MS)
                {
                    ck->event_active = 1;
                    ck->state_cnt = 0;
                }
            }
            else
                ck->state = KEY_IDLE; 
            break;
        }
    }
}

KeyState get_key(uint8_t idx)
{
    if(idx >= KEY_QNT)
        while(1);             // wrong key index
        

    if (key[idx].state == KEY_CLICK)
    {
        if (key[idx].event_active)
        {
            key[idx].event_active = 0;
            return KEY_CLICK;
        }
        return KEY_CLICK_NO_EVENT;
    }

    if (key[idx].state == KEY_HOLD)
    {
        if (key[idx].event_active)
        {
            key[idx].event_active = 0;
            return KEY_HOLD;
        }
        return KEY_HOLD_NO_EVENT;
    }
    
    return key[idx].state;
}


bool check_key(uint8_t idx, KeyState check_state)
{
  if(idx >= KEY_QNT)
     while(1);             // wrong key index
  
  if (key[idx].state == check_state)
  {
      if(check_state == KEY_CLICK || check_state == KEY_HOLD)
      {
        if(key[idx].event_active)
        {
          key[idx].event_active = 0;
          return true;
        }
      
        return false;
      }
      return true;
  }
  return false;  
}