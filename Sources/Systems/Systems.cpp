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

	//!!! ここでクリエイトするのはサウンドやインプットなどのもの + シーンマネージャ
	if (!Create<Debug>			((int)SYSTEM_NUM::DEBUG	  ,	"デバッグ"	))	{ return E_FAIL; }
	if (!Create<TextureManager>	((int)SYSTEM_NUM::TEXTURE ,	"テクスチャ"))	{ return E_FAIL; }
	if (!Create<Input>			((int)SYSTEM_NUM::INPUT	  , "入力"		))	{ return E_FAIL; }

	/* pmxモデルローダーは制作段階 */
	if (!Create<ModelLoader>	((int)SYSTEM_NUM::MODEL	  , "モデル"	))	{ return E_FAIL; }

	

	return S_OK;
}


void Systems::Uninit(void)
{
	// forを逆からデクリで各マネージャ内部を解放していく
	// 後処理 重要なのを最後に？
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
	// クリア
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
	string error_ = error + "の初期化に失敗しました";

	if (FAILED(_manager[i]->Init()))
	{ 
		MessageBox(_window->GetHWND(), error_.c_str(), "エラー", MB_OK);
		return false; 
	}
	return true;
}