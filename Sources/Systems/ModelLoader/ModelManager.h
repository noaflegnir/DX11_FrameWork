/**
* @file		ModelManager.h
* @brief	���f���Q�̊Ǘ�
* @author	���R�q��
* @date		2019/03/26
*/
#pragma once

#include "../BaseManager.h"
#include "PMXLoader/PMXLoader.h"

class Systems;
class ModelManager {


	friend class ModelLoader;
public:
	ModelManager(Systems* systems);
	~ModelManager();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:

	bool _pmxEnable; //! pmx���g�p���邩 false�Ń��[�h���Ȃ��@true�ŃI�[�����[�h

	Systems* _systems;
	PMXLoader* _pmx;

};