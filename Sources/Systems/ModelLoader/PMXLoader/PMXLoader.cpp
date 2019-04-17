#include "PMXLoader.h"
#include "../../Systems.h"


PMXLoader::PMXLoader(Systems* systems)
	: _systems (systems)
{
}

PMXLoader::~PMXLoader()
{
	DeleteThis(_modRes);
}

HRESULT PMXLoader::Load()
{
	_modRes = new ModelResource();

	if (const auto& graphics_ = _systems->GetGraphics())
	{
		if (const auto& wrapper_ = graphics_->GetWrapper())
		{
			for (int i = 0; i < _modRes->MAX;i++)
			{
				PMXModelData data{};
				// ���b�p�[���烍�[�h���Ăяo���ĉ�
				wstring path(_modRes->PMXModelFilePath[i].begin(), _modRes->PMXModelFilePath[i].end());
				HRESULT hr = S_OK;

				if (FAILED(hr))
				{
					MessageBox(_systems->GetWindow()->GetHWND(), ".pmx�̃��[�h�Ɏ��s", "�G���[", MB_OK);
					return hr;
				}
				// ���[�h���ĕϐ��ɂԂ�����
				//wrapper_->SetPMXModelData(data, i);
			}
		}
	}
	return S_OK;
}

void PMXLoader::UnLoad()
{
}
