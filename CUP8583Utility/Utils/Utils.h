#ifndef _UTILS_H_
#define _UTILS_H_

#include <string.h>

#include "UserType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BIT8		(0x80)
#define BIT7		(0x40)
#define BIT6		(0x20)
#define BIT5		(0x10)

#define BIT4		(0x08)
#define BIT3		(0x04)
#define BIT2		(0x02)
#define BIT1		(0x01)



#define VALIDATEHEXSTRING(s) ((strlen((s))%2)==0)?1:0 //判断是否是合法的由字节数组转换过来的十六进制字符串

#define UPERCASE(c) ((c)>='a' && (c)<='z')?((c)-0x20):(c)  //转大写

#define LOWECASE(c)	 ((c)>='a' && (c)<='z')?((c)+0x20):(c) //转小写

#define DECCHECK(c)	((c)>='0' && (c) <= '9')			//十进制字符?

#define HEXCHECK(c)	 (((c)>='0' && (c) <= '9') || ((c)>='a' && (c) <= 'f') || ((c)>='A' && (c) <= 'F'))  	//十六进制字符?

#define SETBITS(a, b)	((a) |= (b))	

#define CHECKBITSSET(a, b)  (((a)&(b)) == (b))

#define DIGIT_TO_CHAR(a)	((a)+'0') 

int32 toUperCase(cstring str);

int32 toLowerCase(cstring str);

inline int32 getCharIndex(cstring str, tchar ch);

int32 hexStringToByteArray(byteArray desBytearray, int32 *byteArrayLen, cstring hexString);

int32 byteArrayToHexString(cstring desHexString, byteArray srcByteArray, int32 srcByteArrayLen);

int64 bcdNumericToLong(byteArray bcdNumeric, byte len);

int64 byteArrayToLong(byteArray data, byte len);

int32 byteArrayToInt(byteArray data, byte len);


#ifdef __cplusplus
}
#endif

#endif

