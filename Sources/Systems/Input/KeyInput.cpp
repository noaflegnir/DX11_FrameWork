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

	// ���͏����̏�����
	if (_input8 == nullptr)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(window_->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_input8, NULL);
		if (FAILED(hr))
		{
			MessageBox(window_->GetHWND(), "DirectInput�I�u�W�F�N�g�������s", "�G���[", MB_OK);
			return E_FAIL;
		}
	}

	// �f�o�C�X�̍쐬
	hr = _input8->CreateDevice(GUID_SysKeyboard, &_devKeyboard, NULL);
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "�L�[�{�[�h������܂���", "�G���[", MB_OK);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = _devKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł���", "�G���[", MB_OK);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = _devKeyboard->SetCooperativeLevel(window_->GetHWND(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(window_->GetHWND(), "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł���", "�G���[", MB_OK);
		return E_FAIL;
	}


	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	_devKeyboard->Acquire();

	ZeroMemory(_state, sizeof(INPUT_BUTTON) * KEY_MAX);

	return S_OK;
}

void KeyInput::Update()
{
	byte newKey[KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(_devKeyboard->GetDeviceState(sizeof(newKey), newKey)))
	{
		for (int keyCnt = 0; keyCnt < KEY_MAX; keyCnt++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			_state[keyCnt].trigger = (_state[keyCnt].press ^ newKey[keyCnt]) & newKey[keyCnt];
			//											(�ߋ�^����) & ����
			//									     1 =  0    1       1
			//										 0 =  1    1       1
			//										 0 =  1    0       0
			_state[keyCnt].release = (_state[keyCnt].press ^ newKey[keyCnt]) & _state[keyCnt].press;
			//										(�ߋ�^����) & �ߋ�
			//										 1 =  1    0       1
			//										 0 =  0    1       0

			// �L�[���s�[�g���𐶐�
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

			// �L�[�v���X����ۑ�
			_state[keyCnt].press = newKey[keyCnt];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		_devKeyboard->Acquire();
	}
}

KeyInput::~KeyInput()
{
	if (_devKeyboard != nullptr)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		_devKeyboard->Unacquire();

		_devKeyboard->Release();
		_devKeyboard = nullptr;
	}

	ReleaseThis(_input8);
}

// �L�[�{�[�h�̃v���X��Ԃ��擾
bool KeyInput::Press(int key)
{
	return (_state[key].press & 0x80) ? true : false;
}

// �L�[�{�[�h�̃g���K�[��Ԃ��擾
bool KeyInput::Trig(int key)
{
	return (_state[key].trigger & 0x80) ? true : false;
}


// �L�[�{�[�h�̃����|�X��Ԃ��擾
bool KeyInput::Release(int key)
{
	return (_state[key].release & 0x80) ? true : false;
}

// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
bool KeyInput::Repeat(int key)
{
	return (_state[key].repeat & 0x80) ? true : false;
}
