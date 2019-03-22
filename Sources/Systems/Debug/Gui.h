/**
* @file		Gui.h
* @brief	GuiŠÖŒW‚ÌŠÇ—
* @author	¬R’q–ç
* @date		2019/03/22
*/
#pragma once

class Systems;
class Gui {

	friend class GuiManager;

public:
	Gui(Systems* systems);
	~Gui();

	virtual void GuiUpdate() {};

	
private:
	GuiManager* _guiManager;
};