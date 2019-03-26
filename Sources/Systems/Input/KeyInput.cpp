#include "KeyInput.h"
#include "../Systems.h"

KeyInput::KeyInput(Input* input)
	: _input		(input)
	, _input8		(nullptr)
	, _devKeyboard	(nullptr)
{

}

HRESULT KeyInput::Init()
{
	Windows* window_ = _input->GetSystems()->GetWindow();

	HRESULT hr;

	// 入力処理の初期化
	if (_input8 == nullptr)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(window_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_input8, NULL);
		if (FAILED(hr))
		{
			MessageBox(window_->GetHWND(), "DirectInputオブジェクト生成失敗", "エラー", MB_OK);
			return E_FAIL;
		}
	}

	// デバイスの作成
	hr = _input8->CreateDevice(GUID_SysKeyboard, &_devKeyboard, NULL);
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "キーボードがありません", "エラー", MB_OK);
		return E_FAIL;
	}

	// データフォーマットを設定
	hr = _devKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "キーボードのデータフォーマットを設定できませんでした", "エラー", MB_OK);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = _devKeyboard->SetCooperativeLevel(window_->GetHWND(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "キーボードの協調モードを設定できませんでした", "エラー", MB_OK);
		return E_FAIL;
	}


	// キーボードへのアクセス権を獲得(入力制御開始)
	_devKeyboard->Acquire();

	ZeroMemory(_state, sizeof(INPUT_BUTTON) * KEY_MAX);

	return S_OK;
}

void KeyInput::Update()
{
	byte newKey[KEY_MAX];

	// デバイスからデータを取得
	if (SUCCEEDED(_devKeyboard->GetDeviceState(sizeof(newKey), newKey)))
	{
		for (int keyCnt = 0; keyCnt < KEY_MAX; keyCnt++)
		{
			// キートリガー・リリース情報を生成
			_state[keyCnt].trigger = (_state[keyCnt].press ^ newKey[keyCnt]) & newKey[keyCnt];
			//											(過去^現在) & 現在
			//									     1 =  0    1       1
			//										 0 =  1    1       1
			//										 0 =  1    0       0
			_state[keyCnt].release = (_state[keyCnt].press ^ newKey[keyCnt]) & _state[keyCnt].press;
			//										(過去^現在) & 過去
			//										 1 =  1    0       1
			//										 0 =  0    1       0

			// キーリピート情報を生成
			if (newKey[keyCnt])
			{
				if (_state[keyCnt].repeatCnt < Input::REPEAT_RANGE)
				{
					_state[keyCnt].repeatCnt++;
					if (_state[keyCnt].repeatCnt == 1)
					{
						_state[keyCnt].repeat = newKey[keyCnt];
					}
					else
					{
						_state[keyCnt].repeat = 0;
					}
				}
				else
				{
					_state[keyCnt].repeatCnt = 0;
				}
			}
			else
			{
				_state[keyCnt].repeatCnt = 0;
				_state[keyCnt].repeat = 0;
			}

			// キープレス情報を保存
			_state[keyCnt].press = newKey[keyCnt];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		_devKeyboard->Acquire();
	}
}

KeyInput::~KeyInput()
{
	if (_devKeyboard != nullptr)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		_devKeyboard->Unacquire();

		_devKeyboard->Release();
		_devKeyboard = nullptr;
	}

	ReleaseThis(_input8);
}

// キーボードのプレス状態を取得
bool KeyInput::Press(int key)
{
	return (_state[key].press & 0x80) ? true : false;
}

// キーボードのトリガー状態を取得
bool KeyInput::Trig(int key)
{
	return (_state[key].trigger & 0x80) ? true : false;
}


// キーボードのリリ－ス状態を取得
bool KeyInput::Release(int key)
{
	return (_state[key].release & 0x80) ? true : false;
}

// キーボードのリピート状態を取得
bool KeyInput::Repeat(int key)
{
	return (_state[key].repeat & 0x80) ? true : false;
}
