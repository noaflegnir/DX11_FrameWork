/**
* @file		Debug.h
* @brief	ImGui‚ÌŠÇ—
* @author	¬R’q–ç
* @date		2019/03/22
*/
#pragma once

#include "../BaseManager.h"
#include "ImGui/imgui.h"
#include "GuiManager.h"

class Systems;
class Debug : public Interface {

public:
	Debug(Systems* systems);
	~Debug();

	HRESULT Init()	override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	inline GuiManager*	GetGuiManager(void) { return _gui; }


private:
	GuiManager* _gui;
};