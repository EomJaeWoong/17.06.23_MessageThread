#ifndef __MESSAGE__H__
#define __MESSAGE__H__

struct st_MSG_HEAD
{
	short shType;
	short shStrLen;
};

#define dfTYPE_ADD_STR		0
#define dfTYPE_DEL_STR		1
#define dfTYPE_PRINT_LIST	2
#define dfTYPE_QUIT			3	

#endif