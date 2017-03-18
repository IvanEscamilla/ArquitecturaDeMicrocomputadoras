/*
 * Task.c
 *
 *  Created on: Oct 15, 2014
 *      Author: Morita
 */

#include "Task.h"

#define MAIN_RETURN 0xFFFFFFF9  //Tells the handler to return using the MSP
#define THREAD_RETURN 0xFFFFFFFD //Tells the handler to return using the PSP
#define XPSR 0x01000000 //Default xpsr

u16 usTaskCount = 0;//Initialising Task Count
u32 ReadyCount = 0;
u32 BlockedCount = 0;

u16 GetTaskCount(void)
{
  return usTaskCount;
}
u16 GetReadyCount(void)
{
  return ReadyCount;
}
u16 GetBlockedCount(void)
{
  return BlockedCount;
}
void addReadyCount(void)
{
   ReadyCount++;
}
void addBlockedCount(void)
{
  BlockedCount++;
}
//This is called when the task returns or finishes
void del_task(void){
  TaskTable[usTaskCount].TaskState = eTaskDeleted; //clear the in use and exec flags
  while(1); //once the context changes, the program will no longer return to this thread
}
//Task create by the user
void TASK_vfnTaskReady(u08 ucTaskID)
{
	u16 i;
	u08 Finish = FALSE;
	/*Find the task to be change to ready state and put it to the Readyqueue 
	 * in order that the scheduler could exec that task, delet the task in the 
	 * bloquedqueue and insert it to Readyqueue*/
	for(i=0;i<=BlockedCount;i++)
	{
		//find 
		if(Blocked_queue[i]->TaskID == ucTaskID)
		{
			Ready_queue[ReadyCount] = Blocked_queue[i];
			Ready_queue[ReadyCount]->TaskState = eTaskReady;
			ReadyCount++;
			BlockedCount--;
			Blocked_queue[i] = 0;
		}
		else 
		{
			
		}	
	}
	/*Reordering Blockedqueue*/
	i=0;
	do
	{
		if(Blocked_queue[i] == 0)
		{
			if(Blocked_queue[i+1]==0)
			{
				Finish = TRUE;
			}
			else
			{			
			Blocked_queue[i] = Blocked_queue[i+1];
			Blocked_queue[i+1] = 0;
			}
		}
		else 
		{
			
		}	
	i++;
	}while(Finish != TRUE);
	
}



/*This Function Creates a task as ready and put it into the array of ready tasks and increments the global variable usTaskCount 
 * for the next task  to be added 
 * Params:
 *  void (*pTask)(void) - Entry point to task
 *  ucPriority			- Variable to set priority to task, not used right now but for upgrading later
 *  ucTaskID			- ID given to the task, it will be assigned by the user (it could be assigned automatically?)
 *  
 *  Return 
 *   void
 * */
void TASK_vfnTaskCreate(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID)
{		
	//store task address (Entry Point)
	TaskTable[usTaskCount].pEntryPointTask = pTaskEntryPoint;
	//store task priority. not used right now def NULL = 0
	TaskTable[usTaskCount].TaskPriority = ucPriority;
	//store Task ID it is assigned by the user at the moment he creates the task by default TaskID_0 is for IDLE Task
	TaskTable[usTaskCount].TaskID = ucTaskID;
	//Set the task Ready run
	TaskTable[usTaskCount].TaskState = eTaskReady;
	//Save stack pointer
	TaskTable[usTaskCount].pStack =  stackPointer;
    /*Stack*/
	*(TaskTable[usTaskCount].pStack   ) = 	XPSR;//XPSR  <-End of stack
	*(TaskTable[usTaskCount].pStack -1) = 	(u32)pTaskEntryPoint + 1;//PC
	*(TaskTable[usTaskCount].pStack -2) = 	(u32)pTaskEntryPoint + 1;//LR
	*(TaskTable[usTaskCount].pStack -3) = 	(u32)0;//R12
	*(TaskTable[usTaskCount].pStack -4) = 	(u32)0;//R3
	*(TaskTable[usTaskCount].pStack -5) = 	(u32)0;//R2
	*(TaskTable[usTaskCount].pStack -6) = 	(u32)0;//R1
	*(TaskTable[usTaskCount].pStack -7) = 	(u32)0;//R0
	*(TaskTable[usTaskCount].pStack -8) = 	MAIN_RETURN;//LR with the EXEC_RETURN
	*(TaskTable[usTaskCount].pStack -9) = 	(u32)8;//R7
	*(TaskTable[usTaskCount].pStack -10) = 	(u32)7;//R6
	*(TaskTable[usTaskCount].pStack -11) = 	(u32)6;//R5
	*(TaskTable[usTaskCount].pStack -12) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -13) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -14) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -15) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -16) = 	(u32)1;//R0
	*(TaskTable[usTaskCount].pStack -17) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -18) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -19) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -20) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -21) = 	(u32)1;//R0
	//*(TaskTable[usTaskCount].pStack -8) = (u32)MAIN_RETURN;//MAIN_RETURN
	//*(TaskTable[usTaskCount].pStack -9) = (u32)pTaskEntryPoint + 1;;//R7
	TaskTable[usTaskCount].pStack  =  stackPointer -21;//with offset

	//Incrementing usTaskCount
	usTaskCount++;
	
}	 

/*This Function Creates a task as ready and put it into the array of ready tasks and increments the global variable usTaskCount 
 * for the next task  to be added 
 * Params:
 *  void (*pTask)(void) - Entry point to task
 *  ucPriority			- Variable to set priority to task, not used right now but for upgrading later
 *  ucTaskID			- ID given to the task, it will be assigned by the user (it could be assigned automatically?)
 *  
 *  Return 
 *   void
 * */
void TASK_vfnTaskCreateReady(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID)
{	
	//store task address (Entry Point)
	TaskTable[usTaskCount].pEntryPointTask = pTaskEntryPoint;
	//store task priority. not used right now def NULL = 0
	TaskTable[usTaskCount].TaskPriority = ucPriority;
	//store Task ID it is assigned by the user at the moment he creates the task by default TaskID_0 is for IDLE Task
	TaskTable[usTaskCount].TaskID = ucTaskID;
	//Set the task Ready run
	TaskTable[usTaskCount].TaskState = eTaskReady;
	//Save stack pointer
	TaskTable[usTaskCount].pStack =  stackPointer;
    /*Stack*/
	*(TaskTable[usTaskCount].pStack   ) = 	XPSR;//XPSR  <-End of stack
	*(TaskTable[usTaskCount].pStack -1) = 	(u32)pTaskEntryPoint + 1;//PC
	*(TaskTable[usTaskCount].pStack -2) = 	(u32)pTaskEntryPoint + 1;//LR
	*(TaskTable[usTaskCount].pStack -3) = 	(u32)0;//R12
	*(TaskTable[usTaskCount].pStack -4) = 	(u32)0;//R3
	*(TaskTable[usTaskCount].pStack -5) = 	(u32)0;//R2
	*(TaskTable[usTaskCount].pStack -6) = 	(u32)0;//R1
	*(TaskTable[usTaskCount].pStack -7) = 	(u32)0;//R0
	*(TaskTable[usTaskCount].pStack -8) = 	MAIN_RETURN;//LR with the EXEC_RETURN
	*(TaskTable[usTaskCount].pStack -9) = 	(u32)8;//R7
	*(TaskTable[usTaskCount].pStack -10) = 	(u32)7;//R6
	*(TaskTable[usTaskCount].pStack -11) = 	(u32)6;//R5
	*(TaskTable[usTaskCount].pStack -12) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -13) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -14) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -15) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -16) = 	(u32)1;//R0
	*(TaskTable[usTaskCount].pStack -17) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -18) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -19) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -20) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -21) = 	(u32)1;//R0
	//*(TaskTable[usTaskCount].pStack -8) = (u32)MAIN_RETURN;//MAIN_RETURN
	//*(TaskTable[usTaskCount].pStack -9) = (u32)pTaskEntryPoint + 1;;//R7
	TaskTable[usTaskCount].pStack  =  stackPointer -21;//with offset.

	//Incrementing usTaskCount
	usTaskCount++;
}


/*This Function Creates a task as ready and put it into the array of ready tasks and increments the global variable usTaskCount 
 * for the next task  to be added 
 * Params:
 *  void (*pTask)(void) - Entry point to task
 *  ucPriority			- Variable to set priority to task, not used right now but for upgrading later
 *  ucTaskID			- ID given to the task, it will be assigned by the user (it could be assigned automatically?)
 *  
 *  Return 
 *   void
 * */
void TASK_vfnTaskCreateBlocked(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID)
{	
	//store task address (Entry Point)
	TaskTable[usTaskCount].pEntryPointTask = pTaskEntryPoint;
	//store task priority. not used right now def NULL = 0
	TaskTable[usTaskCount].TaskPriority = ucPriority;
	//store Task ID it is assigned by the user at the moment he creates the task by default TaskID_0 is for IDLE Task
	TaskTable[usTaskCount].TaskID = ucTaskID;
	//Set the task Ready run
	TaskTable[usTaskCount].TaskState = eTaskBlocked;
	//Save stack pointer
	TaskTable[usTaskCount].pStack =  stackPointer;
    /*Stack*/
	*(TaskTable[usTaskCount].pStack   ) = 	XPSR;//XPSR  <-End of stack
	*(TaskTable[usTaskCount].pStack -1) = 	(u32)pTaskEntryPoint + 1;//PC
	*(TaskTable[usTaskCount].pStack -2) = 	(u32)pTaskEntryPoint + 1;//LR
	*(TaskTable[usTaskCount].pStack -3) = 	(u32)0;//R12
	*(TaskTable[usTaskCount].pStack -4) = 	(u32)0;//R3
	*(TaskTable[usTaskCount].pStack -5) = 	(u32)0;//R2
	*(TaskTable[usTaskCount].pStack -6) = 	(u32)0;//R1
	*(TaskTable[usTaskCount].pStack -7) = 	(u32)0;//R0
	*(TaskTable[usTaskCount].pStack -8) = 	MAIN_RETURN;//LR with the EXEC_RETURN
	*(TaskTable[usTaskCount].pStack -9) = 	(u32)8;//R7
	*(TaskTable[usTaskCount].pStack -10) = 	(u32)7;//R6
	*(TaskTable[usTaskCount].pStack -11) = 	(u32)6;//R5
	*(TaskTable[usTaskCount].pStack -12) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -13) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -14) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -15) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -16) = 	(u32)1;//R0
	*(TaskTable[usTaskCount].pStack -17) = 	(u32)5;//R4
	*(TaskTable[usTaskCount].pStack -18) = 	(u32)4;//R3
	*(TaskTable[usTaskCount].pStack -19) = 	(u32)3;//R2
	*(TaskTable[usTaskCount].pStack -20) = 	(u32)2;//R1
	*(TaskTable[usTaskCount].pStack -21) = 	(u32)1;//R0
	//*(TaskTable[usTaskCount].pStack -8) = (u32)MAIN_RETURN;//MAIN_RETURN
	//*(TaskTable[usTaskCount].pStack -9) = (u32)pTaskEntryPoint + 1;;//R7
	TaskTable[usTaskCount].pStack  =  stackPointer -21;//with offset.

	//Incrementing usTaskCount
	usTaskCount++;
}
