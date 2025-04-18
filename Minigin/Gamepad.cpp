#include "Gamepad.h"

int dae::Gamepad::controllerCount = 0;

bool dae::Gamepad::ProcessInput()
{
	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &currentState);

	auto buttonsChanged = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	buttonsPressed = buttonsChanged & currentState.Gamepad.wButtons;
	buttonsReleased = buttonsChanged & ~currentState.Gamepad.wButtons;

	return true;
}

bool dae::Gamepad::ButtonIsDownThisFrame(unsigned int button) const
{
	return buttonsPressed & button;
}

bool dae::Gamepad::ButtonIsUpThisFrame(unsigned int button) const
{
	return buttonsReleased & button;
}

bool dae::Gamepad::ButtonIsPressed(unsigned int button) const
{
	return currentState.Gamepad.wButtons & button;;
}

float dae::Gamepad::GetLeftStickX()
{
	return currentState.Gamepad.sThumbLX;
}

float dae::Gamepad::GetLeftStickY()
{
	return currentState.Gamepad.sThumbLY;
}

float dae::Gamepad::GetRightStickX()
{
	return currentState.Gamepad.sThumbRX;
}

float dae::Gamepad::GetRightStickY()
{
	return currentState.Gamepad.sThumbRY;
}

float dae::Gamepad::GetLeftTrigger()
{
	return currentState.Gamepad.bLeftTrigger;
}

float dae::Gamepad::GetRightTrigger()
{
	return currentState.Gamepad.bRightTrigger;
}
