/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "MyTypes.h"
#include "Task.h"

typedef enum
{
	eConfigurationMode = 0,
	eWaitMode,
	eErrorState
}_eSystemState;
U08 Message[16] = "Hola Mundo!!";
u32 SchedulerSuspended = FALSE;
u32 TaskRunning = 0;
u32 TaskCount = 0;
u32 taskIndex;
u32 systick = 0;
u08	systemStatus;

void vfnSetClk48MHZ(void);
void StartScheduler(void);
void MAIN_vfnIdleTask(void);
void LCD_Task(void);
void LCD_PrintTask(void);

extern void SysTick_Config();
void SysTick_Stop(); 
void SysTick_Run();
extern void Scheduler_Init(); 

int main(void)
{
	vfnSetClk48MHZ();
	TimeBaseGenerator_Init();
	LCD_vFnInit();
	/*Needed for first run*/
	//TBG_RELOAD_TIMER_CHN(TIMER_LED,TIME_INIT);
	//TBG_RELOAD_TIMER_CHN(TIMER_DEBOUNCE,TIME_INIT);
	
	TASK_vfnTaskCreate(MAIN_vfnIdleTask,NULL,&main_stack[GetTaskCount()][STACKSIZE-1],TaskID_0);
	TASK_vfnTaskCreate(LCD_Task,NULL,&main_stack[GetTaskCount()][STACKSIZE-1],TaskID_1);
	TASK_vfnTaskCreate(LCD_PrintTask,NULL,&main_stack[GetTaskCount()][STACKSIZE-1],TaskID_2);

	StartScheduler();
	
	for(;;){	 
		
	}
	
	return 0;
}

void SysTick_Stop()
{
	u32 tempCsr = SYST_CSR;
	tempCsr &= ~(1 << SysTick_CSR_ENABLE_SHIFT);
	SYST_CSR = tempCsr;
}

void SysTick_Run()
{
	u32 tempCsr = SYST_CSR;
	tempCsr |= (1 << SysTick_CSR_ENABLE_SHIFT);
	SYST_CSR = tempCsr;
}

void StartScheduler(void)
{
	volatile u08 i;
	TaskCount = GetTaskCount();
	/*Search the first task to run, in order to never return from the scheduler 
	 * it was created an idle task that will be running if there is no more task
	 * to run. if there is a task will run imediately in other case will run the idle task
	 * 
	 * also fill queue for each task
	 * */
	if(TaskCount != 1)
	{
		/*there is at least one or more than idle task*/
		for(i=1;i<=MAXNUMBERTASKS;i++)
		{
			//fill ready queue
			if(TaskTable[i].pEntryPointTask != 0 && TaskTable[i].TaskState == eTaskReady)
			{
				Ready_queue[GetReadyCount()] = &TaskTable[i];
				addReadyCount();
				
			}
			else if (TaskTable[i].pEntryPointTask != 0 && TaskTable[i].TaskState == eTaskBlocked)
			{
				Blocked_queue[GetBlockedCount()] = &TaskTable[i];
				addBlockedCount();
			}	
		}
		
		SchedulerSuspended = FALSE;
	
	}
	else
	{
		/*there is not other task to run*/
		SchedulerSuspended = TRUE;
		taskIndex = TaskID_0;
	}
	
	//printf("Configuring Base time for Round Robin Scheduler.... \n");
	SysTick_Config();
		
	//force Context switch for the first task
	asm("SVC #0");
	
	for(;;)
	{
		
	}
	
}

void MAIN_vfnIdleTask(void)
{
	for(;;)
	{
		
	}
}

void LCD_Task(void)
{
	for(;;){
		LCD_vFnTask();
	}
}

void LCD_PrintTask(void){
	for(;;){
		if(LCD_gu8Status == eLCD_OK){
			LCD_vfnWriteMessage((U08*)&Message, wfnStrLen((U08*)&Message));
		}
	}
}

void vfnSetClk48MHZ(void)
{
   u08 temp_reg;
	
   SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV4(1); //Clock 1 output divider value
   
   MCG_C1 |= MCG_C1_IREFS_MASK;         // Select internal reference
		
   temp_reg = MCG_C4;
   
   temp_reg &= ~MCG_C4_DRST_DRS_MASK;    // Clear the DRS field 
   temp_reg |= MCG_C4_DRST_DRS(1);       // Mid range 
   temp_reg |= MCG_C4_DMX32_MASK;        // make sure DMX32 is set 
   
   MCG_C4 = temp_reg;
   
   /* Wait until FLL output is stable */
   while(MCG_S & MCG_S_CLKST_MASK);
   
}


/*
 * this funtion set the context for the first task to run*/
u32 Set_Context(void)
{
	Ready_queue[TaskRunning]->TaskState = eTaskRunning;
	return (u32)Ready_queue[TaskRunning]->pStack; //Return to main process using main stack
 }
