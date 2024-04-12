/*
 * ultra.c
 *
 *  Created on: 13 Oct 2022
 *      Author: Aly Tarek
 */


#include "ultra.h"
#include"icu.h"
#include"gpio.h"
#include<util/delay.h>

/*******************************************************************************
 *                      Global Variables                                  *
 *******************************************************************************/
static uint16 g_echotime=0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Ultrasonic_init(void){
	/*Initialize ICU */
	Icu_ConfigType Config_Ptr={F_CPU_8,RISING};
	Icu_init(&Config_Ptr);


	/*Setup callback function
		 */
		Icu_setCallBack(Ultrasonic_edgeProcessing);


		/*Setup Trigger PIN as output pin*/
	GPIO_setupPinDirection(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID, LOGIC_LOW);
}

void Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRA_TRIGGER_PORT_ID, ULTRA_TRIGGER_PIN_ID, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
return (g_echotime*0.017);
}

void Ultrasonic_edgeProcessing(void){
	static uint8 edgecount=0;

	edgecount++;
	if(edgecount==1){
		Icu_clearTimerValue();

		Icu_setEdgeDetectionType(FALLING);
	}
	else if(edgecount==2){
		/*
		 * store time taken
		 */
		g_echotime= Icu_getInputCaptureValue();

		Icu_setEdgeDetectionType(RISING);

		edgecount=0;
	}
}
