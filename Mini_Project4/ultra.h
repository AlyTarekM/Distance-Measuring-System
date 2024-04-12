/*
 * ultra.h
 *
 *  Created on: 13 Oct 2022
 *      Author: Aly Tarek
 */

#ifndef ULTRA_H_
#define ULTRA_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRA_TRIGGER_PORT_ID PORTB_ID
#define ULTRA_TRIGGER_PIN_ID PIN5_ID

#define ULTRA_ECHO_PORT PORTD_ID
#define ULTRA_ECHO_PIN  PIN6_ID



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRA_H_ */
