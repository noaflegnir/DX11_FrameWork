#include "ModelManager.h"
#include "../Systems.h"


ModelManager::ModelManager(Systems* systems)
	: _systems	 (systems)
	, _pmx		 (nullptr)
	, _pmxEnable (false)
{
}

ModelManager::~ModelManager()
{
}

HRESULT ModelManager::Init()
{
	const auto& window_ = _systems->GetWindow();

	_pmx = new PMXLoader(_systems);
	if (!_pmx)
	{
		MessageBox(window_->GetHWND(), "PMXローダーエラー", "エラー", MB_OK);
		return E_FAIL;
	}
	else if (_pmxEnable)
	{
		_pmx->Load();
	}

	return S_OK;
}

void ModelManager::Uninit()
{
	if (_pmxEnable) { _pmx->UnLoad(); }
	DeleteThis(_pmx);
}

void ModelManager::Update()
{
}

void ModelManager::Draw()
{
}
