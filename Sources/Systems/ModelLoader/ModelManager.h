/**
* @file		ModelManager.h
* @brief	モデル群の管理
* @author	小山智也
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

	bool _pmxEnable; //! pmxを使用するか falseでロードしない　trueでオールロード

	Systems* _systems;
	PMXLoader* _pmx;

};