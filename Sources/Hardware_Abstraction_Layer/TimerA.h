/*
 * TimerA.h
 *
 *  Created on: Feb 5, 2015
 *      Author: Luis Ivan Escamilla Estrada
 */

#ifndef TIMERA_H_
#define TIMERA_H_

#include "derivative.h"
#include "StandarLibrary.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define TA_CLOCK_INIT		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
#define TIME_MS				(1)

typedef enum
{
	eLPTPM_DIS = 0,
	eLPTPM_INC,
	eLPTPM_RISE,
	eLPTPM_RESERVED
}_eCMODConf;

typedef enum
{
	eDiv_1 = 0,
	eDiv_2,
	eDiv_4,
	eDiv_8,
	eDiv_16,
	eDiv_32,
	eDiv_64,
	eDiv_128
}_ePS;

typedef enum
{
	eCLOCK_DIS = 0,
	eMCGFLLCLK,
	eOSCERCLK,
	eMCGIRCLK
}_eTMPSRC;

/*************************************************************************************************/
/*********************					Global Variables					**********************/
/*************************************************************************************************/

U08 TA_gChannelFlag;

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
/**
 * Brief: Init TimerA (Hardware)
 * Params:    
 *         void 
 * return: void (nothing to return) 
 */
void TIMERA_INIT(void);

void Polling_ISR_FLG(void);

void TimerA_ISR(void);
#endif /* TIMERA_H_ */
