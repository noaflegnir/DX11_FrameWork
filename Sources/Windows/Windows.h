/**
* @file		Windows.h
* @brief	ウィンドウ
* @author	小山智也
* @date		2019/03/17
*/
#pragma once

#include <Windows.h>
#include "API.h"
#include "../Graphics/Graphics.h"

class Systems;
class Windows {

	static constexpr char* CLASS_NAME = "Game";			//! クラス名
	static constexpr char* WINDOW_NAME = "DX11_Sample";	//! ウィンドウ名
	static constexpr int   WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX;	// ウィンドウスタイル				// FPSの設定
	//#define CLASS_NAME "sample"
	//#define WINDOW_NAME "Magic Enchant Ver2.0"

	static constexpr int  SCREEN_WIDTH = 1280;	// @def	ウィンドウサイズ幅
	static constexpr int  SCREEN_HEIGHT = 720;	// @def	ウィンドウサイズ高さ

public:

	static constexpr int  FPS = 60;

	/* @brief	コンストラク	*/
	Windows();
	/* @brief	デストラクタ	*/
	~Windows(){}

	// Getter
	float     GetFps(void) { return _fps; }	// 実際のFPS
	HWND      GetHWND(void) { return _hWnd; }	// HWND
	MSG       GetMsg(void) { return _msg; }	// MSG
	HINSTANCE GetHInstance(void) { return _hInstance; }	// HINSTANCE

	Graphics* GetGraphics(void) { return _graphics; }

	/* @brief	初期化
	 * @param	(Instance) ハンドル
	 * @parsm	(cmdshow) ハンドル　
	 * @return	成功か失敗か		*/
	HRESULT Init(HINSTANCE Instance, int CmdShow);


	/* @brief	ゲームループ
	 * @param	(Fps) FPS値			*/
	void Loop(DWORD Fps);


	/* @brief	解放
	 * @return	wparam				*/
	WPARAM  Uninit(void);


private:
	/* @brief	更新
	 * @return 初期化の有無			*/
	bool Update();

	/* @brief	描画				*/
	void Draw();

	/* @brief	ウィンドウの設定	*/
	void SetWindowParam();

	/* @brief	ウィンドウの生成
	 * @param	(CmdShow) ウィンドウ生成時のフラグ	*/
	void SetWindow(int CmdShow);

	/* @brief	メッセージプロセス	*/
	bool MsgProcess();

	/* @brief	ゲームの初期化		*/
	bool InitGame();

	Graphics*	_graphics;
	Systems*	_systems;


	HWND		_hWnd;
	HINSTANCE	_hInstance;
	MSG			_msg;
	WNDCLASSEX	_wcex;


	int	_nowTime;
	int _oldTime;
	int _timeFPS;
	int _counterFPS;
	float _fps;

	inline LONG WindowCenter(LONG dr, LONG wr) { return Hf(dr - wr) > 0 ? Hf(dr - wr) : 0; }


	//ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};