#include "SceneManager.h"

SceneManager::SceneManager(Systems* systems)
	: Interface(systems)
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
	// カメラマネージャをnewする
	// シーンをnewする
	return E_NOTIMPL;
}

void SceneManager::Uninit()
{
}

void SceneManager::Update()
{
}

void SceneManager::Draw()
{
}
