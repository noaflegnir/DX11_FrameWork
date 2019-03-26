/**
* @file		ModelManager.h
* @brief	ƒ‚ƒfƒ‹ŒQ‚ÌŠÇ—
* @author	¬R’q–ç
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
	Systems* _systems;
	PMXLoader* _pmx;

};