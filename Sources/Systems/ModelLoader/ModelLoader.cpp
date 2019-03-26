#include "ModelLoader.h"
#include "../Systems.h"


ModelLoader::ModelLoader(Systems* systems)
	: Interface (systems)
	, _manager  (nullptr)
{
}

ModelLoader::~ModelLoader()
{
}

HRESULT ModelLoader::Init()
{
	_manager = new ModelManager(_systems);
	if (!_manager)
	{
		MessageBox(_systems->GetWindow()->GetHWND(), "ModelManager Error", "エラー", MB_OK);
		return E_FAIL;
	}
	else
	{ 
		if (FAILED(_manager->Init()))
		{
			MessageBox(_systems->GetWindow()->GetHWND(), "manager init error", "エラー", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

void ModelLoader::Uninit()
{
	_manager->Uninit();
	DeleteThis(_manager);
}

void ModelLoader::Update()
{
}

void ModelLoader::Draw()
{
}
