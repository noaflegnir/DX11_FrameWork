/**
* @file		ModelLoader.h
* @brief	ƒ‚ƒfƒ‹ŒQ
* @author	¬R’q–ç
* @date		2019/03/26
*/
#pragma once

#include "../BaseManager.h"
#include "ModelManager.h"

class ModelLoader : public Interface {

public:
	ModelLoader(Systems* systems);
	~ModelLoader();

	HRESULT Init()	override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

private:
	//Systems* _systems;
	ModelManager* _manager;

};