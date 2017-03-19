/*
 * Task.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Morita
 */

#ifndef TASK_H_
#define TASK_H_

#include "MyTypes.h"
#include "stdio.h"

//Define the number of tasks 
#define NUMBERTASKS 	(u08)(6)
//Define the number of tasks 
#define MAXNUMBERTASKS 	(u08)(6)
//#define STACKSIZE		(u08)(32)
//Define Stack size in bytes
//1byte 8bits
//128bytes 1024bits
//arreglo 32bits * 32 = 1024 bits = 128bytes
#define STACKSIZE		(u08)(32)

#define TaskID_0	(u08)(0)
#define TaskID_1	(u08)(1)
#define TaskID_2	(u08)(2)
#define TaskID_3	(u08)(3)
#define TaskID_4	(u08)(4)
#define TaskID_5	(u08)(5)
#define TaskID_6	(u08)(6)


typedef enum
{
	eTaskReady = 0,
	eTaskSuspended,
	eTaskBlocked,
	eTaskRunning,
	eTaskDeleted
}_eTaskState;

typedef struct
{
	u32 *pStack;
	void (*pEntryPointTask) (void);
	u08 TaskID;
	u08 TaskPriority; //not needed but defined for later use
	_eTaskState TaskState;
	
}_TaskDescriptor;

u32 main_stack[MAXNUMBERTASKS][STACKSIZE];
_TaskDescriptor TaskTable[MAXNUMBERTASKS];
_TaskDescriptor *Ready_queue[MAXNUMBERTASKS];
_TaskDescriptor *Blocked_queue[MAXNUMBERTASKS];
_TaskDescriptor *Suspended_queue[MAXNUMBERTASKS];

u16 GetTaskCount(void);
u16 GetReadyCount(void);
u16 GetBlockedCount(void);
void addReadyCount(void);
void addBlockedCount(void);
void del_task(void);
void TASK_vfnTaskReady(u08 ucTaskID);
u16 GetTaskCount(void);
void TASK_vfnTaskCreate(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID);
void TASK_vfnTaskCreateReady(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID);
void TASK_vfnTaskCreateBlocked(void (* const pTaskEntryPoint)(void),u08 ucPriority,u32 *stackPointer,u08 ucTaskID);

#endif /* TASK_H_ */
