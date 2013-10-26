/**********************************************************************
*@filename: TlvDecoder.h
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/


#ifndef _TLV_DECODER_H_
#define _TLV_DECODER_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "UserType.h"

#define MIN_CONSTRUCTEDTLVDATA_LEN			2

typedef int32 (*saveTlvElement)(byte *tag, byte tagLen,int32 len, byteArray value, void *tlvObjRepo);

int32 decodeConstructedTlvData(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, boolean parseConstructedTags, 
							boolean parseSubConstructedTlvData, void *objRepo);

int32 decodeFirstLevelConstructedTlvObj(void *saveDataCallback,byteArray constructedData,
										int32 constructedDataLen, void *objRepo);

int32 decodeAllConstructedTlvObj(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, void *objRepo);

int32 decodeFirstLevelConstructedTlObj(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, void *objRepo);

int32 decodeAllConstructedTlObj(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, void *objRepo);

#ifdef __cplusplus
}
#endif

#endif

