// MessageThread.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

//-----------------------------------------------
// ������ ��, ���ڿ� ����Ʈ
//-----------------------------------------------
list<wstring>		g_List;

//-----------------------------------------------
// ������ �޽��� ť (������ �˳��ϰ� ũ�� 4~5�� ����Ʈ)
//-----------------------------------------------
CAyaStreamSQ		g_msgQ;

//-----------------------------------------------
// shutdown flag
//-----------------------------------------------
bool b_shutdown = false;

#define MAX_THREAD		3

unsigned __stdcall WorkerThread(LPVOID workerParam);

int _tmain(int argc, _TCHAR* argv[])
{
	//-----------------------------------------------
	// Worker Thread Handle
	//-----------------------------------------------
	HANDLE hWorkerThread[MAX_THREAD];

	//-----------------------------------------------
	// Worker Event Handle
	//-----------------------------------------------
	HANDLE hWorkerEvent;

	char *cStr = "PROCADEMY";

	srand(time(NULL));

	/////////////////////////////////////////////////////
	// Thread Create
	/////////////////////////////////////////////////////
	for (int iCnt = 0; iCnt < MAX_THREAD; iCnt++)
	{
		hWorkerThread[iCnt] = (HANDLE)_beginthreadex(
			NULL,
			0,
			WorkerThread,
			(LPVOID)0,
			0,
			NULL);
	}

	/////////////////////////////////////////////////////
	// Event Create
	/////////////////////////////////////////////////////
	hWorkerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	/////////////////////////////////////////////////////
	// Message Create
	/////////////////////////////////////////////////////
	while (1)
	{
		st_MSG_HEAD *pMsgHeader = new st_MSG_HEAD;

		pMsgHeader->shType = rand() % 3;
		pMsgHeader->shStrLen = (rand() % 6) + 3;

		/////////////////////////////////////////////////
		// Exit code check
		/////////////////////////////////////////////////
		if (_kbhit())
		{
			if (' ' == _getch())
				pMsgHeader->shType = 3;
		}

		/////////////////////////////////////////////////
		// Message Input
		/////////////////////////////////////////////////
		g_msgQ.Lock();
		g_msgQ.Put((char *)pMsgHeader, sizeof(st_MSG_HEAD));
		g_msgQ.Put((char *)cStr, pMsgHeader->shStrLen);

		/////////////////////////////////////////////////
		// wake WorkerThread
		/////////////////////////////////////////////////
		SetEvent(hWorkerEvent);

		Sleep(50);
	}

	return 0;
}

unsigned __stdcall WorkerThread(LPVOID workerParam)
{
	printf("Worker Thread [%d] Running..\n", GetCurrentThreadId());

	while (!b_shutdown)
	{
		st_MSG_HEAD *pMsgHeader;
		char *cMsg;

		g_msgQ.Lock();
		g_msgQ.Get((char *)pMsgHeader, sizeof(st_MSG_HEAD));

		switch (pMsgHeader->shType)
		{
		case dfTYPE_ADD_STR:
			break;

		case dfTYPE_DEL_STR:
			break;

		case dfTYPE_PRINT_LIST:
			break;

		case dfTYPE_QUIT:
			b_shutdown = true;
		}
		g_msgQ.Unlock();
	}
	
	return 0;
}