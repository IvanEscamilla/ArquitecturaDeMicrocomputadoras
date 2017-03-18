
	.set SYST_CSR_ADD,	0xe000e010	
	.set SYST_CSR_VAL,	0x00000003	
	.set SYST_RVR_ADD,	0xe000e014
	/*
	 * to get 10ms from the systick timer we need to set value of RVR = d30000
	 * tick = 48Mhz/16 = 3Mhz of clock source so t= 333.3333x10-9 s
	 *     t           value RVR 
	 * 333.3333x10-9       1
	 * 10x10-3           30,000 =   0x7530
	 * 50x10-3           150,000 =   0x249F0
	 * 1s				0x002DC6C0
	 **/
	.set SYST_RVR_VAL, 	0x000249F0
	.set SYST_CVR_ADD,	0xe000e018
	.set SYST_CVR_VAL, 	0x00000000
	

	.data /*Variables*/
	.align 2
	
	wLoopCounter: .word

/* This assembly file uses GNU syntax */
	.text
	.section	.rodata
	.align	2
	
	
.LC0:
	
	.text
	.align	2
	
	.global SysTick_Handler
	.type SysTick_Handler function
	
	.global SVC_Handler
	.type SVC_Handler function
	
	.global SysTick_Config
	.type SysTick_Config function
	
	.global Scheduler
	.type Scheduler function

	
Change_RegVal:
	push {LR}
	
	mov R0,#123
	mov R1,#12
	mov R2,#184
	mov R3,#200
	mov R4,#15
	mov R5,#1
	mov R6,#52
	mov R7,#98
	mov R8,R0
	mov R9,R1
	mov R10,R5
	mov R11,R7
	mov R12,R2

	pop {PC}


SVC_Handler:
	push {R0-R7,LR}
	
	mov R0,R8
	mov R1,R9
	mov R2,R10
	mov R3,R11
	mov R4,R12
	
	push {R0-R4}
	 /*Save the pointer to task stack*/
    /* MRS R0, MSP*/
    bl Set_Context   
    /*Branch to Contex Switcher*/
    /*bl Contex_Switcher*/
    /*Save the new stack pointer to the main stack pointer*/      	
	MSR MSP, R0
	
	pop {R0-R4}
	
	mov R8,R0
	mov R9,R1
	mov R10,R2
	mov R11,R3
	mov R12,R4	
		
	pop {R0-R7,PC}

SysTick_Handler:
	/*Save Context*/
	push {R0-R7,LR}
	
	mov R0,R8
	mov R1,R9
	mov R2,R10
	mov R3,R11
	mov R4,R12
	
	push {R0-R4}
	ldr R4, =systick
	ldr R5, [R4]
	add R5, #1
    str R5, [R4]
	
	/*Get direction memory to *sp of the task running
	and save the new dir of the stack pointer to it*/
	ldr  R0, =TaskRunning
	ldr  R1, [R0]
	ldr  R0, =Ready_queue
	lsl  R1, #2
	ldr  R0, [R1,R0]
    MRS R1, MSP
    str R1, [R0]
    /*Call for Scheduler*/
    b Scheduler
    /*bl scheduler_c*/
    /*Restoring Context for the new task*/
RESTORE_CONTEXT: 
    /*Save the new stack pointer to the main stack pointer*/      	
	MSR MSP, R0
	/*Restore Context*/
	pop {R0-R4}
	
	mov R8,R0
	mov R9,R1
	mov R10,R2
	mov R11,R3
	mov R12,R4	
		
	pop {R0-R7,PC}
	

SysTick_Config:
	push {R0,R1,LR}
	
	ldr R0, =SYST_RVR_ADD
	ldr R1, =SYST_RVR_VAL 
	str R1, [R0]
	
	ldr R0, =SYST_CVR_ADD
	ldr R1, =SYST_CVR_VAL
	str	R1, [R0]	
	
	ldr R0, =SYST_CSR_ADD
	ldr R1, =SYST_CSR_VAL
	str R1, [R0]
	
	pop {R0,R1,PC}


Scheduler:
   
   ldr R0, =TaskRunning		@if(Ready_queue[TaskRunning+1] == 0)
   ldr R1, [R0]
   add R1, #1				@TaskRunning+1
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1,R0]
   cmp R0, #0
   bne ELSE
   
   ldr R0, =TaskRunning		@Ready_queue[TaskRunning]->TaskState = eTaskReady;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1,R0]
   mov R2, #0				@eTaskReady
   strb R2, [R0, #10]		@store 0 at dir with offset of 10 
   
   ldr R0, =TaskRunning		@TaskRunning = 0;
   ldr R1, =0 				
   str R1, [R0]
   
   ldr R0, =TaskRunning		@Ready_queue[TaskRunning]->TaskState = eTaskRunning;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1,R0]
   mov R2, #3				@eTaskRunning
   strb R2, [R0, #10]		@store 3 at dir with offset of 10 
   
   ldr R0, =TaskRunning		@R0 = Ready_queue[TaskRunning]->pStack;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1, R0]
   ldr R0, [R0]
   b   RESTORE_CONTEXT
   
ELSE:			
   ldr R0, =TaskRunning		@Ready_queue[TaskRunning]->TaskState = eTaskReady;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1,R0]
   mov R2, #0				@eTaskReady
   strb R2, [R0, #10]		@store 0 at dir with offset of 10 
   
   ldr R0, =TaskRunning		@TaskRunning++;
   ldr R1, [R0]
   add R1, #1				
   str R1, [R0]
   
   ldr R0, =TaskRunning		@Ready_queue[TaskRunning]->TaskState = eTaskRunning;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1,R0]
   mov R2, #3				@eTaskRunning
   strb R2, [R0, #10]		@store 3 at dir with offset of 10 
   
   ldr R0, =TaskRunning		@R0 = Ready_queue[TaskRunning]->pStack;
   ldr R1, [R0]
   ldr R0, =Ready_queue
   lsl R1, #2
   ldr R0, [R1, R0]
   ldr R0, [R0]
   b   RESTORE_CONTEXT
   

			
	.align	2
.L3:
	.word	.LC0
	.end
