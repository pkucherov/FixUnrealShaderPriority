// FixShaderCompilerW32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void SetProcessProirity(LPCWSTR ProcessName, DWORD Priority)
{
	PROCESSENTRY32 proc32;
	HANDLE hSnap;
	if (hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	if (hSnap == INVALID_HANDLE_VALUE)
	{

	}
	else
	{
		proc32.dwSize = sizeof(PROCESSENTRY32);
		while ((Process32Next(hSnap, &proc32)) == TRUE)
		{
			if (_wcsicmp(proc32.szExeFile, ProcessName) == 0)
			{
				wprintf(L"Found %s\n", ProcessName);
				HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SET_INFORMATION , TRUE, proc32.th32ProcessID);
				DWORD p = GetPriorityClass(h);
				wprintf(L"Handle: %u Priority:%u Is %sat requested priority\n", h, p, p == Priority ? L"":L"not ");
				BOOL ok = SetPriorityClass(h, Priority);
				CloseHandle(h);
			}
		}
		CloseHandle(hSnap);
	}
}

int main()
{
	while (1) {
		SetProcessProirity(L"ShaderCompileWorker.exe", NORMAL_PRIORITY_CLASS );
		Sleep(500);
	}
}