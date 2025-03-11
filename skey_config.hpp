/* This is simple Key handler library for STM32 */

/* HOW TO USE */

// 1. Define timing in milliseconds
#define KEY_DEBOUNCE_MS             10                  // Rise "KEY_CLICK" event after pin state is stable specified amount of time
#define KEY_HOLD_MS                 1500                // Rise "KEY_HOLD" event first time after holding key specified amount of time
#define KEY_HOLD_REPEAT_EVENT_MS    500                 // Rise "KEY_HOLD" event every specified amount of time when key is hold for long time


// 2. Enumerate KEYS you plan to use. Last enumeration value should always be KEY_QNT
enum KEYS {
    KEY_SEL,
    KEY_UP,
    KEY_DOWN,

    KEY_QNT             // Do not change!
};



// 3. Define "PORT", "PIN", and "ACTIVE LEVEL" of keys in p.2 enumeration order
#define KEY_LIST    TKey(GPIOA, GPIO_PIN_5, KEY_ACTIVE_LOW), \
                    TKey(GPIOA, GPIO_PIN_6, KEY_ACTIVE_LOW), \
                    TKey(GPIOA, GPIO_PIN_7, KEY_ACTIVE_LOW)      


// 4. Call key_process() function every 1 millisecond
// 5. Check if the key had an event. You can use "bool check_key(key, event)" or "event get_key(key)" functions

                      
/* -------------------- Example ----------------------
 
void 1MS_TIMER_IRQ(){
    key_process();
}

main(){
  if (check_key(KEY_SEL, KEY_CLICK)){
      do_smth();
  }

  if (get_key(KEY_SEL, KEY_HOLD)){
      do_smth_else();
  }


OR


  key_state = get_key(KEY_SEL);

  if(key_state == KEY_HOLD){
    do_smth();
  }

  if(key_state == KEY_CLICK){
    do_smth_else();          
  }     
}
    
-----------------------------------------------------*/
                      
/* ------------------- ATTENTION ----------------------                      

Always use "get_key()" function with temp variable:

In the next example second condition will never executed as "KEY_CLICK" event will be reset in first function call:

if(get_key(id) == KEY_HOLD)
  do_smth();

if(get_key(id) == KEY_CLICK)
  do_smth_else();               // never executed

*/

                      
                      
                      