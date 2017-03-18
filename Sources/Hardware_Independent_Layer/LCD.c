/*
 * LCD.c
 *
 *  Created on: Feb 3, 2015
 *      Author: Luis Ivan Escamilla Estrada / Francisco Javier Diaz Sanchez
 */

/*************************************************************************************************/
/*********************                      Includes                        **********************/
/*************************************************************************************************/

#include "LCD.h"

/*************************************************************************************************/
/*********************                      Defines                         **********************/
/*************************************************************************************************/

#define CLOCK_PORTS2LCD                 GPIO_ENABLE_MODULE_CLOCK(PORTD)

#define LCD_PIN_RS_INIT                 GPIO_ENABLE_MODULE_CLOCK(PORTD);\
                                        GPIO_CONFIG_PIN_FUNCTION(D,0,GPIO);\
                                        GPIO_CONFIG_PIN_AS_OUTPUT(D,0)

#define LCD_PIN_E_INIT                  GPIO_ENABLE_MODULE_CLOCK(PORTD);\
                                        GPIO_CONFIG_PIN_FUNCTION(D,1,GPIO);\
                                        GPIO_CONFIG_PIN_AS_OUTPUT(D,1)

#define LCD_PIN_RS(Bit)	                GPIO_WRITE_PIN(D,0,Bit)

#define LCD_PIN_E(Bit)	                GPIO_WRITE_PIN(D,1,Bit)

#define LCD_READ_BF						GPIO_ENABLE_MODULE_CLOCK(PORTD);\
										GPIO_CONFIG_PIN_AS_INPUT(D,2)

#define LCD_SET_PIN_BF_INPUT			GPIO_ENABLE_MODULE_CLOCK(PORTD);\
										GPIO_CONFIG_PIN_AS_INPUT(D,2)
										
#define LCD_SET_PIN_DATA_AS_OUTPUT      GPIO_ENABLE_MODULE_CLOCK(PORTD);\
										GPIO_CONFIG_PIN_AS_OUTPUT(D,2); \
                                        GPIO_CONFIG_PIN_AS_OUTPUT(D,3); \
                                        GPIO_CONFIG_PIN_AS_OUTPUT(D,4); \
                                        GPIO_CONFIG_PIN_AS_OUTPUT(D,5); \
                                        GPIO_CONFIG_PIN_FUNCTION(D,2,GPIO); \
                                        GPIO_CONFIG_PIN_FUNCTION(D,3,GPIO); \
                                        GPIO_CONFIG_PIN_FUNCTION(D,4,GPIO); \
                                        GPIO_CONFIG_PIN_FUNCTION(D,5,GPIO)

#define LCD_WRITE_DATA_PORT(data)       GPIO_WRITE_PIN(D,2,(data & 0x01));\
										GPIO_WRITE_PIN(D,3,((data & 0x02)>>1));\
										GPIO_WRITE_PIN(D,4,((data & 0x04)>>2));\
										GPIO_WRITE_PIN(D,5,((data & 0x08)>>3));\


#define LCD_SET_PIN_DATA_AS_INPUT     	GPIO_ENABLE_MODULE_CLOCK(PORTD);\
										GPIO_CONFIG_PIN_AS_INPUT(D,2); \
										GPIO_CONFIG_PIN_AS_INPUT(D,3); \
										GPIO_CONFIG_PIN_AS_INPUT(D,4); \
										GPIO_CONFIG_PIN_AS_INPUT(D,5); \
										GPIO_CONFIG_PIN_FUNCTION(D,2,GPIO); \
										GPIO_CONFIG_PIN_FUNCTION(D,3,GPIO); \
										GPIO_CONFIG_PIN_FUNCTION(D,4,GPIO); \
										GPIO_CONFIG_PIN_FUNCTION(D,5,GPIO)

/*************************************************************************************************/
/*********************                      Typedefs                        **********************/
/*************************************************************************************************/

typedef enum
{
    eLCD_IDLE = 0,
    eLCD_WRITE_MSB_DATA,
    eLCD_WRITE_LSB_DATA,
    eLCD_FINISH_SEND_DATA, 
    eLCD_MORE_DATA,/*5*/
}_eLCD_Task;

/**Variable to indicate the LCD Machine States*/
static _sStateMachine LCD_StateMachine;

/*************************************************************************************************/
/*********************                  Function Prototypes                 **********************/
/*************************************************************************************************/
/* This function is implemented to indicate "do nothing".
* @param void
* @return void
*/
static void LCD_vFnIDLE(void);

/* This function  is implemented to write the Most Significant Bits of Data.
* @param void
* @return void
*/
static void LCD_vFnWriteMSBData(void);

/*  This function  is implemented to write the Least Significant Bits of Data.
* @param void
* @return void
*/
static void LCD_vFnWriteLSBData(void);

/* This function is implemented to indicate that the write Data is done.
* @param void
* @return void
*/
static void LCD_vFnFinishSendData(void);

/* This function  is implemented to run the state machine 'till the message is completely sended.
* @param void
* @return void
*/
static void LCD_vFnWriteMoreData(void);


/*************************************************************************************************/
/*********************                  Static Variables                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Global Variables                    **********************/

/*************************************************************************************************/

/**Variable to indicate if the LCD is already initialised*/
U08 LCD_gu8Initialized;
/**Variable to indicate if it need send a command or data*/
U08 LCD_gu8RS;
/**Variable to save the data size and use to validate if we have more data to send*/
U16 LCD_gu16SizeData;
/**Pointer to received the data address*/
U08 *LCD_gpt08Mensage;
/**Variable to indicate what data send*/
U16 LCD_gu16Data2send;
/** Variable to save the data for send*/
U08 LCD_gu8Data;
/** Variable to indicated the LCD status*/
U08 LCD_gu8Status;
/**Variable to indicated the Data position*/
U08 LCD_gu8Position;
/**Array with the initialization values*/
U08 gu8aInitValues[6]= {
                         0x33,  /*8-Bit interface, BF checked before this command*/
                         0x32,  /*Set interface to 4 bits. bit#3 --> 0=4bit, 1=8bits*/
                         0x28,  /*Sets DD RAM address.*/
                         0x0D,  /*Display control:0x08|D=1(display on)|C=1(cursor display)|B=1(Blink display)*/
                         0x01,  /*CLEAR DISPLAY*/
                         0x06   /*Return Home*/
                        }; 
/*************************************************************************************************/
/*********************                  Static Constants                    **********************/
/*************************************************************************************************/
/** Pointer to function array used to move the LCD state machine */
void (*const paWriteTask[])(void) =
{
        LCD_vFnIDLE,
        LCD_vFnWriteMSBData,
        LCD_vFnWriteLSBData,
        LCD_vFnFinishSendData,
        LCD_vFnWriteMoreData,
};

/*************************************************************************************************/
/*********************                      Functions                       **********************/
/*************************************************************************************************/

void LCD_vFnInit(void)
{
    /*Port initialization */  
	CLOCK_PORTS2LCD; //Enable Clock to port D
    LCD_PIN_RS_INIT; //Set pin D0 as RS
    LCD_PIN_E_INIT;  //Set pin D1 as E
    LCD_SET_PIN_DATA_AS_OUTPUT; //Set pin D2,D3,D4,D5 as data port 
    /*Send data to init*/
    LCD_gpt08Mensage = gu8aInitValues;
    LCD_gu16SizeData = wfnStrLen((U08*)&gu8aInitValues);
    LCD_gu8RS = LCD_SEND_COMMAND;    
    LCD_gu16Data2send = 0;
    LCD_gu8Status = (eLCD_BUSY);
    TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,TIME_INIT); //Reload timer for LCD 
    LCD_vFnWriteMoreData(); 
}

void LCD_vfnWriteMessage(U08* bpMessage, U08 Size)
{
	/*Send data to init*/
	LCD_gpt08Mensage = bpMessage;
	LCD_gu16SizeData = Size;
	LCD_gu8RS = LCD_SEND_DATA;    
	LCD_gu16Data2send = 0;
	LCD_gu8Status = (eLCD_BUSY);
	TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,TIME_INIT); //Reload timer for LCD 
	LCD_vFnWriteMoreData(); 
}

void LCD_vfnGotoXY(U08 x, U08 y)
{
	U08 address;

	switch(y) 
	{
		case 1 : address=0x80;break;
		case 2 : address=0xc0;break;
		case 3 : address=0x94;break;
		case 4 : address=0xd4;break;
	}
	address += (x-1);
	
	LCD_gpt08Mensage = (U08*)&address;
	LCD_gu16SizeData = 1;
	LCD_gu8RS = LCD_SEND_COMMAND;    
	LCD_gu16Data2send = 0;
	LCD_gu8Status = (eLCD_BUSY);
	TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,TIME_INIT); //Reload timer for LCD 
	LCD_vFnWriteMoreData(); 
}

void LCD_vfnClrScr(void)
{
	
	LCD_gpt08Mensage = (U08*)LCD_CLEAR;
	LCD_gu16SizeData = 1;
	LCD_gu8RS = LCD_SEND_COMMAND;    
	LCD_gu16Data2send = 0;
	LCD_gu8Status = (eLCD_BUSY);
	TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,TIME_INIT); //Reload timer for LCD 
	LCD_vFnWriteMoreData(); 
}

void LCD_vFnTask(void)
{
    paWriteTask[LCD_StateMachine.bActualState]();
}

static void LCD_vFnIDLE(void)
{
    /*Do nothing*/
    LCD_gu8Status = eLCD_OK;
}

static void LCD_vFnWriteMSBData(void)
{
    U08 Aux;  

	if(TBG_CHECK_TIMER_CHN_FLAG(LCD_TIMER_CH))//If BF is clear
	{
		LCD_PIN_RS(LCD_gu8RS); 
		LCD_PIN_E(0);
		
		Aux = (LCD_gu8Data & 0xF0); // Get The value of the upper bits
		Aux = bfnShiftRight(Aux,4); 
		/*Write data on port*/
		LCD_WRITE_DATA_PORT(Aux); 
		
		LCD_PIN_E(1);
		LCD_StateMachine.bActualState = eLCD_WRITE_LSB_DATA;
		
		TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,LCD_TIMER);
	}
	else
	{
		/*Do nothing*/
	}

}

static void LCD_vFnWriteLSBData(void)
{
	 U08 Aux; 
  
    if(TBG_CHECK_TIMER_CHN_FLAG(LCD_TIMER_CH))
    {
		LCD_PIN_E(0);
		
		Aux = (LCD_gu8Data & 0x0F); // Get The value of the upper bits 
		/*Write data on port*/
		LCD_WRITE_DATA_PORT(Aux); 
		  
        LCD_PIN_E(1);
        LCD_StateMachine.bActualState = eLCD_FINISH_SEND_DATA;
        TBG_RELOAD_TIMER_CHN(LCD_TIMER_CH,LCD_TIMER);
    }
    else
    {
        /*Do nothing*/
    }
}

static void LCD_vFnFinishSendData(void)
{
    if(TBG_CHECK_TIMER_CHN_FLAG(LCD_TIMER_CH))
    {
        LCD_PIN_E(0);
        LCD_StateMachine.bActualState = LCD_StateMachine.bNextState;        
    }
    else
    {
        /*Do nothing*/
    }
}

static void LCD_vFnWriteMoreData(void)
{   /*Review if have more data to send*/
    if( LCD_gu16SizeData-- > 0)
    {
        LCD_gu8Data = *LCD_gpt08Mensage;
        LCD_gpt08Mensage ++;
        LCD_StateMachine.bActualState = eLCD_WRITE_MSB_DATA;
        LCD_gu8Status = (eLCD_BUSY);
        LCD_StateMachine.bNextState = eLCD_MORE_DATA;
    }
    else 
    {
        LCD_StateMachine.bActualState = eLCD_IDLE;
        LCD_gu8Status = eLCD_OK;
    }
}
