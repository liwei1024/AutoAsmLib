/****************************************************************************************************************
 *
 *	CE自动汇编直译器: AA引擎 各语言通用DLL - aa_engine.dll
 *
 *	版本: v1.21 (2013/2/13)
 *	作者: axdx
 *
 *
 *	三个函数, 原型如下:
 *
 *
 *	1). 运行CE AA脚本
 *
 *		bool AutoAssemble(DWORD processID, char * aa_script, int command);
 *
 *			1). ProcessID: 进程ID
 *			2). aa_script: CE AA(自动汇编)脚本
 *			3). command: 1为运行[ENABLE], 0为运行[DISABLE]
 *			4). 返回: 运行成功返回真, 失败返回假
 *	    
 *	    
 *	2). 取地址
 *
 *		DWORD GetAddress(DWORD processID, char * address_line);
 *
 *			1). ProcessID: 进程ID
 *			2). address_line: 地址表达式, 支持指针+偏移+模块基址+AA脚本做的人造指针+游戏空间中存在的API
 *			3). 返回: 成功返回地址, 失败返回0
 *	    
 *	    
 *	3). 取AA引擎版本号
 *
 *		char * Ver();
 *
 *			返回版本号(文本)
 *	    
 *
 *	    
 *	易语言数据类型对照:
 *		int, DWORD = 整数型
 *		char * = 文本型(传址不打勾) 或 字节集型(传址打勾)
 *		bool = 逻辑型 或 整数型
 *	    
 *	    
 *	    
 *	VC2008动态调用DLL方法:
 *		HMODULE hDLL = LoadLibrary(TEXT("aa_engine.dll"));  // 载入DLL
 *
 *		// 调用AutoAssemble
 *		typedef BOOL (FAR WINAPI *PROC1)(DWORD,char*,int);
 *		PROC1 pAutoAssemble=(PROC1)GetProcAddress(hDLL,"AutoAssemble"); 
 *		(pAutoAssemble)(processID,aa_script,1);
 *
 *		// 调用GetAddress
 *		typedef DWORD (FAR WINAPI *PROC2)(DWORD,char*);
 *		PROC2 pGetAddress=(PROC2)GetProcAddress(hDLL,"GetAddress"); 
 *		DWORD addr = (pGetAddress)(processID,addr_line);
 *
 *		// 调用Ver
 *		typedef char *(FAR WINAPI *PROC3)();
 *		PROC3 pVer=(PROC3)GetProcAddress(hDLL,"Ver"); 
 *		char *ver = (pVer)();
 *
 *		FreeLibrary(hDLL);  // 释放DLL
 *
 *	    
 ****************************************************************************************************************/



#include <vector>
#include <string>

#include "autoassembler.h"

using namespace std;


// 1). 运行CE AA脚本
bool __stdcall AutoAssemble(HANDLE hProcess, const char *aa_script, int command)
{
	/*HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,processID);
	if (hProcess==NULL){
		return false;
	}*/
	bool retval = _autoassemble(hProcess, string(aa_script), command);
	//CloseHandle(hProcess);
	return retval;
}


// 2). 取地址
DWORD __stdcall GetAddress(HANDLE hProcess, const char *address_line)
{
	/*HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,processID);
	if (hProcess==NULL){
		return 0;
	}*/
	DWORD retval =  _getAddressFromAddrExpression(hProcess, string(address_line));
	//CloseHandle(hProcess);
	return retval;
}


// 3). 取AA引擎版本号
const char * __stdcall Ver()
{
	return "1.21";
}



// DLL入口点
BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	/* Returns TRUE on success, FALSE on failure */
	return TRUE;
}

