#include "Input.h"
#include "KeyInput.h"
#include "XInput.h"

Input::Input(Systems* systems)
	: Interface (systems)
	, _keyboard	(nullptr)
{
	ZeroMemory(&_state, sizeof(INPUT_STATE));
}

Input::~Input(void)
{
	DeleteThis(_keyboard);
}

HRESULT Input::Init(void)
{
	_keyboard = new KeyInput(this);
	if (FAILED(_keyboard->Init()))
	{
		return E_FAIL;
	}

	//_ctrl = new XInput(this);
	//if (!_ctrl)
	//{
	//	return E_FAIL;
	//}

	return S_OK;
}


void Input::Update(void)
{
	_keyboard->Update();
	//_ctrl->Update(_state);

}

