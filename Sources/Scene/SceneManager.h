/**
* @file		SceneManager.h
* @brief	ƒV[ƒ“ŠÇ—
* @author	¬R’q–ç
* @date		2019/04/11
*/

#pragma once

#include "BaseScene.h"
#include "../Define/Define.h"


class SceneManager : public Interface {

public:
	SceneManager(Systems* systems);
	~SceneManager();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	BaseScene* _scene;

};