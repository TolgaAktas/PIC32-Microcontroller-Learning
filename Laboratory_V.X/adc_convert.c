#include "adc_convert.h"
#include <proc/p32mx795f512l.h>


unsigned int adc_sample_convert(int pin){
    
    unsigned int elapsed = 0, finish_time = 0;
    
    AD1CHSbits.CH0SA = pin;     //Set the positive input to pin
    AD1CON1bits.SAMP = 1;       //Start sampling
    
    //Wait for 10 cycles
    elapsed = _CP0_GET_COUNT();     
    finish_time = elapsed + SAMPLE_TIME;
    while(_CP0_GET_COUNT() < finish_time){;}
    
    AD1CON1bits.SAMP = 0;       //Stop sampling
    
    while(!AD1CON1bits.DONE){;} //Wait for conversion to finish
    
    return ADC1BUF0;            //Return the converted reading
    
}