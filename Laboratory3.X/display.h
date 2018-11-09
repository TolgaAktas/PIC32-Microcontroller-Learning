/* 
 * File:   display.h
 * Author: taktas
 *
 * Created on October 4, 2018, 2:25 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#include <xc.h>
#include <stdlib.h>

void delay(long int cycles);
void display_enable();
void display_initialize();
void display_clear();
void display_write(char* data, int length);

#endif
