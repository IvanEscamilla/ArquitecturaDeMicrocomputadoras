/*
 * TimerA.c
 *
 *  Created on: Feb 5, 2015
 *      Author: Luis Ivan Escamilla Estrada
 */

#include "TimerA.h"

void TIMERA_INIT(void)
{
	TA_gChannelFlag = FALSE;
	TA_CLOCK_INIT;
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(eMCGFLLCLK);
	TPM0_CONF = TPM_CONF_DBGMODE(3); //Enable Debug Counting, 11 LPTPM counter continues in debug mode.
	TPM0_SC = TPM_SC_CMOD(eLPTPM_INC) | TPM_SC_PS(eDiv_1);
	/*Set timer as output compare*/
	TPM0_C0V = TPM_CnV_VAL(((TIME_MS * (48000000 / 1000)) / (1 << eDiv_1)));
	//TPM0_C0SC = (TPM_CnSC_CHIE_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK); //Chann INT enable, 11 10 Output compare Pulse Output low onmatch
	TPM0_C0SC = (TPM_CnSC_MSB_MASK | TPM_CnSC_MSA_MASK | TPM_CnSC_ELSB_MASK);
	/*Clear Interrupt*/
	//NVIC_ICPR |= (1 << eNVIC_TPM0);
	//NVIC_ISER |= (1 << eNVIC_TPM0);
	
}

void Polling_ISR_FLG(void)
{
	/* Clear Interrupt Flag */
	if((TPM0_C0SC & TPM_CnSC_CHF_MASK) == TPM_CnSC_CHF_MASK)
	{
		TPM0_C0SC |= TPM_CnSC_CHF_MASK;
		/* Reset the counter*/
		TPM0_CNT = 0x01;
		/* Set global Flag for TIMER A*/
		TA_gChannelFlag = TRUE;
	}
	else
	{
		//Do Nothing
	}
}
void TimerA_ISR(void)
{
	/* ISR generated because channel0 event */
	/* Clear Interrupt Flag */
	TPM0_C0SC |= TPM_CnSC_CHF_MASK;
	/* Reset the counter*/
	TPM0_CNT = 0x01;
	/* Set global Flag for TIMER A*/
	TA_gChannelFlag = TRUE;
}
