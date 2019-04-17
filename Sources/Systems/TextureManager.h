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

	friend Systems;

public:
	~TextureManager();


private:
	TextureManager(Systems* systems);
	HRESULT Init() override;
	void Uninit() override;

	HRESULT Load();
	void Unload();

	TextureResource* _texRes;

};