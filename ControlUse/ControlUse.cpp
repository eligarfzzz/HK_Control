// ControlUse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<thread>
#include"HK_Control.h"

HWND GetConsoleHwnd(void) {
#define MY_BUFSIZE 1024 // Buffer size for console window titles.     
	HWND hwndFound;         // This is what is returned to the caller.   
	wchar_t pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated         
	// WindowTitle.     
	wchar_t pszOldWindowTitle[MY_BUFSIZE];
	// Contains original  
	// WindowTitle.      
	// Fetch current window title.   
	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.      
	wsprintf(pszNewWindowTitle, L"%d/%d", GetTickCount(), GetCurrentProcessId());

	// Change current window title.     
	SetConsoleTitle(pszNewWindowTitle);
	// Ensure window title has been updated.  

	Sleep(40);
	// Look for NewWindowTitle.  
	hwndFound = FindWindow(NULL, pszNewWindowTitle);
	// Restore original window title.     
	SetConsoleTitle(pszOldWindowTitle);
	return(hwndFound);
}
int main()
{
	HK_Control hk("192.168.1.253", 8000, "admin", "yourpassword");

	std::cout << hk.Login() << std::endl;
	std::cout << hk.Play(GetConsoleHwnd()) << std::endl;
	Sleep(100);
	std::cout << hk.CaptureBMP("./1.bmp") << std::endl;
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
