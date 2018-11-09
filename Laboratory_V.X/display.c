#include <proc/p32mx795f512l.h>

void delay(long int cycles){
    int i = cycles;
    
    while(i > 0){
        i--;
    }
}
void display_enable(){
    //Enable is in PORTD
    TRISDbits.TRISD4= 0;    //Set PortD as output
    LATDbits.LATD4 = 1;     //Set Enable =1 
    
    delay(100);
    LATDbits.LATD4 = 0;     //After delay reset enable to make a pulse
    delay(100);
}
void display_initialize(){
    
    //RS = 0
    TRISB = 0x0000;         //Set PortB as output
    LATBbits.LATB15 = 0;    //Set RS = 0
    
    //Function set
    TRISE = 0x0000;         //Set PortE as output
    LATE = 0b0000111100;    //Set DB registers as desired for function set mode
    display_enable();

    //Display ON, Cursor OFF, BLINK OFF
    LATE = 0x0000;
    LATEbits.LATE3 = 1;     //
    LATEbits.LATE2 = 1;     //
    display_enable();
    
    //Display clear
    LATE = 0x0001;
    display_enable();
    
    //Entry Mode Set
    TRISE = 0x0000;
    LATE = 0x0006;
    
    display_enable();
    
    
}


void display_clear(){
    
    //display_initialize();
    
    LATBbits.LATB15 = 0;
    LATE = 0x0000;
    LATEbits.LATE0 = 1;
    display_enable();
    delay(10000);
}


display_write(char * data, int length){
    
    LATBbits.LATB15 = 1;    //Set RS = 1 
    int i;
    for(i = 0; i < length; i++){

        LATE = data[i];     //Set DB registers to the data character
        display_enable();   //Send enable pulse to pass the data
        
    }    
}

