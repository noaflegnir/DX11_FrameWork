/**
 * @file	Main.h
 * @brief	メイン
 * @author	小山智也
 * @date	2019/03/17
 */

#include "Windows/API.h"
#include "Windows/Windows.h"

// @fn		WinMain
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// メモリーリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Windows window;

	if (FAILED(window.Init(hInstance, nCmdShow))) { return 1; }

	window.Loop(Windows::FPS);

	return (int)window.Uninit();
}