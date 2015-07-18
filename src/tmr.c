/**
 * \file	tmr.c
 *
 * \brief	Handles all setup and updating of the timers used
 *		throughout the project.  It sets up a global clock and 
 *		sets timeouts as increments from the current clock to 
 *		effectively use as many clocks as necessary.
 *
 * \copyright	RDV Labs, LLC
 * \date	6/30/2015 10:42:34 PM
 * \author	Ross Yeager
 */ 

#include "tmr.h"

#include <avr/io.h>
#include <avr/interrupt.h>

 // A free running timer in milliseconds, updated by the hardware timer
static volatile T_U16 freeRunningClock_ms;

/** Setup the timer registers and the interrupts.
 */
void TMR_Init(void)
{
    freeRunningClock_ms = 0;


}


/** Initialize a new software timer.
 *  Despite the logic of the current implementation, always call this function
 *  on new timers. (Future implementation might perform differently.)
 */
void TMR_InitTimer(T_Timer * tmr)
{
    //All we need to make sure is that the timer is off.
    tmr->active = 0;
    tmr->stopwatch = 0;
}


/** Start a one-shot timer.
 *  Note: this system has a maximum timer value of 32 milliseconds.
 */
void TMR_Start__ms(T_Timer * tmr, T_U16 time_ms)
{
	if(time_ms > 32)
	{
		time_ms = 32;
	}

    //Set the trigger point in the future
    tmr->trigger_time_ms = freeRunningClock_ms + time_ms;

    //This is not a repeating timer (this HAS to be zero to enable one-shot)
    tmr->repeating_period_ms = 0;

    tmr->stopwatch = 0;
    tmr->active = 1;
}


/** Start a repeating timer.
 *  Note: this system has a maximum timer value of 32 milliseconds.
 */
void TMR_StartRepeating__ms(T_Timer * tmr, T_U16 time_ms)
{
	if(time_ms > 32)
	{
		time_ms = 32;
	}

    //Set the trigger point in the future
    tmr->trigger_time_ms = freeRunningClock_ms + time_ms;

    //This is a repeating timer, we need to store the period
    tmr->repeating_period_ms = time_ms;

    tmr->stopwatch = 0;
    tmr->active = 1;
}

/** Poll a timer to see if it has expired.
 *  One-shot timers will disable themselves after returning true.
 *  Repeating timers will re-arm themselves after returning true.
 */
T_bool TMR_HasTripped(T_Timer * tmr)
{
    //Are we even active?
    if (tmr->active)
    {
        /* Find the difference between the current timer value and the
         * the trigger point, if the timer is has not trigger, then the value
         * will be negative. We need to cast to signed values to test for
         * negative values.
         */
        if ( ((T_S16)(freeRunningClock_ms - tmr->trigger_time_ms)) >= 0)
        {
            //Are we a repeating timer?
            if (tmr->repeating_period_ms)
            {
                //Reset the timer
                tmr->trigger_time_ms += tmr->repeating_period_ms;
            }
            else
            {
                //No, we are one-shot
                tmr->active = 0;
            }

            //We did trigger the timer!
            return 1;
        }
    }

    return 0;
}

/// Take a snapshot of the current time for an interval timing.
void TMR_SetStopwatch(T_Timer * tmr)
{
    //Grab the current time
    tmr->trigger_time_ms = freeRunningClock_ms;

    tmr->stopwatch = 1;
    tmr->active = 0;
}

/// How long has it been since the interval was sampled?
T_U16 ms__TMR_GetStopwatch(T_Timer * tmr)
{
    if (tmr->stopwatch)
    {
        return freeRunningClock_ms - tmr->trigger_time_ms;
    }
    else
    {
        return 0;
    }
}

/* Simulatenously get an interval while resetting the stopwatch.
 * This function happens atomically making sure we only save the clock once.
 */
T_U16 ms__TMR_SplitStopwatch(T_Timer * tmr)
{
    T_U16 clock;
    T_U16 last_clock;

    if (tmr->stopwatch)
    {
        //We can only sample freeRunningClock_ms once! It's volatile!
        clock = freeRunningClock_ms;
        //Save the old reading since we need it for interval.
        last_clock = tmr->trigger_time_ms;

        tmr->trigger_time_ms = clock;
        return clock - last_clock;
    }
    else
    {
        return 0;
    }
}


/** Stop a timer.
 */
void TMR_Stop(T_Timer * tmr)
{
    tmr->active = 0;
    tmr->stopwatch = 0;
}


/** Access to the free running clock.
 */
T_U16 TMR_Clock(void)
{
    return freeRunningClock_ms;
}

// Timer interrupt routine. Simply increments the timer.
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    //Clear flag
    IFS0bits.T1IF = 0;

    freeRunningClock_ms++;
}
