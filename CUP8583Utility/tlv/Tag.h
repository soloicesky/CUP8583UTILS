/**********************************************************************
*@filename: Tag.h
*
*@author:soloicesky
*@date:2013.08.02
**********************************************************************/


#ifndef _TAG_H_
#define _TAG_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "UserType.h"


#define TAG_LENGTH			3


#define 	TAG_ADF_NAME						0x4F
#define 	TAG_APP_LABEL 						0x50
#define		TAG_TRACK2							0x57
#define		TAG_PAN							0x5A
#define		TAG_ENTRY_TEMPLATE				0x61
#define		TAG_FCI_TEMPLATE					0x6F
#define		TAG_TEMPERATE_70					0x70
#define		TAG_TEMPERATE_71					0x71
#define		TAG_TEMPERATE_72					0x72
#define		TAG_DIRECTORY_TEMPLATE			0x73
#define		TAG_TEMPLATE_77					0x77
#define		TAG_TEMPLATE_80					0x80
#define		TAG_AMOUNT_BINARY				0x81
#define 	TAG_AIP 							0x82
#define 	TAG_DF_NAME 						0x84
#define		TAG_SCRIPT							0x86
#define		TAG_APP_PRIOR						0x87
#define 	TAG_SFI							0x88
#define 	TAG_AUTH_CODE					0x89
#define		TAG_RESPONSE_CODE				0x8A
#define		TAG_CDOL1							0x8C
#define		TAG_CDOL2							0x8D
#define		TAG_CVM							0x8E
#define		TAG_CA_PUBLIC_KEY_INDEX			0x8F
#define		TAG_ISSUER_PK_CERTIFICATE		0x90
#define		TAG_ISSUER_AUTH_DATA				0x91
#define		TAG_ISSUER_PK_REMAINDER			0x92
#define		TAG_SDA_SSAD						0x93
#define 	TAG_AFL 							0x94
#define		TAG_TVR							0x95
#define		TAG_TDOL							0x97
#define		TAG_TDOL_HASH_VALUE				0x98
#define		TAG_TRANSACTION_DATE				0x9A
#define		TAG_TSI							0x9B
#define		TAG_TRANSACTION_TYPE				0x9C
#define		TAG_DDF_NAME						0x9D
#define		TAG_FCI_PROPRIETARY_TEMPLATE	0xA5
#define		TAG_CARDHOLDER_NAME				0x5F20
#define		TAG_APP_EXPIRATION_DATE			0x5F24
#define		TAG_APP_EFFECTIVE_DATE			0x5F25
#define		TAG_ISSUER_COUNTRY_CODE			0x5F28
#define		TAG_TRANS_CURRENCY_CODE			0x5F2A
#define		TAG_PREFERRED_LANGUAGE			0x5F2D
#define		TAG_SERVICE_CODE					0x5F30
#define 	TAG_PAN_SEQU_NUMBER				0x5F34
#define		TAG_TRANS_CURRENCY_EXP			0x5F36
#define     TAG_IBAN						0x5F53
#define 	TAG_ISSUER_COUTRY_CODE_ASII		0x5F56
#define		TAG_ACCOUNT_TYPE					0x5F57
#define		TAG_ACQUIRER_ID					0x9F01
#define 	TAG_AMOUNT						0x9F02
#define		TAG_AMOUNT_OTHER					0x9F03
#define		TAG_AMOUNT_OTHER_BINARY			0x9F04
#define 	TAG_APP_DISC_DATA				0x9F05
#define		TAG_TERMINAL_AID					0x9F06
#define		TAG_AUC							0x9F07
#define		TAG_ICC_APP_VERSION_NUMBER		0x9F08
#define		TAG_APP_VERSION_NUMBER			0x9F09
#define		TAG_CARDHOLDER_NAME_EXTENDED	0x9F0B
#define 	TAG_IAC_DEFAULT					0x9F0D
#define 	TAG_IAC_DENIAL					0x9F0E
#define 	TAG_IAC_ONLINE					0x9F0F
#define		TAG_ISSUER_APP_DATA				0x9F10
#define		TAG_ISSUER_CODE_INDEX			0x9F11
#define		TAG_PREFERRED_NAME				0x9F12
#define		TAG_LAST_ATC						0x9F13
#define		TAG_LOWER_OFFLINE_LIMIT			0x9F14
#define		TAG_MERCHANT_CATEGORY_CODE		0x9F15
#define		TAG_MERCHANT_ID					0x9F16
#define 	TAG_PIN_TRY_COUNTER 				0x9F17
#define		TAG_SCRIPT_ID						0x9F18
#define		TAG_TERM_COUNTRY_CODE			0x9F1A
#define		TAG_FLOOR_LIMIT					0x9F1B
#define		TAG_TERMINAL_ID					0x9F1C
#define		TAG_TERMINAL_RISK_DATA			0x9F1D
#define		TAG_IFD_SERIAL_NUMBER			0x9F1E
#define		TAG_TRANSACTION_TIME				0x9F21
#define		TAG_UPPER_OFFLINE_LIMIT			0x9F23
#define		TAG_CRYPTOGRAM					0x9F26
#define		TAG_CRYPTOGRAM_INFO_DATA		0x9F27
#define 	TAG_PIN_CERTIFICATE				0x9F2D
#define 	TAG_PIN_EXPONENT					0x9F2E
#define 	TAG_PIN_PK_REMAINDER				0x9F2F
#define		TAG_ISSUER_PK_EXPONENT			0x9F32
#define		TAG_TERMINAL_CAPABILITIES		0x9F33
#define		TAG_CVM_RESULTS					0x9F34
#define		TAG_TERMINAL_TYPE					0x9F35
#define 	TAG_ATC								0x9F36
#define		TAG_UNPREDICTABLE_NUMBER			0x9F37
#define		TAG_PDOL							0x9F38
#define		TAG_POS_ENTRY_MODE				0x9F39
#define 	TAG_AMT_REF_CURRENCY			0x9F3A
#define 	TAG_APP_REF_CURRENCY			0x9F3B
#define		TAG_TRANS_REF_CURRENCY_CODE		0x9F3C
#define		TAG_TRANS_REF_CURRENCY_EXP		0x9F3D
#define		TAG_ADDITIONAL_TERM_CAPABILITY	0x9F40
#define		TAG_TRANS_SEQ_COUNTER			0x9F41
#define		TAG_APP_CURRENCY_CODE			0x9F42
#define		TAG_APP_CURRENCY_EXPONENT		0x9F43		
#define 	TAG_APP_CURRENTCY_EXPONENT		0x9F44
#define		TAG_DATA_AUTH_CODE				0x9F45
#define		TAG_ICC_PK_CERTIFICATE			0x9F46
#define		TAG_ICC_PK_EXPONENT				0x9F47
#define		TAG_ICC_PK_REMAINDER				0x9F48
#define		TAG_DDOL							0x9F49
#define		TAG_SDA_TAGLIST						0x9F4A
#define		TAG_DDA_SDAD						0x9F4B
#define		TAG_DYNAMIC_DATA					0x9F4C
#define		TAG_LOG_ENTRY						0x9F4D
#define		TAG_MERCHANT_LOCATION			0x9F4E
#define 	TAG_LOG_FORMAT 					0x9F4F
#define		TAG_TERMINAL_CATEGORY_CODE		0x9F53
#define		TAG_VLP							0x9F7A
#define		TAG_FCI_ISSUER_DATA				0xBF0C


boolean isConstructedTag(byte *tag);

int32 parseTag(byte *tag, byte *tagLen, byte **constructedTlvData, int *constructedTlvDataLen);

boolean isTemplateTag(uint16 tag);

#ifdef __cplusplus
}
#endif

#endif

