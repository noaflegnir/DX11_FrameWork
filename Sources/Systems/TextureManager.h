/**
* @file		Systems.h
* @brief	�e�N�X�`���̊Ǘ�
* @author	���R�q��
* @date		2019/03/19
*/
#pragma once

#include "BaseManager.h"
#include "../Define/Define.h"

// �t�@�C���p�X�̕ύX����
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