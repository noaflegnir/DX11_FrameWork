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

public:
	TextureManager(Systems* systems);
	~TextureManager(){}

	HRESULT Init() override;
	void Uninit() override;

private:


	HRESULT Load();
	void Unload();

};