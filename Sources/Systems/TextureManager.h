/**
* @file		Systems.h
* @brief	テクスチャの管理
* @author	小山智也
* @date		2019/03/19
*/
#pragma once

#include "BaseManager.h"
#include "../Define/Define.h"

// ファイルパスの変更あり
#include "../TextureResource.h"

class TextureManager : public Interface {

public:
	TextureManager(Systems* systems);
	~TextureManager(){}

	HRESULT Init() override;
	void Uninit() override;

private:


	HRESULT Load();
	void Unload();

};