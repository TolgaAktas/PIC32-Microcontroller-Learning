#include <xc.h>
#include <sys/attribs.h>
#include <string.h>

#include <stdio.h>
#include "display.h"
#include "adc_convert.h"
#include "UART_Comm.h"
//#include "pwm.h"

int getLEDmap(int val);
void setDutyCycle(int val);

//static volatile unsigned int choose = 0;
//
//void __ISR(_EXTERNAL_1_VECTOR, IPL4S0FT) s3 (void){
//    if(choose == 0){
//        choose = 1;
//    }else{
//        choose = 0;
//    }
//    LATA = 0x1111;
//    IFS0bits.INT1IF = 0;
//}


int main(void){
    
    display_initialize();
    display_clear();
    
    unsigned int sample_pot = 0, sample_temp = 0, sample_disp = 10000;
   
    char msg[20]={};
    
    //Configuration for using all LED lights
    DDPCON = 0x0000;      
    TRISA  = 0x0000;
    int LEDbits = 0;
    
    TRISDbits.TRISD6 = 1; //S3 button set as input
    
    //R4.1
    T2CONbits.TCKPS = 2;        //Prescaler for TYPE B Timer 2 : 0b10 = 64
    PR2 = 2499;                 //Period = 1/Freq = (PR2 + 1) * Prescaler * 12.5 ns = 0.002 s --> 500 Hz
    TMR2 = 0;
    OC1CONbits.OCM = 0b110;     //PWM mode without fault pin
    OC1RS = 1250;                //Duty Cycle = OC1RS/(PR2+1) = 0.50
    OC1R = 1250;
    
    T2CONbits.ON = 1;
    OC1CONbits.ON = 1;
        
    _CP0_SET_COUNT(0);
    while(_CP0_GET_COUNT() < 0.5 * 20000000){
        ;
    }
    
    //R4.1 end
    
    
    //ADC Configurations here
    AD1PCFGbits.PCFG1 = 0;          //Connect temperature pin to AN1
    AD1PCFGbits.PCFG3 = 0;          //Connect potentiometer to AN3
    AD1PCFGbits.PCFG4 = 0;       //Set temperature sensor as analog input
    AD1PCFGbits.PCFG5 = 0;       //Set AN5 as analog input (potentiometer pin)
    
    AD1CON2bits.VCFG = 0b000;   //Set VREF for SAR Vrefh=3.3 Vrefl=0
    //AD1CON2bits.CSCNA = 0;      //Don't scan the inputs
    AD1CON2bits.ALTS = 0;       //Always use MUXA
    AD1CHSbits.CH0NA = 0;       //Use Vrefl
    AD1CON3bits.ADCS = 2;       //Tad = 3 * Tpb * (ADCS +1);
    AD1CON1bits.ADON = 1;

    int len = 0, sw_in = 0;
    
    while(1){
        
        display_clear();
        sample_temp = adc_sample_convert(1);        //Sample temperature input
        sample_pot = adc_sample_convert(3);         //Sample potentiometer input

        //TODO: Need a switch mechanism here now. 
        
        if(PORTDbits.RD6==1){               //If S3 is pressed, display potentiometer reading, else temperature
            sample_disp = sample_pot;
        }else{
            sample_disp = sample_temp;
        }
        
        getLEDmap(sample_disp);             //Decide which of the LEDs will light up
        
        //R4.2
        setDutyCycle(sample_disp);          //Set the duty cycle according to the reading value
        
        sprintf(msg, "%u : %.2f V",sample_disp,sample_disp*VOLTS_PER_COUNT);
        len = strlen(msg);
        display_write(msg,len);
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < DELAY_TICKS){;}
    }
    
    return 0;
}

int getLEDmap(int sample){
    
    if(sample >= 895)
            LATA = 0b11111111;
        else if(sample >= 767)
            LATA = 0b11111110;
        else if(sample >= 639)
            LATA = 0b11111100;
        else if(sample >= 512)
            LATA = 0b11111000;
        else if(sample >= 384)
            LATA = 0b11110000;
        else if(sample >= 256)
            LATA = 0b11100000;
        else if(sample >= 128)
            LATA = 0b11000000;
        else if(sample >= 1)
            LATA = 0b10000000;
        else{
            LATA = 0x00;
        }
}

//R4.2
void setDutyCycle(int val){
    double dutyCycle = val/1024;
    OC1RS = ((int)dutyCycle) * (PR2+1);
    
}