/* 
 * File:   UART_Comm.h
 * Author: tolgaaktas
 *
 * Created on October 18, 2018, 2:12 PM
 */

#ifndef UART_COMM_H
#define	UART_COMM_H

void WriteUART(const char * string){
    
    while(*string != '\0'){
        while(U3STAbits.UTXBF){;}
    }
    
    U3TXREG = *string;
    ++string;
}


#endif	/* UART_COMM_H */

