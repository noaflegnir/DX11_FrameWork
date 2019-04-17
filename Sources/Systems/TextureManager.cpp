#include "TextureManager.h"
#include "Systems.h"
#include "BaseManager.h"




TextureManager::TextureManager(Systems* systems)
	: Interface (systems)
{
}

TextureManager::~TextureManager()
{
	Unload();
	DeleteThis(_texRes);
}

HRESULT TextureManager::Init()
{
	_texRes = new TextureResource();

	Load();
	return S_OK;
}

void TextureManager::Uninit()
{
}

HRESULT TextureManager::Load()
{
	if (!_systems) { return E_FAIL; }

	HRESULT hr = S_OK;

	if (const auto& graphics_ = _systems->GetGraphics())
	{

		if (const auto& wrapper_ = graphics_->GetWrapper())
		{
			for (int i = 0; i < _texRes->MAX;i++)
			{
				hr = wrapper_->LoadTexture(_texRes->TextureFilePath[i], 0);
				if (FAILED(hr))
				{
					MessageBox(_systems->GetWindow()->GetHWND(), "テクスチャのロードに失敗", "エラー", MB_OK);
					return hr;
				}
			}
		}
	}

	return hr;
}

void TextureManager::Unload()
{
	if (const auto& graphics_ = _systems->GetGraphics())
	{
		if (const auto& wrapper_ = graphics_->GetWrapper())
		{
			for (int i = 0; i < _texRes->MAX;i++)
			{
				wrapper_->ReleaseTexture(i);
			}
		}
	}
}
