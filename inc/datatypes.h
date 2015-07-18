/**
 * Consolidated datatypes utilized through the project
 *
 * \file		datatypes.h
 * \copyright	RDV Labs, LLC
 * \date		6/30/2015 10:42:34 PM
 * \author		Ross Yeager
 */ 

#ifndef DATATYPES_H
#define DATATYPES_H

// AVR specific modules
#include <util/delay.h>


typedef unsigned char		T_U8;
typedef signed char			T_S8;
typedef unsigned int		T_U16;
typedef signed int			T_S16;
typedef unsigned long int	T_U32;
typedef signed long int		T_S32;

typedef T_U8				T_bool;
typedef const char*			T_string;

#define HIGH				1
#define LOW					0

#define TRUE				1
#define FALSE				0

typedef T_U16				T_Time;
typedef T_S16				T_STime;

/** Stucture to create an arbitrary number of timers based on 
*	Timer 1 global clock.
*/ 
typedef struct 
{
	T_bool	is_active			: 1;
	T_bool	is_repeating		: 1;
	T_bool	is_passed			: 1;
	T_Time	trigger_time__ms;
	T_Time	repeat_time__ms;
}T_Timer;

/** Union to access 16-bit words as a whole or as lsb/msb */ 
typedef union
{
	struct  
	{
		T_U8 word_msb;
		T_U8 word_lsb;
	};
	T_U16 raw;
}T_word;

#endif