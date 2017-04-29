/*
 * TFT_SPI.h
 *
 *  Created on: Mar 19, 2014
 *      Author: MyL
 */

#ifndef TFT_SPI_H_
#define TFT_SPI_H_

/*
 *  PTD0 -> CS
 *  PTD1 -> SCK
 *  PTD2 -> MOSI
 *  PTD3 -> MISO
 *  PTD4 -> GPIO A0 o rs o DC
 *  PTD5 -> GPIO Rest 
 *  */
#include"string.h"
#include "derivative.h"

#define uchar 	unsigned char
#define ushort 	unsigned short


#define Reset_0 FGPIOD_PDOR &= (0<<3)
#define Reset_1 FGPIOD_PDOR |= (1<<3)
#define CS_0 FGPIOD_PCOR |= (1 << 0)
#define CS_1 FGPIOD_PSOR |= (1 << 0)
#define A0_0 FGPIOD_PCOR |= (1 << 4)
#define A0_1 FGPIOD_PSOR |= (1 << 4)

/*to initialise the SPI module*/
void spi0_init(void);
void spi_send_data(char spiMsg);  
void spi_send_command(char spiMsg);

void spi1_init(void);
/*Functions for the TFT*/
void Reset_TFT(void);
void tft_initial(void); 
void set_color_background(int color);
void delay(double time);
void PutPixel(int x,int y,uchar DH,uchar DL);
void LCD_SetArea(int x1, int y1, int x2, int y2);
void show_pic(void);
void set_pixel_color(int x, int y,int color);
void RamAdressSet(void);
void RedLine(void);
void BlueLine(void);
void Display_Desc(void);
void Output_Pixel(int x,int y);
void Output_Pixel_C(int x,int y, short color);
void Display_ASCII8X16_C(int x0,int y0,char *s,short color);
void Display_ASCII8X10_C(int x0,int y0,char *s,short color);
void Address_set(int x1,int y1,int x2,int y2);
void tft_DrawLine(int x1, int y1, int x2, int y2);
void tft_DrawRectangle(int x1, int y1, int x2, int y2);
void Draw_Circle(int x,int y,int r);
void graph(int x, int y,int h,int w);
void LCD_Fill(int xsta,int ysta,int xend,int yend,int color);
void DrawPoint(int x, int y,int color);
void Refreshline(int x,int y, int color);
void linegraph(int x,int y,int color);
void draw_hrt_Low(void);
void draw_hrt_High(void);


// Color definitions
#define BLACK   (0x0000)
#define RED 	(0x001F)
#define BLUE 	(0xF800)
#define GREEN 	(0x0400)
#define YELLOW 	(0x07FF)
#define MAGENTA (0xF81F)
#define CYAN 	(0xFFE0) 
#define WHITE 	(0xFFFF)
#define SILVER  (0xC618)
#define GRAY    (0x8410)
#define MAROON  (0x8000)
#define OLIVE   (0x8400)
#define LIME    (0x07E0)
#define TEAL    (0x0410)
#define NAVY    (0x0010)
#define PURPLE  (0x8010)




// mickey mouse



#endif /* TFT_SPI_H_ */
