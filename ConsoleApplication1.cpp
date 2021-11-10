// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <cstring>
#include <TlHelp32.h>
#include <stdlib.h>

using namespace std;

uintptr_t GetModuleBaseAddress(DWORD, const wchar_t*);
DWORD GetProcId(const wchar_t*);

int main()
{
	cout << "IIDX P1 Automatic Screen Positioner By VELIUS" << endl;
	cout << "Go back to Bistro now. Make sure you're in the song select" << endl;
	HWND hwnd = FindWindowA(NULL, "beatmania IIDX 28 BISTROVER main");
	HWND foreground = GetForegroundWindow();
	if (hwnd == NULL)
	{
		cout << "Cannot find window. Make sure Bistro has been started." << endl;
		Sleep(3000);
		exit(-1);
	}
	else
	{
		DWORD64 procID = GetProcId(L"launcher.exe");
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);
		if (procID == NULL)
		{

			cout << "Cannot obtain process. Make sure you're using BT 5.36" << endl;
			Sleep(3000);
			exit(-1);
			
		}

		if (handle == NULL || handle == INVALID_HANDLE_VALUE)
		{
			cout << "Handle not found. Try running as Admin and try again." << endl;
			cout << "Error code: " << GetLastError();
			Sleep(3000);
			exit(-1);
		}
		else
		{
			uintptr_t Base = GetModuleBaseAddress(procID, L"bm2dx.dll");
			int gameplayflag = 0;
			int startflag = 0;
			int songlistflag = 0;
			unsigned int gameplayread;
			unsigned int startread;
			DWORD64 gameplayaddress = Base + 0xD4F44C;
			DWORD64 startaddress = Base + 0x5B54984;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			for (;;) {
				foreground = GetForegroundWindow();
				if (hwnd == foreground)
				{
					break;
				}
				Sleep(1000);
			}
			SetWindowPos(hwnd, 0, rect.left, rect.top, 2560, 1440, SWP_NOMOVE);
			for (;;)
			{
				
				ReadProcessMemory(handle, (BYTE*)gameplayaddress, &gameplayread, sizeof(gameplayread), 0);
				ReadProcessMemory(handle, (BYTE*)startaddress, &startread, sizeof(startread), 0);
				if (gameplayread == 640 && gameplayflag == 0)
				{
					SetWindowPos(hwnd, 0, rect.left, rect.top, rect.right, rect.bottom, SWP_NOSIZE);
					gameplayflag = 1;
					songlistflag = 0;
				}
				if (startread == 0 && startflag == 1)
				{
					SetWindowPos(hwnd, 0, rect.left - 1480, rect.top, rect.right, rect.bottom, SWP_NOSIZE);
					startflag = 0;
				}
				if (startread == 30575 && songlistflag == 1 && startflag == 0)
				{
					SetWindowPos(hwnd, 0, rect.left - 740, rect.top, rect.right, rect.bottom, SWP_NOSIZE);
					startflag = 1;
				}

				if (gameplayread == 1280 && songlistflag == 0 && startread == 0 && startflag == 0)
				{

					SetWindowPos(hwnd, 0, rect.left-1480, rect.top, rect.right, rect.bottom, SWP_NOSIZE);
					songlistflag = 1;
					gameplayflag = 0;
				}
				
				
				
				Sleep(500);

			}

		}
	}
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

DWORD GetProcId(const wchar_t* procName)
{
	DWORD procId;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
