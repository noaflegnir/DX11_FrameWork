/**
* @file		Graphics.h
* @brief	グラフィックス系
* @author	小山智也
* @date		2019/03/17
*/
#pragma once

#include "../Windows/Windows.h"

class Graphics {

	friend class Windows;
	friend class Systems;

public:
	static constexpr int WIDTH = 1280;
	static constexpr int HEIGHT = 720;

	Windows* GetWindow(void) { return window_; }		// ウィンドウクラスの受け渡し

protected:
	Graphics(Windows* window) { window_ = window; }

	virtual HRESULT Init(void) = 0;	// 初期化処理
	virtual void	Uninit(void) = 0;	// 後処理
	virtual HRESULT DrawBegin(void) = 0;	// 描画開始
	virtual void	DrawEnd(void) = 0;	// 描画終了

	virtual void    ClearRenderer(void) {}	// 画面のクリア

	Windows* window_;		// ウィンドウクラスへのポインタ

};