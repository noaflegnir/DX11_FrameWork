#include "Gui.h"
#include "../Systems.h"

Gui::Gui(Systems* systems, string name)
	: _guiManager	(nullptr)
{
#ifdef _DEBUG
	this->_name = name;

	this->_guiManager = systems->GetDebug()->GetGuiManager();

	_guiManager->Add(this);
#endif

}

Gui::~Gui()
{
#ifdef _DEBUG
	_guiManager->Remove(this);
#endif
}
