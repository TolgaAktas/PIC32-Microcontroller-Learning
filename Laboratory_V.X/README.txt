
Name:       Tolga Furkan Aktas
Email:      taktas@u.rochester.edu
Date:       10/23/2018

Academic Honesty: I did not give or receive any unauthorized help, and all work
on this assignment is my own.

I wrote a program to read analog inputs, specifically temperature sensor
and potentiometer readings, and map given analog inputs to a value between 0-1024,
mapping to a certain voltage value between 0 and 3.3V. I also implemented the
functionality for using switch button to switch display between temperature and 
potentiometer reading.

For this part, you have to wire P20 and P22 together, P21 and P24 together.

In the second part, I implemented the code to produce 1) a PWM signal with 500Hz
and 50% off duty cycle, 2) a PWM signal whose duty cycle is a linear function of
the analog input readings of temperature sensor and potentiometer.

For this part, you can test 1) by commenting out setDutyCycle function and wiring
P22 and P72 together. For
