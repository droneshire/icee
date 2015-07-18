/**
 * The timer module to manage global timer and update timers
 *
 * \file		tmr.h
 * \copyright	RDV Labs, LLC
 * \date		6/30/2015 10:42:34 PM
 * \author		Ross Yeager
 */ 

#ifndef TMR_H
#define TMR_H

#include "datatypes.h"

    void TMR_InitTimer(T_Timer * tmr);
    void TMR_Start__ms(T_Timer * tmr, T_U16 time_ms);
	void TMR_StartRepeating__ms(T_Timer * tmr, T_U16 time_ms);
	T_bool TMR_HasTripped(T_Timer * tmr);
	void TMR_SetStopwatch(T_Timer * tmr);
	T_U16 ms__TMR_GetStopwatch(T_Timer * tmr);
	T_U16 ms__TMR_SplitStopwatch(T_Timer * tmr);
	void TMR_Stop(T_Timer * tmr);

	#define TMR__ms_PER_sec         1000
	#define TMR_NOW                 0

#endif