/**
* @file		GuiManager.h
* @brief	ImGui�̊Ǘ�
* @author	���R�q��
* @date		2019/03/22
*/
#pragma once
#include "../BaseManager.h"
#include "Gui.h"

class Systems;
class Debug;
class GuiManager : public BaseManager<Gui> {

public:
	GuiManager();
	~GuiManager();

	HRESULT Init()   override;
	void	Uninit() override;
	void	Update() override;
	void	Draw()   override;

	void	GuiUpdate();


private:
	friend Gui;
	Debug* _debug;

	void StartFrame();
	void EndFrame();

	bool _draw;

};