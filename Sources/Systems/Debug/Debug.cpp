#include "Debug.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "../../Graphics/DirectX11/DirectX11.h"
#include "../../Windows/Windows.h"
#include "../Systems.h"


Debug::Debug(Systems* systems)
	: Interface		(systems)
{
}

Debug::~Debug()
{
}

HRESULT Debug::Init()
{
#ifdef _DEBUG

	_gui = new GuiManager();
	if (_gui)
	{
		if(FAILED(_gui->Init()))
		{
			return E_FAIL;
		}
	}
	return S_OK;
#endif

	return S_OK;
}

void Debug::Uninit()
{
#ifdef _DEBUG
	if (_gui)
	{
		_gui->Uninit();
	}
	DeleteThis(_gui);
#endif
}

void Debug::Update()
{
#ifdef _DEBUG
	if (_gui)
	{
		_gui->Update();
	}
#endif
}

void Debug::Draw()
{
#ifdef _DEBUG
	if (_gui)
	{
		_gui->Draw();
	}
#endif
}
