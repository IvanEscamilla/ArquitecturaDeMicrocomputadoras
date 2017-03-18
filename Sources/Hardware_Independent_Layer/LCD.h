/*
 * LCD.h
 *
 *  Created on: Feb 3, 2015
 *      Author: Luis Ivan Escamilla Estrada / Francisco Javier Diaz Sanchez
 */

#ifndef LCD_H_
#define LCD_H_

#include "StandarLibrary.h"
#include "../Hardware_Abstraction_Layer/GPIO.h"
#include "TimeBaseGen.h"

/*************************************************************************************************/
/*********************                  Defines                     **********************/
/*************************************************************************************************/
#define LCD_TIMER_CH                    3 
#define TIME_INIT						1
#define LCD_TIMER                       2
#define LCD_SEND_COMMAND                0 
#define LCD_SEND_DATA                   1 
#define LCD_CLEAR                      0x01 			

/*************************************************************************************************/
/*********************                  Typedefs                  **********************/
/*************************************************************************************************/

typedef enum 
{
    eLCD_OK = 0,
    eLCD_BUSY,
}e_LcdStatus;

/*************************************************************************************************/
/*********************               Extern Variables               **********************/
/*************************************************************************************************/
/** Variable to indicated the LCD status*/
extern U08 LCD_gu8Status;

/*************************************************************************************************/
/*********************               Function Prototypes               **********************/
/*************************************************************************************************/

/* This function  is implemented to run the LCD state machine.
* @param void
* @return void
*/
void LCD_vFnTask(void);


/* This function  is implemented to LCD initialisation.
* @param void
* @return void
*/
void LCD_vFnInit(void);

/* This function  performs the LCD task.
* @param void
* @return void
*/
void LCD_vfnWriteMessage(U08* bpMessage, U08 Size);

/* This function perform goto X, Y to the LCD.
* @param 
* @return void
*/
void LCD_vfnGotoXY(U08 x, U08 y);

/* This function  performs the LCD task.
* @param void
* @return void
*/
void LCD_vfnClrScr(void);

/*************************************************************************************************/

#endif /* LCD_H_ */
