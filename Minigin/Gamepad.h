#pragma once

#include <windows.h>
#include <Xinput.h>


namespace dae {
	class Gamepad
	{

	private:
		static int controllerCount;

		XINPUT_STATE previousState{};
		XINPUT_STATE currentState{};
		int controllerIndex{};

		WORD buttonsPressed{};
		WORD buttonsReleased{};
	public:
		Gamepad() { controllerIndex = controllerCount; controllerCount++; }
		bool ProcessInput();

		bool ButtonIsDownThisFrame(unsigned int button) const;
		bool ButtonIsUpThisFrame(unsigned int button) const;
		bool ButtonIsPressed(unsigned int button) const;

		float GetLeftStickX();
		float GetLeftStickY();
		float GetRightStickX();
		float GetRightStickY();

		float GetLeftTrigger();
		float GetRightTrigger();
	};

}

