#include "stdafx.h"

#include <stdio.h>

#include "Utils.h"
#include "ErrorNo.h"


int32 toUperCase(cstring str)
{
	if(str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	do{
		*str = UPERCASE (*str);
	}while(*(++str));
	
	return 0;
}


int32 toLowerCase(cstring str)
{
	if(str == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	do{
		*str = LOWECASE (*str);
	}while(*(++str));
	
	return 0;
}



inline int32 getCharIndex(cstring str, tchar ch)
{
	tchar temp[2];

	temp[0] = ch;
	temp[1] = 0x00;

	return (int32)(strstr(str, temp) - str);
}



int32 hexStringToByteArray(byteArray desBytearray, int32 *byteArrayLen, cstring hexString)
{
	tchar hexNumbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int32 i = 0;

	if(desBytearray == NULL || byteArrayLen == NULL || \
		hexString == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	if(0 == VALIDATEHEXSTRING(hexString))
	{
		return ERR_INVALID_PARAMETER;
	}

	if(toUperCase (hexString) != 0)
	{
		return ERR_CONVERT_TYPE;
	}
	
	do{
		desBytearray[i/2] = (getCharIndex(hexNumbers, hexString[i]) << 4) | getCharIndex(hexNumbers, hexString[i+1]);
		i+=2;
	}while(hexString[i]);

	*byteArrayLen = (int)(strlen(hexString)/2);
	return 0;
}



int32 byteArrayToHexString(cstring desHexString, byteArray srcByteArray, int32 srcByteArrayLen)
{
	tchar hexNumbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int32 i = 0;
	
	if(desHexString == NULL || srcByteArray == NULL || \
		srcByteArrayLen<= 0)
	{
		return ERR_INVALID_PARAMETER;
	}

	do{
		desHexString[i*2] = hexNumbers[(srcByteArray[i]&0xF0) >> 4];
		desHexString[i*2 + 1] = hexNumbers[(srcByteArray[i]&0x0F)];
	}while((++i) < srcByteArrayLen);

	desHexString[srcByteArrayLen*2] = 0x00;
	return 0;
}


int64 bcdNumericToLong(byteArray bcdNumeric, byte len)
{
	tchar buf[512];
	byte i = 0;

	memset(buf, 0x00, sizeof(buf));

	for(i = 0; i<len; i++)
	{
		sprintf(buf + strlen(buf), "%02x", bcdNumeric[i]);
	}

	return atol(buf);
}


int64 byteArrayToLong(byteArray data, byte len)
{
	int64 result = 0;
	byte i = 0;
	
	for(i = 0; i<len; i++)
	{
		result = (result << 8) | data[i];
	}

	return result;
}


int32 byteArrayToInt(byteArray data, byte len)
{
	int32 result = 0;
	byte i = 0;
	
	for(i = 0; i<len; i++)
	{
		result = (result << 8) | data[i];
	}

	return result;
}

