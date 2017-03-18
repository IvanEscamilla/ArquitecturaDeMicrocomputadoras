/*
 * StandarLibrary.h
 *
 *  Created on: Jan 20, 2015
 *      Author: Luis Ivan Escamilla Estrada
 *      # Reg: 2376677
 */

#ifndef STANDARLIBRARY_H_
#define STANDARLIBRARY_H_

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

#ifndef NULL
  #define NULL          (void*)0
#endif

typedef enum
{
	eNVIC_DMA0 = 0,
	eNVIC_DMA1,
	eNVIC_DMA2,
	eNVIC_DMA3,
	eNVIC_RESERVED1,
	eNVIC_FTFA, //5
	eNVIC_PMC,
	eNVIC_LLWU,
	eNVIC_I2C0,
	eNVIC_I2C1,
	eNVIC_SPI0, //10
	eNVIC_SPI1,
	eNVIC_UART0,
	eNVIC_UART1,
	eNVIC_UART2,
	eNVIC_ADC0, //15
	eNVIC_CMP0,
	eNVIC_TPM0,
	eNVIC_TPM1,
	eNVIC_TPM2,
	eNVIC_RTC_ALARM, //20
	eNVIC_RTC_SEC,
	eNVIC_PIT,
	eNVIC_RESERVED2,
	eNVIC_USB_OTG,
	eNVIC_DAC0,  //25
	eNVIC_TSI0,
	eNVIC_MCG,
	eNVIC_LPTMR0,
	eNVIC_RESERVED3,
	eNVIC_PORTA, //30
	eNVIC_PORTD
}_eNVIC_INT;
/*************************************************************************************************/
/*********************                      Typedefs                        **********************/
/*************************************************************************************************/

typedef unsigned char               U08;  
typedef unsigned char               BOOLEAN;  
typedef unsigned short              U16;
typedef unsigned long               U32;
typedef signed char                 S08;
typedef signed short                S16;     
typedef signed long                 S32;


typedef struct
{
    U08 bActualState;
    U08 bPrevState;
    U08 bNextState;
    U08 bNextNextState;
    U08 bErrorState;
}_sStateMachine;

/*************************************************************************************************/
/*********************                  Function Prototypes                 **********************/
/*************************************************************************************************/

/**
 * Brief: Copia las cantidad de datos indicados por wSize del bloque apuntado por bpSource al bloque apuntado por bpDest.
 * Params: 	
 * 			unsigned char* bpSource  -  Apuntador a la dirrecion de memoria de la fuente 
 * 			unsigned char* bpDest    -  Apuntador a la direccion de memoria del destino 
 * 			unsigned short wSize	 -  Tamaño
 * return: void (nothing to return) 
 */
void vfnMemCpy (unsigned char* bpSource, unsigned char* bpDest, unsigned short wSize);

/**
 * Brief: Rellena el bloque apuntado por bpDest con el dato indicado por bByteToFill.
 * Params: 	
 * 			unsigned char* bpDest     -  Apuntador a la direccion de memoria del destino
 * 			unsigned char bByteToFill -  Dato que sera copiado al destino (parametro)
 * 			unsigned short wSize	  -  Tamaño
 * return: void (nothing to return) 
 */
void vfnMemSet(unsigned char* bpDest, unsigned char bByteToFill, unsigned short wSize);

/**
 * Brief: Devuelve el número sin digno mayor encontrado en el bloque de memoria apuntado por bpDest.
 * Params: 	
 * 			unsigned char* bpDest     -  Apuntador a la direccion de memoria del destino
 * 			unsigned short wSize	  -  Tamaño
 * 			
 * return: unsigned char 
 */
unsigned char bfnFindMax(unsigned char* bpDest, unsigned short wSize);

/**
 * Brief: Devuelve el número sin signo menor encontrado en el bloque de memoria apuntado por bpDest.
 * Params: 	
 * 			unsigned char* bpDest     -  Apuntador a la direccion de memoria del destino
 * 			unsigned short wSize	  -  Tamaño
 * 			
 * return: unsigned char 
 */
unsigned char bfnFindMin(unsigned char* bpDest, unsigned short wSize);

/**
 * Brief: Compara las cadenas apuntadas por bpSource y bpDest, devolviendo un 1 si las cadenas 
 * 		  son iguales o un 0 si son distintas.
 * Params: 	
 * 			unsigned char* bpSource   -  Apuntador a la direccion de memoria de la fuente
 * 			unsigned char* bpDest     -  Apuntador a la direccion de memoria del destino
 * 			unsigned short wSize	  -  Tamaño
 * 			
 * return: unsigned char 		:	1 iguales
 * 									0 Diferentes	
 */
unsigned char bfnStrCmp(unsigned char* bpSource, unsigned char* bpDest, unsigned short wSize);

/**
 * Brief: Entrega la dirección donde se encuentra el valor bCharToFind en la cadena bpString. En caso de no
 * 		  encontrar datos, regresa un apuntador a NULL (Apuntador apuntando a la direccion 0, "(void*)0").
 * Params: 	
 * 			unsigned char* bpString    -  Apuntador a la direccion de memoria de la cadena
 * 			unsigned char  bCharToFind -  Caracter que se esta buscando
 * 			unsigned short wSize	   -  Tamaño
 * 			
 * return: unsigned char* 		:	NULL (void*)0 si no encuentra
 * 									(U08*)dir del char igual	
 */
unsigned char* bpfnByteAddress(unsigned char* bpString, unsigned char bCharToFind, unsigned short wSize);

/**
 * Brief: Devuelve el tamaño de la cadena terminada en 0 apuntada por bpString.
 * Params: 	
 * 			unsigned char* bpString   -  Apuntador a la direccion de memoria de la cadena
 * 			
 * return: unsigned short 		:	Tamaño de la cadena	
 */
unsigned short wfnStrLen (unsigned char* bpString);

/**
 * Brief: Devuelve el resultado en 16 bits de sumar todos los elementos apuntados por bpSrc.
 *        El total de elementos a sumar es bSize.
 * Params: 	
 * 			unsigned char* bpSrc   -  Apuntador a la direccion de memoria de la Fuente
 * 			unsigned char bSize    -  Numero total de numeros a sumar
 * 			
 * return: unsigned short 		:	Suma total	
 */
unsigned short wfnSum(unsigned char* bpSrc, unsigned char bSize);

/////////////////TODO: optimizar la division ////////////////
/**
 * Brief: Devuelve el promedio de los bN datos apuntados por bpSrc.
 *   
 * Params: 	
 * 			unsigned char* bpSrc   -  Apuntador a la direccion de memoria de la Fuente
 * 			unsigned char bN       -  Numero de datos a promediar
 * 			
 * return: unsigned char 		:	promedio	
 */
unsigned char bfnAvg(unsigned char *bpSrc, unsigned char bN);

/**
 * Brief: Devuelve el dato recibido en bData recorrido bShift espacios a la izquierda 
 * 		  agregando 0. NOTA: bShift no puede ser mayor a 8.
 *   
 * Params: 	
 * 			unsigned char bData   -  Dato que sera recorrido
 * 			unsigned char bShift  -  Numero de veces que se recorrera
 * 			
 * return: unsigned char 		:		
 */
unsigned char bfnShiftLeft (unsigned char bData, unsigned char bShift);

/**
 * Brief: Devuelve el dato recibido en bData recorrido bShift espacios a la derecha 
 * 		  agregando 0. NOTA: bShift no puede ser mayor a 8.
 *   
 * Params: 	
 * 			unsigned char bData   -  Dato que sera recorrido
 * 			unsigned char bShift  -  Numero de veces que se recorrera
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnShiftRight (unsigned char bData, unsigned char bShift);

/**
 * Brief: Devuelve el dato recibido en bChar convertido a mayúsculas en caso de ser una
 * 		  letra entre ‘a’ y ‘z’. Si el dato recibido, no es una letra, entonces regresa 
 * 		  el mismo valor sin alterarlo.
 *   
 * Params: 	
 * 			unsigned char bChar   -  Dato entre a y z esperado
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnToUpperCase (unsigned char bChar);

/**
 * Brief: Devuelve el dato recibido en bChar convertido a minusculas en caso de ser una
 * 		  letra entre ‘A’ y ‘Z’. Si el dato recibido, no es una letra, entonces regresa
 * 		  el mismo valor sin alterarlo.
 *   
 * Params: 	
 * 			unsigned char bChar   -  Dato entre a y z esperado
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnToLowerCase (unsigned char bChar);

/**
 * Brief: Devuelve un 1 si el dato recibido en bChar es un carácter imprimible de la tabla ASCII.
 *   
 * Params: 	
 * 			unsigned char bChar   -  Dato
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnIsPrint (unsigned char bChar);

/**
 * Brief: Devuelve un 1 si el dato recibido en bChar corresponde al valor de la tabla ASCII
 * 		  de un numero entre ‘0’ y ‘9’ o una letra entre ‘A’ y ‘F’.
 *   
 * Params: 	
 * 			unsigned char bChar   -  Dato
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnIsHex (unsigned char bChar);

/****TODO: Terminalo**************/
/**
 * Brief: Devuelve un numero de 16 bits por medio de un generador de números pseudo aleatorio basado
 * 		  en la semilla recibida en wSeed. Utilice el algoritmo de Fibonacci en registros de corrimiento
 * 		  con retroalimentación lineal (LFSR) que muestra la figura (http://en.wikipedia.org/wiki/Linear
 * 		  _feedback_shift_register).
 * 		  x^{16} + x^{14} + x^{13} + x^{11} + 1
 *   
 * Params: 	
 * 			unsigned short wSeed   -  
 * 			
 * return: unsigned char 		:	
 */
unsigned short wfnRand(unsigned short wSeed);

/**
 * Brief: Devuelve el número de 8 bits que resulta de realizar un xor entre todos los datos contenidos en
 * 		  el espacio de memoria apuntado por bpSrc con tamaño especificado por wSize. 
 * 		  (http://en.wikipedia.org/wiki/Longitudinal_redundancy_check)
 *   
 * Params: 	
 * 			unsigned char* bpSrc  -  Apuntador a la direccion de memoria de la Fuente
 * 			unsigned short wSize  -  Tamaño
 * 			
 * return: unsigned char 		:	
 */
unsigned char bfnLRC(unsigned char* bpSrc, unsigned short wSize);

/**
 * Brief: Devuelve el número de 16 bits que representa la cantidad de veces que se repite el elemento bSymbol
 * 		  en el bloque indicado por bpSrc de tamaño wSize (http://en.wikipedia.org/wiki/Run-length_encoding)
 *   
 * Params: 	
 * 			unsigned char bSymbol  -  simbolo a buscar
 * 			unsigned char* bpSrc   -  Apuntador a la direccion de memoria de la Fuente
 * 			unsigned short wSiz    -  Tamaño
 * 			
 * return: unsigned short 		:	numeros de ocurrencias
 */
unsigned short wfnOccurrence(unsigned char bSymbol, unsigned char* bpSrc, unsigned short wSize);

/**
 * Brief: Ordena de menor a mayor, en el mismo sitio, los datos contenidos en el buffer apuntado por bpString.
 *   
 * Params: 	 
 * 			unsigned char* bpString       -  Apuntador a la direccion de memoria de la Fuente
 * 			unsigned short wStringSize    -  Tamaño de la cadena apuntada
 * 			
 * return: void 		
 */
void vfnSort (unsigned char* bpString, unsigned short wStringSize);

/**
 * Brief: Formatea en la cadena string los datos siguiendo el formato. Devuelve el tamaño de la cadena generada.
 *   
 * Params: 	 
 * 			char* string       -  Apuntador a la direccion de memoria de la Fuente
 * 			const char* fmt    -  Apuntador a las variables de formato
 * 			
 * return: unsigned short 	: tamaño de la cadena generada
 */
unsigned short wfnSprintf (char* string, const char* fmt,...);
/*************************************************************************************************/

#endif /* STANDARLIBRARY_H_ */
