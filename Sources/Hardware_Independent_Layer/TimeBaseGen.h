/*
 * TimeBaseGen.h
 *
 *  Created on: Feb 5, 2015
 *      Author: Luis Ivan Escamilla Estrada
 */

#ifndef TIMEBASEGEN_H_
#define TIMEBASEGEN_H_

#include "StandarLibrary.h"
#include "../Hardware_Abstraction_Layer/TimerA.h"
/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define TBG_MAXIMUM_CHANNELS                    (5)
#define TBG_TIMER_DISABLE                       (0xFFFF)
#define TBG_RELOAD_TIMER_CHN(chn,period)        TBG_SoftwareTimers[chn] = period
#define TBG_DISABLE_TIMER_CHN(chn)              TBG_SoftwareTimers[chn] = TBG_TIMER_DISABLE
#define TBG_CHECK_TIMER_CHN_FLAG(chn)           (!TBG_SoftwareTimers[chn])

#define TBG_SOFTWARE_FLG						TBG_RefreshCounter
#define TBG_CHECK_SOFTWARE_FLG	                (TA_g1msFlag)
#define TBG_CLEAR_SOFTWARE_FLG                	TA_g1msFlag = FALSE

#define TBG_Polling_ISR_FLG						Polling_ISR_FLG
#define TBG_CHECK_TIMER_INT_FLAG                (TA_gChannelFlag)
#define TBG_CLEAR_TIMER_INT_FLAG                TA_gChannelFlag = FALSE

#define TBG_1MS_COUNTER							(0xFF95)
#define TBG_COUNTER_RESET						(0xFFFF)
/*************************************************************************************************/
/*********************					Extern Variables					**********************/
/*************************************************************************************************/
extern U16 TBG_SoftwareTimers[TBG_MAXIMUM_CHANNELS];
U08 TA_g1msFlag;
/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/
/**
 * Brief: Init TimerA (Hardware) and software timers by default are disabled
 * Params:    
 *         void 
 * return: void (nothing to return) 
 */
void TimeBaseGenerator_Init(void);
/**
 * Brief: this funtion decrement the soft timers, need to be called periodicaly 
 * Params:    
 *         void
 * return: void (nothing to return) 
 */
void TBG_RefreshChannels(void);

void TBG_RefreshCounter(void);

#endif /* TIMEBASEGEN_H_ */
