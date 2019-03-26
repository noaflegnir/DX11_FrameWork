#include "Systems.h"

Systems* Systems::_system;

Systems::Systems(Windows* window)
	: _window	(window)
	, _graphics	(nullptr)
{
	_graphics = window->GetGraphics();
}


HRESULT Systems::Init(void)
{
	_system = this;

	for (auto& i : _manager) { i = nullptr; }

	//!!! �����ŃN���G�C�g����̂̓T�E���h��C���v�b�g�Ȃǂ̂��� + �V�[���}�l�[�W��
	if (!Create<Debug>			((int)SYSTEM_NUM::DEBUG	  ,	"�f�o�b�O"	))	{ return E_FAIL; }
	if (!Create<TextureManager>	((int)SYSTEM_NUM::TEXTURE ,	"�e�N�X�`��"))	{ return E_FAIL; }
	if (!Create<Input>			((int)SYSTEM_NUM::INPUT	  , "����"		))	{ return E_FAIL; }

	/* pmx���f�����[�_�[�͐���i�K */
	if (!Create<ModelLoader>	((int)SYSTEM_NUM::MODEL	  , "���f��"	))	{ return E_FAIL; }

	

	return S_OK;
}


void Systems::Uninit(void)
{
	// for���t����f�N���Ŋe�}�l�[�W��������������Ă���
	// �㏈�� �d�v�Ȃ̂��Ō�ɁH
	//for (int i = (int)SYSTEM_NUM::MAX - 1; i >= 0; --i)
	//{
	//	if (_manager[i])
	//	{
	//		_manager[i]->Uninit();
	//		DeleteThis(_manager[i]);
	//	}
	//}

	for (int i = 0;i < (int)SYSTEM_NUM::MAX;i++)
	{
		if (_manager[i])
		{
			_manager[i]->Uninit();
			DeleteThis(_manager[i]);
		}
	}
}


void Systems::Update(void)
{
	for (int i = 0; i < (int)SYSTEM_NUM::MAX; ++i)
	{
		if (_manager[i])
		{
			_manager[i]->Update();
		}
	}
}


void Systems::Draw(void)
{
	// �N���A
	_window->GetGraphics()->ClearRenderer();


	for (int i = 0; i < (int)SYSTEM_NUM::MAX; ++i)
	{
		if (i == (int)SYSTEM_NUM::DEBUG) { continue; }
		if (!_manager[i]) { continue; }
		_manager[i]->Draw();
	}

	_manager[(int)SYSTEM_NUM::DEBUG]->Draw();
}


template<class T>
bool Systems::Create(int i, string error)
{
	_manager[i] = new T(this);
	string error_ = error + "�̏������Ɏ��s���܂���";

	if (FAILED(_manager[i]->Init()))
	{ 
		MessageBox(_window->GetHWND(), error_.c_str(), "�G���[", MB_OK);
		return false; 
	}
	return true;
}