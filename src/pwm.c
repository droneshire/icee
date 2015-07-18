/**
 * \file		pwm.c
 *
 * \brief		Driver for all PWM activity.  Used by the LED and TEC 
 *				modules.
 * \copyright	RDV Labs, LLC
 * \date		6/30/2015 10:42:34 PM
 * \author		Ross Yeager
 */ 

#include "pwm.h"
#include "io.h"
 
#include <avr/interrupt.h>