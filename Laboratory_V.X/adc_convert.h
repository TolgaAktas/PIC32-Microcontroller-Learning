/* 
 * File:   adc_convert.h
 * Author: tolgaaktas
 *
 * Created on October 18, 2018, 2:12 PM
 */

#ifndef ADC_CONVERT_H
#define	ADC_CONVERT_H

#define VOLTS_PER_COUNT 3.3/1024
#define CORE_TICK_TIME 25
#define SAMPLE_TIME 10
#define DELAY_TICKS 1000000

#include <xc.h>

unsigned int adc_sample_convert(int pin);

#endif	/* ADC_CONVERT_H */

