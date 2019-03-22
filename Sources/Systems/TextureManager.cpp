#include "TextureManager.h"
#include "Systems.h"
#include "../Graphics/DirectX11/WICTextureLoader.h"

TextureManager::TextureManager(Systems* systems)
	: Interface (systems)
{
}

HRESULT TextureManager::Init()
{
	HRESULT hr = Load();

	if (FAILED(hr))
	{
		return E_FAIL;
	}
	return S_OK;
}

void TextureManager::Uninit()
{
	Unload();
}

HRESULT TextureManager::Load()
{
	//HRESULT hr = DirectX::CreateWICTextureFromFile()
	//_tex->TextureFilePath[0];

	return S_OK;
}

void TextureManager::Unload()
{
}
