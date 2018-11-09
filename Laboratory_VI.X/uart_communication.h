/* 
 * File:   uart_communication.h
 * Author: tolgaaktas
 *
 * Created on November 8, 2018, 7:23 PM
 */

#ifndef UART_COMMUNICATION_H
#define	UART_COMMUNICATION_H

#include <xc.h>

void initUART();

unsigned int readUART();

unsigned int writeUART(const char* data);



#endif	/* UART_COMMUNICATION_H */

