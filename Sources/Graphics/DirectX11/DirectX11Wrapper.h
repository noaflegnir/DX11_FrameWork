/**
* @file		DirectX11Wrapper.h
* @brief	DirectX11のラッパー
* @author	小山智也
* @date		2019/03/18
*/
#pragma once

#include "WICTextureLoader.h"
#include "DirectX11.h"

class DX11Wrapper {

	friend DirectX11;

public:
	HRESULT LoadTexture(string fileName);
};