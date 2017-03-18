/**
 * file:   StandarLibrary.c  
 * author: Luis Ivan Escamilla Estrada 2376677
 * date:   20/01/2015
 * brief:  Archivo con las funciones de la practica 1
 *
 */

/*************************************************************************************************/
/*********************                    Own Includes                      **********************/
/*************************************************************************************************/

#include "StandarLibrary.h"

/*************************************************************************************************/
/*********************                   Local Defines                      **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                       Enums                          **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************             Local Functions prototypes               **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                     Variables                        **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                   Main Function                      **********************/
/*************************************************************************************************/

void vfnMemCpy (unsigned char* bpSource, unsigned char* bpDest, unsigned short wSize)
{
	while(wSize--)
	{
		*bpDest++ =  *bpSource++;
	}
}

void vfnMemSet(unsigned char* bpDest, unsigned char bByteToFill, unsigned short wSize)
{
	while(wSize--)
	{
		*bpDest++ = bByteToFill;
	}
}

unsigned char bfnFindMax(unsigned char* bpDest, unsigned short wSize)
{
	U08 btemp = *bpDest;

	while(wSize--)
	{
		if(*bpDest > btemp )
		{
			btemp = *bpDest++; 
		}
		else
		{
			bpDest++;
		}
	}
	
	return btemp;
}

unsigned char bfnFindMin(unsigned char* bpDest, unsigned short wSize)
{
	U08 temp = (U08)*bpDest;

	while(wSize--)
	{
		if(*bpDest < temp )
		{
			temp = *bpDest++; 
		}
		else
		{
			bpDest++;
		}
	}
	
	return (U08) temp;
}

unsigned char bfnStrCmp(unsigned char* bpSource, unsigned char* bpDest, unsigned short wSize)
{
	while(wSize--)
	{
		if(*bpSource ^ *bpDest)
		{
			return (U08) 0;
		}
		else 
		{
			bpSource++;
			bpDest++;
		}
	}
	
	return (U08) 1;
}

unsigned char* bpfnByteAddress(unsigned char* bpString, unsigned char bCharToFind, unsigned short wSize)
{
	while(wSize--)
	{
		if(!(*bpString ^ bCharToFind))
		{
			return (U08*)bpString;
		}
		else 
		{
			bpString++;
		}
	}
		
	return NULL;
	
}

unsigned short wfnStrLen (unsigned char* bpString)
{
	U16 usCnt = 0;
	
	while(*bpString != '\0')
	{
		usCnt++;
		bpString++;
	}
	
	return (U16) usCnt;
}

unsigned short wfnSum(unsigned char* bpSrc, unsigned char bSize)
{
	U16 usTotal = 0;
	
	while(bSize--)
	{
		usTotal += *bpSrc++;
	}
	
	return (U16) usTotal;
}

unsigned char bfnAvg(unsigned char *bpSrc, unsigned char bN)
{
	U16 usSumaTotal= wfnSum((U08*)bpSrc,(U08)bN);
	U16 usTotal = 0;
	
	/*Division
	 *  Total = UsSumaTotal/bN;
	 *   ->  Total
	 *     -----------
	 *  bN)UsSumaTotal
	 *  
	 * */
	
	while(usSumaTotal >= bN)
	{
		usSumaTotal -= bN;
		usTotal++;
	}
	
	return (U08)(usTotal);
}

unsigned char bfnShiftLeft (unsigned char bData, unsigned char bShift)
{
	if(bShift > 8)
	{
		return bData;
	}
	else
	{
		while(bShift--)
		{
			bData = (bData * 2);
		}
		return bData;
	}
}

unsigned char bfnShiftRight (unsigned char bData, unsigned char bShift)
{
	if(bShift > 8)
	{
		return bData;
	}
	else
	{
		while(bShift--)
		{
			bData = (bData / 2);
		}
		return bData;
	}
}

unsigned char bfnToUpperCase (unsigned char bChar)
{
	if(bChar >= 'a' && bChar <= 'z')
	{
		return (bChar - (U08)0x20);
	}
	else
	{
		return bChar;
	}
}

unsigned char bfnToLowerCase (unsigned char bChar)
{
	if(bChar >= 'A' && bChar <= 'Z')
	{
		return (bChar + (U08)0x20);
	}
	else
	{
		return bChar;
	}
}

unsigned char bfnIsPrint (unsigned char bChar)
{
	if(bChar >= (U08)0x20 && bChar <= (U08)0x7E)
	{
		return (U08)0x01;
	}
	else
	{
		return (U08)0x00;
	}
}

unsigned char bfnIsHex (unsigned char bChar)
{
	if((bChar >= (U08)0x30 && bChar <= (U08)0x39) || (bChar >= (U08)0x41 && bChar <= (U08)0x46) || (bChar >= (U08)0x61 && bChar <= (U08)0x66))
	{
		return (U08)0x01;
	}
	else
	{
		return (U08)0x00;
	}
}

unsigned short wfnRand(unsigned short wSeed)
{
	U16 lfsr = wSeed;
	U08 bit;
	
	bit  =  ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	lfsr =  (lfsr >> 1) | (bit << 15);
    
	return lfsr;
}

unsigned char bfnLRC(unsigned char* bpSrc, unsigned short wSize)
{
	U08 bLRC = 0;
	
	while(wSize--)
	{
		bLRC = ((bLRC + *bpSrc) & 0xFF);
		bpSrc++;
	}
	
	return (((bLRC ^ 0xFF) + 1) & 0xFF);
}

unsigned short wfnOccurrence(unsigned char bSymbol, unsigned char* bpSrc, unsigned short wSize)
{
	U16 usCounter = 0;
	
	while(wSize--)
	{
		if(!(*bpSrc ^ bSymbol))
		{
			usCounter++;
			bpSrc++;
		}
		else 
		{
			bpSrc++;
		}
	
	}
	
	return (U16)usCounter;
}

void vfnSort (unsigned char* bpString, unsigned short wStringSize)
{
	U08* Origin = bpString;
	U08 bAct;
	U08 bSig;
	U08 i = wStringSize - 1;
	U08 j = wStringSize - 1;

	while(i--)
	{
		while(j--)
		{
			bAct = *bpString;
			bpString++;
			bSig = *bpString;
			
			if(bAct > bSig)
			{
				*(bpString - 1) = bSig;
				*bpString = bAct;
			}
		}
		
		j = wStringSize -1;		
		bpString = Origin;
	}
	
}

unsigned short wfnSprintf (char* string, const char* fmt,...)
{
	//U08 cnt = 0;
	while(*string != '\0')
	{
		/*if(*string == '%c')
		{
			cnt++;
		}
		else if(*string == '%d')
		{
			
			cnt++;
		}
		else if(*string == '%s')
		{
			
			cnt++;
		}
		else if(*string == '%x')
		{
			
			cnt++;
		}
		else if(*string == '%b')
		{
			
			cnt++;
		}
		else
		{
		
			cnt++;
		}*/
	}
	
	return 0;
}
