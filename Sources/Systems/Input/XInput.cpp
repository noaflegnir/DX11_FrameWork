#include "XInput.h"
#include "Controller.h"
#include "KeyInput.h"

XInput::XInput(Input* input)
	: Gui (input->GetSystems(), "XInput")
{
}


XInput::~XInput()
{
}

void XInput::Update(INPUT_STATE& state)
{
	XINPUT_STATE state_;
	ZeroMemory(&state_, sizeof(XINPUT_STATE));

	if (XInputGetState(0, &state_) == ERROR_SUCCESS)
	{// Ú‘±Žž

		INPUT_STATE newState;
		ZeroMemory(&newState, sizeof(INPUT_STATE));

		_enable = true;

		Button(newState.button, state_);
		ButtonPress(newState.button, state.button);

		Axis(newState.axis, state_, state.axis);
		ButtonPress(newState.axis.bit, state.axis.bit);
	}
	else
	{// ”ñÚ‘±Žž
		_enable = false;
	}
}

void XInput::AxisPress(WORD & axisPress, const SHORT & newAxis, SHORT & axis, WORD bit, bool inverted)
{
	if (inverted)
	{
		bit *= 2;
	}
	if (newAxis > Hf(Input::RANGE))
	{
		axisPress |= bit;
	}
	else if (newAxis < -Hf(Input::RANGE))
	{
		if (inverted)
		{
			bit /= 4;
		}
		axisPress |= bit * 2;
	}
	axis = newAxis;
}


void XInput::ButtonPress(INPUT_BUTTON& newState, INPUT_BUTTON& button)
{

	button.trigger = (button.press ^ newState.press) & newState.press;
	button.release = (button.press ^ newState.press) & button.press;

	this->RepeatCheck(newState.press, button, Input::REPEAT_RANGE);

	button.press = newState.press;
}


void XInput::RepeatCheck(WORD & newStatePress, INPUT_BUTTON & button, int range)
{
	if (newStatePress)
	{
		if (button.repeatCnt < range)
		{
			button.repeatCnt++;
			if (button.repeatCnt == 1)
			{
				button.repeat = newStatePress;
			}
			else
			{
				button.repeat = 0;
			}
		}
		else
		{
			button.repeatCnt = 0;
		}
	}
	else
	{
		button.repeatCnt = 0;
		button.repeat = 0;
	}
}


void XInput::Button(INPUT_BUTTON& newState, XINPUT_STATE& state)
{
	WORD temp = state.Gamepad.wButtons;
	if (temp & XINPUT_GAMEPAD_A) { newState.press |= Input::GAMEPAD_CROSS;    }
	if (temp & XINPUT_GAMEPAD_B) { newState.press |= Input::GAMEPAD_CIRCLE;   }
	if (temp & XINPUT_GAMEPAD_X) { newState.press |= Input::GAMEPAD_SQUARE;	  }
	if (temp & XINPUT_GAMEPAD_Y) { newState.press |= Input::GAMEPAD_TRIANGLE; }

	if (temp & XINPUT_GAMEPAD_DPAD_UP)	  { newState.press |= Input::GAMEPAD_UP;   }
	if (temp & XINPUT_GAMEPAD_DPAD_DOWN)  { newState.press |= Input::GAMEPAD_DOWN; }
	if (temp & XINPUT_GAMEPAD_DPAD_LEFT)  { newState.press |= Input::GAMEPAD_LEFT; }
	if (temp & XINPUT_GAMEPAD_DPAD_RIGHT) { newState.press |= Input::GAMEPAD_RIGHT;}

	if (temp & XINPUT_GAMEPAD_LEFT_SHOULDER)  { newState.press |= Input::GAMEPAD_L1; }
	if (temp & XINPUT_GAMEPAD_RIGHT_SHOULDER) { newState.press |= Input::GAMEPAD_R1; }
	if (temp & XINPUT_GAMEPAD_LEFT_THUMB)	  { newState.press |= Input::GAMEPAD_L3; }
	if (temp & XINPUT_GAMEPAD_RIGHT_THUMB)	  { newState.press |= Input::GAMEPAD_R3; }

	if (temp & XINPUT_GAMEPAD_START) { newState.press |= Input::GAMEPAD_START;  }
	if (temp & XINPUT_GAMEPAD_BACK)  { newState.press |= Input::GAMEPAD_SELECT; }
}

void XInput::Axis(INPUT_AXIS & newState, XINPUT_STATE & state, INPUT_AXIS & axState)
{
	newState.stickLX = (SHORT)(state.Gamepad.sThumbLX * rangeThumb);
	newState.stickLY = (SHORT)(state.Gamepad.sThumbLY * rangeThumb);
	newState.stickRX = (SHORT)(state.Gamepad.sThumbRX * rangeThumb);
	newState.stickRY = (SHORT)(state.Gamepad.sThumbRY * rangeThumb);

	AxisPress(newState.bit.press, newState.stickLX, axState.stickLX, Input::JUDGE_LX_PLUS, false);
	AxisPress(newState.bit.press, -newState.stickLY, axState.stickLY, Input::JUDGE_LY_PLUS, true);
	AxisPress(newState.bit.press, newState.stickRX, axState.stickRX, Input::JUDGE_RX_PLUS, false);
	AxisPress(newState.bit.press, -newState.stickRY, axState.stickRY, Input::JUDGE_RY_PLUS, false);

	newState.triggerL = (SHORT)(state.Gamepad.bLeftTrigger  * rangeTrig);
	newState.triggerR = (SHORT)(state.Gamepad.bRightTrigger * rangeTrig);

	AxisPress(newState.bit.press, newState.triggerL, axState.triggerL, Input::JUDGE_L2, false);
	AxisPress(newState.bit.press, newState.triggerR, axState.triggerR, Input::JUDGE_R2, false);
}


void XInput::GuiUpdate(void)
{
}

