#include "ModelManager.h"
#include "../Systems.h"


ModelManager::ModelManager(Systems* systems)
	: _systems	(systems)
	, _pmx		(nullptr)
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
		MessageBox(window_->GetHWND(), "pmxError", "ƒGƒ‰[", MB_OK);
		return E_FAIL;
	}
	else{ _pmx->Load(); }

	return S_OK;
}

void ModelManager::Uninit()
{
	_pmx->UnLoad();
	DeleteThis(_pmx);
}

void ModelManager::Update()
{
}

void ModelManager::Draw()
{
}
