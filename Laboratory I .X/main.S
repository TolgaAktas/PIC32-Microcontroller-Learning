/*
    Author: Tolga F. Aktas
    File: main.S
    Date: 09/13/2018
    Description: Introduction to Assembly programming
     
     
     README:
     Tolga F. Aktas, taktas@u.rochester.edu 09/13/2018
    I affirm that I have not given or received any unauthorized help on this laboratory assignment, and that all work is my own.
    
    The assignment starts off with implementing the given code and observing the effects on the LED lights on the development board. This is
     an introduction to assembly programming.
     
     Later, I manipulated the given code to complete part I and II of the assignment, setting D3,4,7,8 at start and toggling lights by xor-ing
     the bit vector by a mask of all one values.
     
    
 */
    
#include <xc.h>
    .global main
    .text
    .set noreorder
   
.ent delay
    delay:
	beq	a2,zero,exitdelay
	nop
	addi	a2,a2,-1
	j delay
	nop
.end delay
	
.ent exitdelay
	exitdelay:
	    jr	ra
	    nop
.end exitdelay
	
.ent main
main:
    la	s0,TRISA
    li	t0,0x0000
    sw	t0,0(s0)
    la	s0,DDPCON
    li	t0,0x0000
    sw	t0,0(s0)
    la	s0,LATA
    li	t0,0b00110011
    sw	t0,0(s0)
    nop
endless:
    li	a2,150000
    jal	delay
    la	s0,LATA
    lw	t0,0(s0)
    xor	t0,t0,0b11111111
    sw	t0,0(s0)
    j	endless
    nop
.end main