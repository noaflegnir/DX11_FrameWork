#include "Gui.h"
#include "../Systems.h"

Gui::Gui(Systems* systems)
{
	this->_guiManager = systems->GetDebug()->GetGuiManager();

	_guiManager->Add(this);

}

Gui::~Gui()
{
}
