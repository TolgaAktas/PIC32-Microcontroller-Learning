#include "math_ops.h"
#include "display.h"
#include <xc.h>
#include <stdlib.h>
#include <string.h>

int main(){

    //SET LEDS AS OUTPUT
    TRISA = 0x0000;
    //DDPCON = 0x0000;
    DDPCONbits.JTAGEN = 0;
    LATA = 0x0000;
    
    TRISD = 0x0000;
    //SET SWITCHES AS INPUTS
    TRISDbits.TRISD6 = 1; //S3 button input
    TRISDbits.TRISD7 = 1; //S6 button input
    TRISAbits.TRISA7 = 1; //S5 button input
    TRISDbits.TRISD13 = 1;//S4 button input
    
    display_initialize();
    
    char arg2[100];
    int length = strlen(arg2);
    
    math_ops_t math_ops; 
    math_ops_init(&math_ops);           //Initialize math_ops to a+b=0
    math_ops_display(&math_ops,arg2);   //Store the math_ops as a string in arg2
    display_write(arg2,length);         //Write arg2 to display
    
    int ctr = 0;
    
 
    while(1){
        
        
        if(PORTDbits.RD6==0){               //If S3 is pressed
            LATAbits.LATA0=1;               //Set LED3 on
            math_ops.a = math_ops.a + 1;    //Increment operator a
            math_ops_update(&math_ops);     //Update the operation result
            display_clear();                //Display clear for rewrite
            math_ops_display(&math_ops,arg2); //Turn the ops into string
            display_write(arg2,length);     //Write the operation string to display
        }else{
            LATAbits.LATA0=0;               //Set it zero when released
        }
        
        if(PORTDbits.RD13==0){                  //If S4 is pressed
            LATAbits.LATA1 = 1;                 //Set LED4 on   
            math_ops_init(&math_ops);           //Reset the operation to init
            math_ops_display(&math_ops,arg2);   //Create its string
            display_clear();                    //Clear screen for rewrite
            display_write(arg2,length);         //Write reset string
        }else{
            LATAbits.LATA1 = 0;               //Set it zero when released
        }
        
        
        if(PORTAbits.RA7==0){           //If S5 is pressed
            
            LATAbits.LATA2=1;
            
            //This basically rotates the operation in the direction ADD->SUBTRACT->MULTIPLY->ADD->...
            if(ctr<2){
                math_ops.operator++;
                ctr++;
                
                math_ops_update(&math_ops);
                display_clear();
                math_ops_display(&math_ops,arg2);
                display_write(arg2,length);   
            }else{
                ctr = 0;
                display_clear();
                math_ops.operator=ADD;
                math_ops_update(&math_ops);
                math_ops_display(&math_ops,arg2);
                display_write(arg2,length);
            }
        }else{
            LATAbits.LATA2=0;           //Set it zero when released
        }
        
        //This block does the same operation as S3 except for operator b with S6
        if(PORTDbits.RD7==0){           //If S6 is pressed
            LATAbits.LATA3=1;
            math_ops.b = math_ops.b + 1;
            math_ops_update(&math_ops);
            display_clear();
            math_ops_display(&math_ops,arg2);
            display_write(arg2,length);
            
        }
        
//        LATAbits.LATA0 = ~PORTDbits.RD6;
//        LATAbits.LATA1 = ~PORTDbits.RD13;
//        LATAbits.LATA2 = ~PORTAbits.RA7;
//        LATAbits.LATA3 = ~PORTDbits.RD7;
        
        delay(5000);
       
    }
    return 0;
}
