/*
 * icu.c
 *
 *  Created on: 13 Oct 2022
 *      Author: Aly Tarek
 */

#include"icu.h"
#include<avr/io.h>
#include "common_macros.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect){
	if(*g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void Icu_init(const Icu_ConfigType * Config_Ptr){
	/* Set Pin 6 as Input Pin*/
	DDRD &= ~(1<<PD6);

	TCCR1A = (1<<FOC1A) | (1<<FOC1B); //non PWM mode
	/*	Set Edge RISING/FALLING
	 */
	TCCR1B= (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);
	/*Configure Clock
	 */
	TCCR1B= (TCCR1B & 0xF8) | (Config_Ptr->clock);

	TCNT1=0;

	ICR1=0;
/*
 * Enable I-bit in status register
 */
	TIMSK |= (1<<TICIE1);
}

void Icu_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}
/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const Icu_EdgeSet a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}


