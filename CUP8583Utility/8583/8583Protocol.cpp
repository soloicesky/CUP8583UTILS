#include "stdafx.h"

#include <math.h>

#include "Utils.h"
#include "element.h"
#include "8583Protocol.h"


int parseISO8583Msg(unsigned char *src8583Msg, int srcLen, SaveFieldData storeFieldData)
{

	//add your to do here
	int bitMapLen;
	int cursor;
	int i = 0;
	int j = 0;
	int temp = 0;
	int base;
	int fieldId = 0;
	FieldAttr fa;
	int contentLen;
	ELEMENT e;
	char valueBuff[1024];

	if (srcLen <=8 || src8583Msg == NULL)
	{
		return -1;
	}

	bitMapLen = 8;
	cursor = 8;

	if (*src8583Msg & 0x80)
	{
		bitMapLen += 8;
		cursor += 8;
	}

	e.value = valueBuff;

	for (i = 0; i< bitMapLen; i++)
	{
		temp = src8583Msg[i] & 0xFF;

		for (j = 0; j<8; j++)
		{
			base = (int)(pow(2.0, (int)(7-j))) & 0xFF;

			if (temp >= base)
			{

				if (i==0 && j==0)
				{
					continue;
				}

				memset(valueBuff, 0x00, sizeof(valueBuff));
				fieldId = i*8 + j +1;
				fa = fdAttrDict.fdAttrSet[fieldId - 1];
				e.fieldID = fieldId;

				switch (fa.lenAttr) {
				case Attr_fix:
					contentLen = fa.len;

					break;
				case Attr_var1:
					contentLen = ((src8583Msg[cursor] & 0xF0) >> 4) * 10
						+ (src8583Msg[cursor] & 0x0F);
					cursor++;

					if (contentLen > fa.len) {
						return (-1000 - fieldId);
					}

					break;
				case Attr_var2:
					contentLen = (src8583Msg[cursor] & 0x0F) * 100
						+ ((src8583Msg[cursor + 1] & 0xF0) >> 4) * 10
						+ (src8583Msg[cursor + 1] & 0x0F);
					cursor += 2;

					if (contentLen > fa.len) {
						return (-1000 - fieldId);
					}

					break;

				default:
					break;
				}

				switch (fa.valueAttr) {
				case Attr_a:

					memcpy(e.value, src8583Msg+cursor, contentLen);
					//	e.setValue(new String(resp8583Msg, cursor, contentLen));
					//	e.setLength(contentLen);
					e.len = contentLen;
					cursor += contentLen;
					break;
				case Attr_n:

					// break;
				case Attr_z:

					memcpy(e.value, src8583Msg+cursor, contentLen);
					byteArrayToHexString((char *)e.value, src8583Msg+cursor, (contentLen + 1) / 2);
					//	e.setValue(HexStringUtil.byteArrayToHexstring(resp8583Msg,
					//		cursor, cursor + ((contentLen + 1) / 2)));
					//	e.setLength(contentLen);

					e.len = contentLen;
					cursor += ((contentLen + 1) / 2);

					break;
				case Attr_b:
					byteArrayToHexString((char *)e.value, src8583Msg+cursor, contentLen);
					//	e.setValue(HexStringUtil.byteArrayToHexstring(resp8583Msg,
					//		cursor, cursor + contentLen));
					//	e.setLength(contentLen);
					e.len = contentLen;

					cursor += contentLen;

					break;
				default:
					break;
				}

				storeFieldData(e.fieldID, e.value, e.len);

			}

			temp = temp % base;
		}
	}

	return 0;
}
