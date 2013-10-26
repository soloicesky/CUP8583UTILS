#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#define FIELD_TPDU		-2
#define FIELD_MSG_HEADER -1
#define FIELD_MSG_CODE   0

#define LEN_TPDU				10
#define LEN_MSG_HEADER			12
#define LEN_MSG_CODE			4
#define LEN_BITMAP				8
#define LEN_PAN					19
#define LEN_PROC_CODE			6
#define LEN_TRAN_AMT			12
#define LEN_POS_STAN			6
#define LEN_LOCAL_TIME			6
#define LEN_LOCAL_DATE			4
#define LEN_EXP_DATE			4
#define LEN_SETTLE_DATE			4
#define LEN_ENTRY_MODE			4	// 为了处理左对齐方式
#define LEN_PAN_SEQ_NO			3
#define LEN_SVR_CODE			2
#define LEN_CAPTURE_CODE		     2
#define LEN_ACQUIRER_ID			11
#define LEN_TRACK2				37
#define LEN_TRACK3				104
#define LEN_RRN			     12
#define LEN_AUTH_CODE			6
#define LEN_RSP_CODE			2
#define LEN_TERM_ID				8
#define LEN_MERCHANT_ID			15
#define LEN_ADD_RSP_DATA		     25
#define LEN_FIELD48				322
#define LEN_CURRENCY_CODE		3
#define LEN_PIN_DATA			8
#define LEN_SECURITY_INFO		16
#define LEN_EXT_AMOUNT			40 //20
#define LEN_ICC_DATA			255
#define LEN_EP_DATA				100
#define LEN_FIELD60				17//13
#define LEN_ORIGINAL_MSG		     29
#define LEN_FIELD62				512
#define LEN_FIELD63				163
#define LEN_MAC_DATA			8


typedef struct _element_{
	int fieldID;
	void *value;
	int len;
}ELEMENT;


#define Attr_a  0
#define Attr_b 1
#define Attr_n 2
#define Attr_z 3
#define Attr_UnUsed 4
#define Attr_Over 5

#define Attr_var1  0
#define Attr_var2  1
#define Attr_fix  2

typedef struct _fieldattr_{
	int valueAttr;
	int lenAttr;
	int len;
}FieldAttr;


typedef struct field_attr_dict_{
	FieldAttr *fdAttrSet;
	int	iCount;
}FieldAttrDict;


extern FieldAttrDict fdAttrDict;

#endif