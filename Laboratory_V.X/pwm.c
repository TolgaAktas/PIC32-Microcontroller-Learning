#include "pwm.h"


void generatePWM(){
    
    T2CONbits.TCKPS = 6;    //Prescaler set to 64
    PR2 = 2499;             //Period = (PR2 + 1) * Prescaler * 12.5ns = 0.002 = 1/500Hz
    TMR2 = 0;
    OC1CONbits.OCM = 0b110; //PWM mode without fault pin
    OC1RS = 500;            //
    OC1R = 500;
    
    T2CONbits.ON = 1;
    OC1CONbits.ON = 1;
    
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < 4 * 40000000){
        ;
    }
    
    OC1RS = 1250;
    
//    while(1){
//        ;
//    }
    
}