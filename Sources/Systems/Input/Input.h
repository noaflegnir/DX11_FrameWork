/**
* @file		Input.h
* @brief	入力処理
* @author	小山智也
* @date		2019/03/26
*/
#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <XInput.h>

#include "../../Define/Define.h"
#include "../BaseManager.h"

#pragma comment(lib, "xinput.lib")

struct INPUT_BUTTON
{
	WORD press;
	WORD trigger;
	WORD release;
	WORD repeat;
	WORD repeatCnt;
};

struct INPUT_AXIS
{
	SHORT stickLX;
	SHORT stickLY;
	SHORT stickRX;
	SHORT stickRY;

	SHORT triggerL;
	SHORT triggerR;

	INPUT_BUTTON bit;
};

struct INPUT_STATE
{
	INPUT_BUTTON button;
	INPUT_AXIS   axis;
};



class KeyInput;
class XInput;
class Input : public Interface {

public:
	friend class Systems;

	// アナログスティックの傾きの最大値
	static constexpr int RANGE = 100;		// 0～いくつまでか
	static constexpr int REPEAT_RANGE = 30;

	static constexpr int GAMEPAD_SQUARE = 0x0001;
	static constexpr int GAMEPAD_CROSS = 0x0002;
	static constexpr int GAMEPAD_CIRCLE = 0x0004;
	static constexpr int GAMEPAD_TRIANGLE = 0x0008;

	static constexpr int GAMEPAD_L1 = 0x0010;
	static constexpr int GAMEPAD_R1 = 0x0020;
	static constexpr int GAMEPAD_L3 = 0x0040;
	static constexpr int GAMEPAD_R3 = 0x0080;

	static constexpr int GAMEPAD_START = 0x0100;
	static constexpr int GAMEPAD_SELECT = 0x0200;
	static constexpr int GAMEPAD_HOME = 0x0400;
	static constexpr int GAMEPAD_SHARE = 0x0800;

	static constexpr int GAMEPAD_UP = 0x1000;
	static constexpr int GAMEPAD_RIGHT = 0x2000;
	static constexpr int GAMEPAD_DOWN = 0x4000;
	static constexpr int GAMEPAD_LEFT = 0x8000;

	static constexpr int AXIS_LX = 0xa000;
	static constexpr int AXIS_LY = 0xb000;
	static constexpr int AXIS_RX = 0xc000;
	static constexpr int AXIS_RY = 0xd000;

	static constexpr int GAMEPAD_L2 = 0xe000;
	static constexpr int GAMEPAD_R2 = 0xf000;

	static constexpr int JUDGE_LX_PLUS = 0x0001;
	static constexpr int JUDGE_LX_MINUS = 0x0002;
	static constexpr int JUDGE_LY_PLUS = 0x0004;
	static constexpr int JUDGE_LY_MINUS = 0x0008;
	static constexpr int JUDGE_RX_PLUS = 0x0010;
	static constexpr int JUDGE_RX_MINUS = 0x0020;
	static constexpr int JUDGE_RY_PLUS = 0x0040;
	static constexpr int JUDGE_RY_MINUS = 0x0080;
	static constexpr int JUDGE_L2 = 0x0100;
	static constexpr int JUDGE_R2 = 0x0200;


	Input(Systems* systems);
	~Input() override;
	HRESULT Init() override;

	KeyInput* GetKeyboard() { return _keyboard; }
	XInput* GetCtrl() { return _ctrl; }


private:
	void Update(void) override;

	INPUT_STATE _state;

	KeyInput*   _keyboard;
	XInput*		_ctrl;

};