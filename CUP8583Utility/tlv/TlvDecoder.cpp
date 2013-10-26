//系统头文件

#include "stdafx.h"

#include <stdlib.h>

//自定义头文件
#include "TlvDecoder.h"
#include "Tag.h"
#include "ErrorNo.h"
#include "TlvDecoderErrorNo.h"

int validateConstructedTlvData(byteArray constructedTlvData, uint16 constructedTlvDataLen)
{
	if(constructedTlvData == NULL ||  \
		constructedTlvDataLen < MIN_CONSTRUCTEDTLVDATA_LEN)
	{
		return ERR_INVALID_TLVDATA;
	}

	return 0;
}



static int parseLength(int32 *lengthLen, byteArray * data, int32 *constructedTlvDataLen) {
	int lengthByte = **data;
	int lenByteCounts;

	if(lengthLen == NULL ||  data == NULL ||\
		constructedTlvDataLen == NULL)
	{
		return ERR_INVALID_TLVDATA;
	}
	
	if ((lengthByte & 0x80) == 0x80) 
	{
		lenByteCounts = (lengthByte & 0x7F);
		*constructedTlvDataLen -= lenByteCounts;

		if(*constructedTlvDataLen < 0)
		{
			return ERR_PARSE_LENGTH;
		}
		
		while (lenByteCounts > 0) 
		{
			*lengthLen += **data & 0xFF;
			
			if (lenByteCounts > 1) 
			{
				*lengthLen *= 256;
			}
			
			lenByteCounts--;
			*data += 1;
		}

	}
	else 
	{
		*lengthLen = lengthByte;
	}

	if(*constructedTlvDataLen <= 0)
	{
		return ERR_PARSE_LENGTH;
	}
	
	*data += 1;
	*constructedTlvDataLen -= 1;
	
	return 0;
}



int32 decodeConstructedTlvData(void *saveDataCallback,byteArray constructedData,
							int32 constructedDataLen, boolean parseConstructedTags, 
							boolean parseSubConstructedTlvData, void *objRepo)
{
	byte tag[TAG_LENGTH];
	byte tagLen;
	int32 length;
	saveTlvElement saveTlvObjCallBack = NULL;  //保存TLV元素接口如果是constructed ber-tl则用此接口保存
	int32 iret = 0;

	if(constructedData == NULL || constructedDataLen < 2)
	{
		return ERR_INVALID_PARAMETER;
	}

	if(saveDataCallback != NULL)
	{
		saveTlvObjCallBack = (saveTlvElement)saveDataCallback;
	}

	while(constructedDataLen > 0)
	{
		if (parseTag(tag, &tagLen, &constructedData, &constructedDataLen) != 0)
		{
			return ERR_PARSE_TAG;
		}

		if (parseLength(&length, &constructedData, &constructedDataLen) != 0)
		{ 
			return ERR_PARSE_LENGTH;
		}		

		if(true == parseConstructedTags)
		{
			if(saveTlvObjCallBack(tag, tagLen, length, NULL,objRepo) != 0)
			{
				return ERR_SAVEDATA_FAIL;
			}

			continue;
		}
		else
		{
			constructedDataLen -= length;

			if(constructedDataLen < 0)
			{
				return ERR_PARSE_VALUE;
			}
							
			if(saveTlvObjCallBack(tag, tagLen, length, constructedData, objRepo) != 0)
			{
				return ERR_SAVEDATA_FAIL;
			}

			if((parseSubConstructedTlvData == true) && (isConstructedTag (tag) == true))  //如果要求解析子constructed tlv obj 数据而且又是一个constructed tlv obj 则解析
			{
				iret = decodeConstructedTlvData(saveDataCallback, constructedData, length, 
												parseConstructedTags, parseSubConstructedTlvData,objRepo);

				if(iret != 0)
				{
					return iret;
				}
			}

			constructedData += length;
		}
	}

	if(constructedDataLen < 0)
	{
		return ERR_PARSE_VALUE;
	}
	
	return 0;
}


int32 decodeFirstLevelConstructedTlvObj(void *saveDataCallback,byteArray constructedData,
										int32 constructedDataLen, void *objRepo)
{
	return decodeConstructedTlvData(saveDataCallback, constructedData, constructedDataLen,
							false, false, objRepo);
}


int32 decodeAllConstructedTlvObj(void *saveDataCallback,byteArray constructedData,
									int32 constructedDataLen, void *objRepo)
{
	return decodeConstructedTlvData(saveDataCallback, constructedData, constructedDataLen,
							false, true, objRepo);
}


int32 decodeFirstLevelConstructedTlObj(void *saveDataCallback,byteArray constructedData,
										int32 constructedDataLen, void *objRepo)
{
	return decodeConstructedTlvData(saveDataCallback, constructedData, constructedDataLen,
							true, false, objRepo);
}


int32 decodeAllConstructedTlObj(void *saveDataCallback,byteArray constructedData,
									int32 constructedDataLen, void *objRepo)
{
	return decodeConstructedTlvData(saveDataCallback, constructedData, constructedDataLen,
							true, true, objRepo);
}


