/**
* @file		KeyInput.h
* @brief	�L�[�{�[�h�ɂ����͏���
* @author	���R�q��
* @date		2019/03/26
*/
#pragma once

#include "Input.h"

class KeyInput {

	friend Input;

public:
	static constexpr int REPEAT_RANGE = 60;		// ���s�[�g�Ԋu
	static constexpr int KEY_MAX = 256;	// �L�[�̍ő吔
	~KeyInput();

	bool Press(int key);
	bool Trig(int key);
	bool Repeat(int key);
	bool Release(int key);


private:
	KeyInput(Input* input);
	HRESULT Init();
	void    Update();

	Input*               _input;
	LPDIRECTINPUT8       _input8;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 _devKeyboard;			// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

	INPUT_BUTTON         _state[KEY_MAX];
};