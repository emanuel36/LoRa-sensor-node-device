#include "../../inc/Peripheral Drivers/statusLed.h"
#include "../../inc/main.h"

void statusLed_Inicialize(){
    NORMAL_LED_PIN = 0;
    WARNING_LED_PIN = 0;
    NORMAL_LED = 0;
    WARNING_LED = 0;
}

void swapLedState(){
    if(getSystemStatus() == NORMAL){
        WARNING_LED = 0;
        NORMAL_LED = !NORMAL_LED;
    }else{//systemStatus == WARNING_MODE
        NORMAL_LED = 0;
        WARNING_LED = !WARNING_LED;
    }
}
