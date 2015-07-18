/**
 * \file		cntl.c
 *
 * \brief		The control system for temperature control
 * \copyright	RDV Labs, LLC
 * \date		6/30/2015 10:42:34 PM
 * \author		Ross Yeager
 */ 

#include "cntl.h"
#include "io.h"
 
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h> 

