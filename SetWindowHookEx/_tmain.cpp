#include <Windows.h>
#include <iostream>
#include <tchar.h>
using namespace std;
int _tmain() {
	HWND hwnd = FindWindow(NULL,_T("League of Legends (TM) Client"));
	if (hwnd == NULL) {
		_tprintf(_T("target window could not be found\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	if (tid == NULL) {
		_tprintf(_T("thread id of could not be found\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	HMODULE dll = LoadLibraryEx(L"test.dll", NULL, DONT_RESOLVE_DLL_REFERENCES); 
	if (dll == NULL) {
		_tprintf(_T("dLL could not be found\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook"); 
	if (addr == NULL) {
		_tprintf(_T("function could not be found\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	HHOOK handle = SetWindowsHookEx(WH_KEYBOARD, addr, dll, tid); 
	//  WH_KEYBOARD manually
    //  WH_GETMESSAGE auto
	if (handle == NULL) {
		_tprintf(_T("SetWindowsHookEx can be failure\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	//PostThreadMessage(tid, WM_NULL, NULL, NULL);//WH_GETMESSAGE auto
	_tprintf(_T("hook set and triggered can be OK\r\n"));
	_tprintf(_T("press any key to unhook and unload the dll\r\n"));
	system("pause > nul");

	// Unhooking
	BOOL unhook = UnhookWindowsHookEx(handle);
	if (unhook == FALSE) {
		_tprintf(_T("remove the hook can be failure\r\n"));
		system("pause");
		return EXIT_FAILURE;
	}
	_tprintf(_T("success,press any key to exit\r\n"));
	system("pause > nul");
	return EXIT_SUCCESS;
}