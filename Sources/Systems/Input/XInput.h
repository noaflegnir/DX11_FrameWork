/**
* @file		XInput.h
* @brief	XInputコントローラによる入力処理
* @author	小山智也
* @date		2019/03/26
*/
#pragma once

#include "Input.h"
#include "../Debug/Gui.h"

class XInput : public Gui {

	friend Input;

public:

	static constexpr float THUMB_MAX = 32768.0f;
	static constexpr float TRIGGER_MAX = 255.0f;
	static constexpr float NOT_ENABLE_THUMB = (THUMB_MAX / (float)Input::RANGE / 2.f);
	static constexpr float NOT_ENABLE_TRIGGER = (TRIGGER_MAX / (float)Input::RANGE / 2.f);

	static constexpr int AXIS_LX = 0xa000;
	static constexpr int AXIS_LY = 0xb000;
	static constexpr int AXIS_RX = 0xc000;
	static constexpr int AXIS_RY = 0xd000;

	static constexpr int TRIGGER_L = 0xe000;
	static constexpr int TRIGGER_R = 0xf000;


	~XInput();
	void GuiUpdate(void) override;

private:
	XInput(Input* input);
	void Update(INPUT_STATE& state);

	void Button(INPUT_BUTTON& newState, XINPUT_STATE& state);
	void Axis(INPUT_AXIS& newState, XINPUT_STATE& state, INPUT_AXIS& axState);

	void AxisPress(WORD& axisPress, const SHORT& newAxis, SHORT& axis, WORD bit, bool inverted);
	void ButtonPress(INPUT_BUTTON& newState, INPUT_BUTTON& button);
	void RepeatCheck(WORD& newStatePress, INPUT_BUTTON& button, int range);




	static constexpr float rangeTrig = 1 / (TRIGGER_MAX / (float)Input::RANGE);
	static constexpr float rangeThumb = 1 / (THUMB_MAX / (float)Input::RANGE);

	bool _enable;

};