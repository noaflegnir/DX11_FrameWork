/**
* @file		DirectX11Include.h
* @brief	DirectX11関係のインクルード群
* @author	小山智也
* @date		2019/03/26
*/
#pragma once

#include "../../Define/Define.h"
#include "WICTextureLoader.h"

#pragma warning (disable : 4005)
#pragma warning (disable : 4838)
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")