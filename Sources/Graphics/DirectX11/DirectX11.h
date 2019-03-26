/**
* @file		DirectX11.h
* @brief	DirectX11の基本動作
* @author	小山智也
* @date		2019/03/18
*/
#pragma once

#pragma warning (disable : 4005)
#pragma warning (disable : 4838)

#include "DirectX11Include.h"
#include "../../Windows/Windows.h"
#include "../Graphics.h"


class DirectX11 : public Graphics {

	friend Windows;

public:
	ID3D11Device*        GetDevice()		{ return _device; }		// デバイスの受け渡し
	ID3D11DeviceContext* GetDeviceContext() { return _deviceContext; }	// コンテキストの受け渡し
	IDXGISwapChain*		 GetSwapChain()		{ return _swapChain;; }

private:
	DirectX11(Windows* window);

	HRESULT Init()		override;
	void Uninit()		override;
	HRESULT DrawBegin() override;
	void DrawEnd()		override;

	void ClearRenderer(void) override;		// 画面のクリア

	HRESULT InitAll();
	bool SetDevice();

	IDXGISwapChain*         _swapChain;
	ID3D11Device*           _device;			// DirectXの機能
	ID3D11DeviceContext*    _deviceContext;		// GPUの方
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStencilView;

};