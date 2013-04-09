
#include "sender.h"
#include <libmaple/gpio.h>
#include <libmaple/exti.h>
#include <libmaple/nvic.h>
#include <libmaple/libmaple.h>

#define DEFAULT_PLAYER_CODE 8
#define SENDER_PORT GPIOC
#define SENDER_PIN 14


uint8 playerCode;


void sender_pulseIR(long microsecs){

  while (microsecs > 0) {
   // 38 kHz is about 13 microseconds high and 13 microseconds low
   gpio_write_bit(SENDER_PORT, SENDER_PIN, 1);
   // this takes about 3 microseconds to happen
   delay_us(10);
   // waits 10 microseconds
   gpio_write_bit(SENDER_PORT, SENDER_PIN, 0);
   // this also takes about 3 microseconds
   delay_us(10);
   // waits 10 microseconds
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }

}

void sender_sendOneHigh(void){
    sender_pulseIR(832);
}

void sender_sendZeroHigh(void){
    sender_pulseIR(416);
}

void sender_sendOneLow(void){
    delay_us(832);
}

void sender_sendZeroLow(void){
    delay_us(416);
}

void sender_setPlayerCode(uint8 newCode){
    playerCode = newCode;
}

uint8 sender_getPlayerCode(void){
    return playerCode;
}

void sender_start(void){
    gpio_set_mode(SENDER_PORT, SENDER_PIN, GPIO_OUTPUT_PP);
    sender_setPlayerCode(DEFAULT_PLAYER_CODE);
}

void sender_sendCode(uint8 code){

    nvic_globalirq_disable();
    int i;
    for(i=0;i<8;i++){
        if (i % 2 == 0){ //Checks if the bit is even.
            if ((code >> i) & 1){ //Grabs the individual ith bit and checks if its a 1.
                sender_sendOneHigh();
            } else {
                sender_sendZeroHigh();
            }
        } else { //Odd bits
            if ((code >> i) & 1){
                sender_sendOneLow();
            } else {
                sender_sendZeroLow();
            }
        }
    }
    sender_sendZeroHigh(); //Sends an end bit as a "high" to close the signal.
    nvic_globalirq_enable();
}

void sender_shoot(void){
    sender_sendCode(playerCode);
}
