/**
* @file		KeyInput.h
* @brief	キーボードによる入力処理
* @author	小山智也
* @date		2019/03/26
*/
#pragma once

#include "Input.h"

class KeyInput {

	friend Input;

public:
	static constexpr int REPEAT_RANGE = 60;		// リピート間隔
	static constexpr int KEY_MAX = 256;	// キーの最大数
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
	LPDIRECTINPUT8       _input8;				// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 _devKeyboard;			// 入力デバイス(キーボード)へのポインタ

	INPUT_BUTTON         _state[KEY_MAX];
};