/**
* @file		DirectX11Wrapper.h
* @brief	DirectX11�̃��b�p�[
* @author	���R�q��
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