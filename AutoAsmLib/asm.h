#pragma once
#include <windows.h>

DWORD __stdcall GetAddress(HANDLE hProcess, const char *address_line);

bool __stdcall AutoAssemble(HANDLE hProcess, const char *aa_script, int command = 1);

const char * __stdcall Ver();