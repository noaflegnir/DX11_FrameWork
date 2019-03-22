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
	if (!Create<Debug>((int)SYSTEM_NUM::DEBUG, "Debug")) { return E_FAIL; }




	return S_OK;
}


void Systems::Uninit(void)
{
	// for���t����f�N���Ŋe�}�l�[�W��������������Ă���
	// �㏈�� �d�v�Ȃ̂��Ō�ɁH
	for (int i = (int)SYSTEM_NUM::MAX - 1; i >= 0; --i)
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
	// �e�̕`��
	//const auto& objRenderer = (ObjectRendererManager*)manager_[(int)SystemsNum::OBJECTRENDERER];
	//objRenderer->DrawShadow();

	_window->GetGraphics()->ClearRenderer();

	// �Q�[���̕`��
	//const auto& scene = (SceneManager*)_manager[(int)SYSTEM_NUM::SCENE];
	//scene->Draw();

	// �V���ƃt�B�[���h���ɕ`��
	//objRenderer->FastDraw();

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