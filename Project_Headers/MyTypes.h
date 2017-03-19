/*
 * MyTypes.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Morita
 */

#ifndef MYTYPES_H_
#define MYTYPES_H_

/*************************************************************************************************/
/*********************                      Includes                        **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                      Defines                         **********************/
/*************************************************************************************************/
#ifndef TRUE
    #define TRUE                        (1)
#endif

#ifndef FALSE
    #define FALSE                       (0)
#endif

#ifndef HIGH
    #define HIGH                        (1)
#endif

#ifndef LOW
    #define LOW                         (0)
#endif

#ifndef NULL
  #define NULL          (void*)0
#endif

#ifndef CLOCK48M
	#define CLOCK48M		48000000
#endif

//
//typedef enum
//{
//	eNVIC_DMA0 = 0,
//	eNVIC_DMA1,
//	eNVIC_DMA2,
//	eNVIC_DMA3,
//	eNVIC_RESERVED1,
//	eNVIC_FTFA, //5
//	eNVIC_PMC,
//	eNVIC_LLWU,
//	eNVIC_I2C0,
//	eNVIC_I2C1,
//	eNVIC_SPI0, //10
//	eNVIC_SPI1,
//	eNVIC_UART0,
//	eNVIC_UART1,
//	eNVIC_UART2,
//	eNVIC_ADC0, //15
//	eNVIC_CMP0,
//	eNVIC_TPM0,
//	eNVIC_TPM1,
//	eNVIC_TPM2,
//	eNVIC_RTC_ALARM, //20
//	eNVIC_RTC_SEC,
//	eNVIC_PIT,
//	eNVIC_RESERVED2,
//	eNVIC_USB_OTG,
//	eNVIC_DAC0,  //25
//	eNVIC_TSI0,
//	eNVIC_MCG,
//	eNVIC_LPTMR0,
//	eNVIC_RESERVED3,
//	eNVIC_PORTA, //30
//	eNVIC_PORTD
//}_eNVIC_INT;
/*************************************************************************************************/
/*********************                      Typedefs                        **********************/
/*************************************************************************************************/


typedef unsigned char               u08;  
typedef unsigned char               BOOLEAN; 
typedef unsigned char               BYTE;
typedef unsigned short              u16;
typedef unsigned long               u32;
typedef signed char                 s08;
typedef signed short                s16;     
typedef signed long                 s32;
typedef int 						i32;

#endif /* MYTYPES_H_ */
