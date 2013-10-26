#ifndef _8583PROTOCOL_H_
#define _8583PROTOCOL_H_


typedef int (*SaveFieldData)(int fieldID, void *value, int len);

int parseISO8583Msg(unsigned char *src8583Msg, int srcLen, SaveFieldData storeFieldData);


#endif