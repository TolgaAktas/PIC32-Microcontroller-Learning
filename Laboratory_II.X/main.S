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
    la s0,TRISD
    li t0,0x0000
    sw t0,0(s0)
    
    //Set enable=1, RW = 0 
    la s0,LATD
    li t0,0b0000000000010000
    sw t0,0(s0)
    
    li a2,1000
    jal delay
    
    //Set RS = 0
    la s1,TRISB
    li t1,0x0000
    sw t1,0(s1)
    la s1,LATB
    li t1,0x0000
    sw t1,0(s1)
    
    //Set enable=0
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
   
    //Set DB registers
    la s2,TRISE
    li t2,0x0000
    sw t2,0(s2)
    la s2,LATE
    li t2,0x0038 
    sw t2,0(s2)
    
    li a2,20000
    jal delay
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
    
    //Display ON/OFF Control
    li t2,0x000F
    sw t2,0(s2)
    
    li a2,20000
    jal delay
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
    
    //Clear Display
    li t2,0x0001
    sw t2,0(s2)
    
    li a2,40000
    jal delay
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
    
    //Entry Mode Set
    li t2,0x0006
    sw t2,0(s2)
    nop
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    //END OF INITIALIZATION
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
    
    //Set RS = 1 at s1
    li t1,0x8000
    sw t1,0(s1)
    
    li a2,10000
    jal delay
    
    //Write letter N 
    li t2,0x004E
    sw t2,0(s2)
    nop
    
    li a2,40000
    jal delay
    
    //Set RS = 0 at s1
    li t1,0x0000
    sw t1,0(s1)
    nop
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    
    
    //Set enable=1, RW = 0 
    li t0,0b0000000000010000
    sw t0,0(s0)
    nop
    
    //Set RS = 1 at s1
    li t1,0x8000
    sw t1,0(s1)
    
    li a2,10000
    jal delay
    
    
    //write a  

    li t2,0x0061
    sw t2,0(s2)
    nop
    
    li a2,40000
    jal delay
    
    //Set RS = 0 at s1
    li t1,0x0000
    sw t1,0(s1)
    nop
    
    //Set enable=0, RW = 0 
    li t0,0b0000000000000000
    sw t0,0(s0)
    nop
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   
    
    
   
.end main