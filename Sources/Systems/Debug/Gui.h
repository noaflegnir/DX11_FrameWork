/**
* @file		Gui.h
* @brief	Gui�֌W�̊Ǘ�
* @author	���R�q��
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