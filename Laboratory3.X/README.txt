Name:   Tolga Furkan Aktas
Email:  taktas@u.rochester.edu
Date:   10/10/2018

I did not give or receive any unauthorized help, and all work is my own.

Lab: C Programming

    This lab exercise aims to practice C programming concepts by interacting
with the Explorer 16/32 board and PIC32MX795L board using C language, rather than
assembly. 

    In doing so, we experiment with digital i/o by entering data using switches
on the board. Each switch is in charge of a task (incr a, incr b, reset, 
switch_op) and lighting up the corresponding LED. 
   
    This task involved defining two header files, one for declaring math functions
and other for declaring display functions. In the source files with the same name,
the same functions are defined.

    In main.c, we use our function definitions from other source files to initialize
the display and necessary variables. We use an infinite for-loop to keep "listening"
for switch inputs and using the conditional statements, we implement the desired
behavior for each switch.