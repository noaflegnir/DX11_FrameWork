/**
* @file		Gui.h
* @brief	GuiŠÖŒW‚ÌŠÇ—
* @author	¬R’q–ç
* @date		2019/03/22
*/
#pragma once

#include "../../Define/Define.h"
#include "ImGui/imgui.h"

class Systems;
class Gui {

	friend class GuiManager;

public:
	Gui(Systems* systems, string name);
	~Gui();

	virtual void GuiUpdate() {};

protected:
	string _name;

	
private:
	GuiManager* _guiManager;
};