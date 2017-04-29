/*
 * SPI.c
 *
 *  Created on: Mar 26, 2017
 *      Author: Luis Ivan Escamilla
 */

/** Create SPI Obj to specific pins
*
* Pin Options:
* 		ALT1	ALT2	ALT3	ALT4	ALT5	ALT6	ALT7
* PTE1:		  SPI1_MOSI				 SPI1_MISO
* PTE2:		  SPI1_SCK
* PTE3:		  SPI1_MISO				 SPI1_MOSI
* PTE4:		  SPI1_PCS0
* PTA14:	  SPI0_PCS0
* PTA15:	  SPI0_SCK
* PTA16:	  SPI0_MOSI				 SPI0_MISO
* PTA17:	  SPI0_MISO				 SPI0_MOSI
* PTB10:	  SPI1_PCS0
* PTB11:	  SPI1_SCK
* PTB16:	  SPI1_MOSI				 SPI1_MISO
* PTB17:	  SPI1_MISO				 SPI1_MOSI
* PTC4:		  SPI0_PCS0
* PTC5:		  SPI0_SCK
* PTC6:	  	  SPI0_MOSI				 SPI0_MISO
* PTC7:	  	  SPI0_MISO				 SPI0_MOSI
* PTD0:	 	  SPI0_PCS0
* PTD1:		  SPI0_SCK
* PTD2:		  SPI0_MOSI				 SPI0_MISO
* PTD3:		  SPI0_MISO				 SPI0_MOSI
* PTD4:		  SPI1_PCS0
* PTD5:		  SPI1_SCK
* PTD6:		  SPI1_MOSI				 SPI1_MISO
* PTD7:		  SPI1_MISO				 SPI1_MOSI
* 
*
*  mosi or miso can be specfied as NC if not used
*
*  @param MOSI 	SPI Master Out, Slave In pin
*  @param MISO 	SPI Master In, Slave Out pin
*  @param SCK 	SPI Clock pin
*  @param PCS0 	SPI Clock pin  
*  
*/


