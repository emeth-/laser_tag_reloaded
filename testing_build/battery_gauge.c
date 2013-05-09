//Plays the shoot sound whenever BUT (onboard button) is pressed.
//Requires a speaker connected to P3 and GND.

//Local includes:
#include <libmaple/libmaple.h>
#include "initialize.h"
#include "communication.h"
#include "usb.h"
#include "ledGraph.h"

#include <libmaple/gpio.h>

#include "player.h"

#include "speaker.h"
#include "trigger.h"
#include "fuelGauge.h"

/*void transmit_interrupt(void){
    hit result = storage_getShot();
    if(result.ID!=0){
        transmit_hitData(result);
    }
}*/

/*
void toggleLED(void){
    gpio_toggle_bit(GPIOB, 1);
}
*/



void laserTest(void){
    sender_shoot();
    speaker_playShoot();
    gpio_toggle_bit(GPIOB, 1);

}



// setup() and loop():
void setup(void) {
    
/*    storage_start();
    storage_add(16, "SOME LOCATION");
    storage_add(16, "ANOTHER LOCATION");
*/

    //usb_end();
    //batteryMonitor_initialize();
    //communication_start();

    bluetooth_start();
    
    speaker_start();

    //gpio_set_mode(GPIOB, 8, GPIO_INPUT_PD);
    //exti_attach_interrupt(AFIO_EXTI_8, AFIO_EXTI_PB, speakerTest, EXTI_RISING);

    //exti_attach_interrupt(AFIO_EXTI_8, AFIO_EXTI_PB, fakeShot, EXTI_RISING);

    //Onboard LED
    gpio_set_mode(GPIOB, 1, GPIO_OUTPUT_PP);
    gpio_write_bit(GPIOB, 1, 1);
    

    sender_start(10);
    trigger_set_interrupt(laserTest);
    trigger_start();

    batteryMonitor_initialize();

    //LED Graph Button
    //gpio_set_mode(GPIOA,0,GPIO_INPUT_PU);
    //exti_attach_interrupt(AFIO_EXTI_0, AFIO_EXTI_PA, laserTest, EXTI_RISING);
    //

    //LED
    //gpio_set_mode(GPIOB, 1, GPIO_OUTPUT_PP);
    //gpio_write_bit(GPIOB, 1, 1);

    //Onboard Button
    //gpio_set_mode(GPIOB, 8, GPIO_INPUT_PD);
    //exti_attach_interrupt(AFIO_EXTI_8, AFIO_EXTI_PB, fakeShot, EXTI_RISING);
    
    

}

void loop(void) {


    if (bluetooth_available()){
        char myChar = bluetooth_read();
        if (myChar == 'a') {
            gpio_write_bit(GPIOB, 1, 1);
        } else if (myChar == 'h') {
            speaker_playHit();
        } else if (myChar == 's') {
            speaker_playShoot();
        } else if (myChar == 'l') {
            laserTest();
        } else if (myChar == 'p') {
            char message[128] = { ' ' };
            char msg[12] = { ' ' };
            gauge_voltage(msg, 12);
            sprintf(message, "Battery voltage is: %s \r\n", msg);
            bluetooth_printString(message);
            sprintf(message, "Battery percentage is: %f \r\n", gauge_percentFloat());
            bluetooth_printString(message);

        } else {
            gpio_write_bit(GPIOB, 1, 0);
        }
    }

}


__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();
    
    while (1) {
        loop();
    }
    
    return 0;
}
