
#include<Windows.h>
#include<iostream>

HANDLE hKillEvent;
HANDLE hReadFile;
HANDLE hWriteFile;
HANDLE hIOCP;
#define READ_KEY 1000
#define WRITE_KEY 2000
#define MAXWORKER_THREAD 3
HANDLE hWorkerThread[MAXWORKER_THREAD];
#define MAX_TRANS_DATA (4096*4096)
TCHAR g_Buffer[4096*4096] ;

LARGE_INTEGER g_LargeRead;
LARGE_INTEGER g_LargeWrite;

OVERLAPPED g_ReadOV;
OVERLAPPED g_WriteOV;

bool DispatchRead(DWORD Offset)
{
	g_LargeRead.QuadPart += Offset;

	g_WriteOV.Offset = g_LargeWrite.LowPart;
	g_WriteOV.OffsetHigh = g_LargeWrite.HighPart;



	DWORD ReadByte;

	

	bool Ret = WriteFile(hWriteFile, g_Buffer, Offset, &ReadByte, &g_ReadOV);
	if (Ret == FALSE)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			return false;
		}
		std::cout << "Copy="<< g_WriteOV.Offset + Offset << std::endl;
	}
	if (Ret == TRUE)
	{
		std::cout << "로딩 완료!" << std::endl;
		return true;
	}
	return true;
}
bool DispatchWrite(DWORD Offset)
{
	g_LargeWrite.QuadPart += Offset;

	g_ReadOV.Offset = g_LargeRead.LowPart;
	g_ReadOV.OffsetHigh = g_LargeRead.HighPart;



	DWORD ReadByte;

	if (Offset < MAX_TRANS_DATA)
	{
		SetEvent(hKillEvent);
		return true;
	}

	bool Ret = ReadFile(hReadFile, g_Buffer, Offset, &ReadByte, &g_ReadOV);
	if (Ret == FALSE)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			return false;
		}
		std::cout << "Roading=" << g_ReadOV.Offset + Offset << std::endl;
	}
	if (Ret == TRUE)
	{
		std::cout << "로딩 완료!" << std::endl;
		return true;
	}
	return true;
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	DWORD dwTransfer;
	ULONG_PTR pKey;
	OVERLAPPED* pOV;
	bool bRet;
	while (1)
	{
		
		if (WaitForSingleObject(hKillEvent, 0)== WAIT_OBJECT_0)
		{			std::cout << "DeadThread" << std::endl;
			break;
		}



		bool bRet = GetQueuedCompletionStatus(hIOCP, &dwTransfer,&pKey, &pOV, 1);

		if (bRet == TRUE)
		{
			if (pKey==READ_KEY)
			{
				if (!DispatchRead(dwTransfer))
				{
					::SetEvent(hKillEvent);
					std::cout << "Error!" << std::endl;
					return false;
				}
			}
			if (pKey==WRITE_KEY)
			{
				if (!DispatchWrite(dwTransfer))
				{
					::SetEvent(hKillEvent);
					std::cout << "Error!" << std::endl;
					return false;
				}
			}
		}
		else
		{
			bRet = GetLastError();
			if (bRet == WAIT_TIMEOUT)
			{
				continue;
			}
			if (bRet==ERROR_HANDLE_EOF)
			{
				SetEvent(hKillEvent);
			}
		}
	}
	return 1;
}
int main(void)
{

	hKillEvent = CreateEvent(0, TRUE, FALSE, 0);

	std::wstring readname = L"../../CJH_Project";
	std::wstring writename = L"Copy";
	std::wstring extream = L".Zip";

	readname += extream;
	writename += extream;

	hReadFile = CreateFile(readname.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	hWriteFile=CreateFile(writename.c_str(),GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	
	
	/*HANDLE WINAPI CreateIoCompletionPort(
		_In_     HANDLE    FileHandle,
		_In_opt_ HANDLE    ExistingCompletionPort,
		_In_     ULONG_PTR CompletionKey,
		_In_     DWORD     NumberOfConcurrentThreads //운영 체제가 I / O 완료 포트에 대한 I / O 완료 패킷을 동시에 처리 할 수있는 최대 스레드 수입니다
	);*/


	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	::CreateIoCompletionPort(hReadFile, hIOCP, READ_KEY, 0);
	::CreateIoCompletionPort(hWriteFile, hIOCP, WRITE_KEY, 0);
	DWORD dwThreadID;

	
	for (int i = 0; i < MAXWORKER_THREAD; i++)
	{
		
		hWorkerThread[i] = CreateThread(NULL, 0, WorkerThread, nullptr, 0, &dwThreadID);
	}

	DWORD ReadData;
	DWORD dwTrans= MAX_TRANS_DATA;
	ReadFile(hReadFile, g_Buffer, dwTrans, &ReadData,&g_ReadOV);
	


	WaitForMultipleObjects(MAXWORKER_THREAD, hWorkerThread, TRUE, INFINITE);
	CloseHandle(hReadFile);
	CloseHandle(hWriteFile);
	CloseHandle(hIOCP);

	for (int i = 0; i < MAXWORKER_THREAD; i++)
	{
		CloseHandle(hWorkerThread[i]);
	}



	
}