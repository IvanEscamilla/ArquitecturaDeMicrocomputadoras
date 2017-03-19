/*
 * TimeBaseGen.c
 *
 *  Created on: Feb 5, 2015
 *      Author: Luis Ivan Escamilla Estrada
 */

/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include "TimeBaseGen.h"

/*************************************************************************************************/
/*********************					Global Constants					**********************/
/*************************************************************************************************/

/** This Array has the time count for each software channel */
U16 TBG_SoftwareTimers[TBG_MAXIMUM_CHANNELS];
U16 TBG_gCounter;

/*************************************************************************************************/
/*********************					Functions	        				**********************/
/*************************************************************************************************/

void TimeBaseGenerator_Init(void)
{
    U08 u8Index = TBG_MAXIMUM_CHANNELS;

    /* Write 0xFFFF value to all timer channels, this means channel disable */
    while(u8Index--)
    {
    	TBG_SoftwareTimers[u8Index] = TBG_TIMER_DISABLE;
    }
    
    /* Enable FlexTimerA low level driver */
    //TIMERA_INIT();
    TBG_gCounter = 0xFFFF;
    TA_g1msFlag = FALSE;
}

void TBG_RefreshChannels(void)
{
    U08 u8Index = TBG_MAXIMUM_CHANNELS;

    /* Poll all channels */
    while(u8Index--)
    {
        if(TBG_SoftwareTimers[u8Index] != TBG_TIMER_DISABLE)
        {
            /* Channel enable */
            if(TBG_SoftwareTimers[u8Index])
            {
                /* Channel higher than zero, then decrement by one */
            	TBG_SoftwareTimers[u8Index]--;
            }
        }
    }
}
   
void TBG_RefreshCounter(void)
{
	if(TBG_gCounter == 0)
	{
		TBG_gCounter = TBG_COUNTER_RESET;
	}
	else if(TBG_gCounter <= TBG_1MS_COUNTER)
	{
		TA_g1msFlag = TRUE;
		TBG_gCounter = TBG_COUNTER_RESET;
	}
	else
	{
		TBG_gCounter--;
	}
}
