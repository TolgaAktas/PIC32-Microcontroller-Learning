#include "math_ops.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>

#include <xc.h>
#include <string.h>
#include <sys/attribs.h>


math_ops_t math_ops;

int ctr=0;    
int len;   
char arg2[17] = {};  

static int flag = 0;

void __ISR(_EXTERNAL_0_VECTOR, IPL4S0FT) s3 (void){
    
    LATAbits.LATA0=1;                       //Set LED3 on
    math_ops.a++;                           //Increment a
    math_ops_update(&math_ops);             //Update the result        
    
    display_clear();                       //Clear display for rewrite
    math_ops_display(&math_ops,arg2);    //op -> string
    len = strlen(arg2);                       
    display_write( arg2, len );             //Write to display
    
    IFS0bits.INT0IF = 0;                    //Reset interrupt 0 flag
    
}

void __ISR(_EXTERNAL_1_VECTOR, IPL4S0FT) s6 (void){
    LATAbits.LATA3=1;                       //Set LED6 on
    math_ops.b++;                           //Increment b
    math_ops_update(&math_ops);             //Update the result
    display_clear();                        //Clear display for rewrite
    math_ops_display (&math_ops,arg2);      //op->string
    len = strlen(arg2);                     
    display_write( arg2, len );             //Write to display
    IFS0bits.INT1IF = 0;                    //Clear flag
}

void __ISR(_EXTERNAL_2_VECTOR, IPL4S0FT) s5(void){
   
    LATAbits.LATA2 = 1;                      //Set LED5 on
    
            //Same revolver logic applies here too (from Lab 3)
            if(ctr < 2){
                
                math_ops.operator++;
                ctr++;
                
                math_ops_update (&math_ops);        //Update the result
                display_clear();
                
                math_ops_display(&math_ops,arg2);   //op->string
                
                len = strlen(arg2);
                
                display_write(arg2,len);            //Write to display
            
            }else{
                
                ctr=0;
                display_clear ();
                
                math_ops.operator = ADD;
                math_ops_update(&math_ops);
                math_ops_display(&math_ops,arg2);
                
                len = strlen(arg2);
                display_write(arg2,len);    
            }
   
    IFS0bits.INT2IF = 0;                          //Clear flag
}
void __ISR(_EXTERNAL_4_VECTOR, IPL4S0FT) s4(void){
    
    LATAbits.LATA1=1;                       //Set LED4 on
    
    display_clear();
    math_ops_init (&math_ops);              //Reset the op to 0+0=0
    math_ops_display (&math_ops,arg2);      //Write the data
    len = strlen(arg2);
    display_write(arg2,len);
    
    IFS0bits.INT4IF = 0;                    //Clear flag
}

int main(){
    
    display_initialize();
    math_ops_init (&math_ops);   
    math_ops_display ( &math_ops, arg2);  
    
//    TRISE=0x0000;
//    //Set interrupt bits as input
    TRISDbits.TRISD0=1; 
    TRISEbits.TRISE8=1;   
    TRISEbits.TRISE9=1;  
    TRISAbits.TRISA15=1; 
    //SET LEDS AS OUTPUT
    
    //TRISA = 0x0000;
    //DDPCON = 0x0000;
    DDPCONbits.JTAGEN = 0;
    LATA = 0x0000;
    
//    TRISD = 0x0000;
//    //SET SWITCHES AS INPUTS
    TRISDbits.TRISD6 = 1; //S3 button input
    TRISDbits.TRISD7 = 1; //S6 button input
    TRISAbits.TRISA7 = 1; //S5 button input
    TRISDbits.TRISD13 = 1;//S4 button input
    
    
    
    len = strlen(arg2);
    display_write(arg2,len);  
    
    //Set multi-vector mode 
    INTCONbits.MVEC=1;   
    __builtin_disable_interrupts();  //Disable interrupts
    
    //Setting Interrupt Spe Registers
    //Interrupt 0
    INTCONbits.INT0EP = 0; //Trigger on falling edge 
    IPC0bits.INT0IP = 4;   //Set priority 4 
    IPC0bits.INT0IS = 0;   //Set subp 0
    IFS0bits.INT0IF = 0;   //Clear flag
    IEC0bits.INT0IE = 1;   //Set core timer enable

    //Interrupt 1
    INTCONbits.INT1EP = 0;   
    IPC1bits.INT1IP = 4;   
    IPC1bits.INT1IS = 0;    
    IFS0bits.INT1IF = 0;    
    IEC0bits.INT1IE = 1;    
       
    //Interrupt 2
    INTCONbits.INT2EP = 0;  
    IPC2bits.INT2IP = 4;    
    IPC2bits.INT2IS = 0;    
    IFS0bits.INT2IF = 0;   
    IEC0bits.INT2IE = 1;    

    //Interrupt 4
    INTCONbits.INT4EP = 0;   
    IPC4bits.INT4IP = 4;    
    IPC4bits.INT4IS = 0;    
    IFS0bits.INT4IF = 0;    
    IEC0bits.INT4IE = 1;   
    
   __builtin_enable_interrupts();       //Enable interrupts
   
    while (1){ 
        ;
    }
}

