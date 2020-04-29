
#include<Windows.h>
#include<iostream>

OVERLAPPED g_ReadOV;
LARGE_INTEGER g_LargeRead;
LARGE_INTEGER FileSize;
TCHAR* g_pLoadBuffer=0;
#define MAX_TRANS_DATA 4096*4096
bool AsyncChuckLoad(const TCHAR*FileName);
int main(void)
{

	AsyncChuckLoad(L"../../01_TBasis3DSamples.7z");

}

bool FileRead(HANDLE hFile,DWORD offset)
{	g_LargeRead.QuadPart += offset;

	g_ReadOV.Offset		= g_LargeRead.LowPart;
	g_ReadOV.OffsetHigh = g_LargeRead.HighPart;
	TCHAR*pData = &g_pLoadBuffer[g_LargeRead.LowPart];

	DWORD dwTrans= MAX_TRANS_DATA;
	DWORD ReadByte; 

	if (FileSize.QuadPart - g_LargeRead.QuadPart < dwTrans)
	{
		dwTrans = FileSize.QuadPart - g_LargeRead.QuadPart;
	}

	bool Ret = ReadFile(hFile, pData, dwTrans, &ReadByte, &g_ReadOV);
	if (Ret==FALSE)
	{
		if (GetLastError()!=ERROR_IO_PENDING)
		{
			return true;
		}
	}
	if (Ret==TRUE)
	{
		std::cout << "로딩 완료!" << std::endl;
		return true;
	}
	return true;
}

bool AsyncChuckLoad(const TCHAR*FileName)
{

	HANDLE hReadFile = CreateFile(FileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);

	
	GetFileSizeEx(hReadFile, &FileSize);
	
	if (hReadFile!=NULL)
	{
		ZeroMemory(&g_ReadOV, sizeof(OVERLAPPED));
		g_pLoadBuffer = new TCHAR[FileSize.QuadPart];
		bool bPending = TRUE;
		bool bResult;
		FileRead(hReadFile,0);
		DWORD dwTrans=0;
		while (bPending)
		{
		
			bResult = WaitForSingleObject(hReadFile, 0);
			if (bResult==WAIT_OBJECT_0)
			{
				bResult = GetOverlappedResult(hReadFile, &g_ReadOV, &dwTrans, TRUE);
				if (bResult==TRUE)
				{
					if (g_LargeRead.LowPart+dwTrans<FileSize.QuadPart)
					{
						
						std::cout << g_LargeRead.LowPart << std::endl;
						FileRead(hReadFile, dwTrans);
					}
					else
					{
						bPending = FALSE;
						std::cout << g_LargeRead.LowPart+ dwTrans << std::endl;
					
					}
				}
			
			}
			
			
		}
	}
	return 1;
	delete g_pLoadBuffer;
	CloseHandle(hReadFile);
	
}