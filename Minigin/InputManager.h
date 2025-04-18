#pragma once
#include "Singleton.h"

#include <unordered_map>
#include <memory>

#include "Gamepad.h"
#include "Command.h"


namespace dae
{
	struct InputBinding {
		enum class Type {
			None,
			Keyboard,
			Controller,
			Mouse,
		};
		enum class Event {
			None,
			Triggered,
			Pressed,
			Released,
		};

		enum class Controller {
			None,
			LeftTrigger,
			RightTrigger,
			LeftStick,
			RightStick,
			Button,
		};
		enum class Mouse {
			None,
			LeftClick,
			MiddleClick,
			RightClick,
			MiddleScroll,
		};
		enum class Keyboard {
			None,
			Key,
		};

		union {
			Controller controller;
			Keyboard keyboard;
			Mouse mouse;
		};
		Event inputEvent;
		Type inputType;
		unsigned int inputsystemId; // controllers keyboards
		unsigned int inputId; // g h key or x y buttons
	};

	struct KeyHasher {
		size_t operator()(const dae::InputBinding& binding)const {
			return std::hash<int>()(static_cast<int>(binding.inputType)) ^ std::hash<unsigned int>()(binding.inputId);
		}
	};
	struct KeyEquals {
		bool operator()(const dae::InputBinding& b1, const dae::InputBinding& b2) const{
			return b1.inputId == b2.inputId && b1.inputType == b2.inputType;
		}
	};

	class InputManager final : public Singleton<InputManager>
	{
	private:
		std::vector<std::unique_ptr<Gamepad>> gamepads;
		std::unordered_map<InputBinding, std::unique_ptr<Command>, KeyHasher,KeyEquals> bindings;

		std::vector<std::pair<std::function<bool(unsigned int)>, std::unique_ptr<Command>>> predecateBindings;
		std::vector<std::pair<std::function<float()>, std::unique_ptr<Command>>> functionBindings;
	public:

		bool ProcessInput();

		bool BindCommand(std::unique_ptr<class Command> command, InputBinding inputBinding);
		bool UnbindCommand(InputBinding inputBinding);

		bool ButtonIsDownThisFrame(unsigned int button, unsigned int gamepadId = 0) const;

		bool ButtonIsUpThisFrame(unsigned int button, unsigned int gamepadId = 0) const;

		bool ButtonIsPressed(unsigned int button, unsigned int gamepadId = 0) const;

		float GetLeftStickX(unsigned int gamepadId = 0);

		float GetLeftStickY(unsigned int gamepadId = 0);

		float GetRightStickX(unsigned int gamepadId = 0);

		float GetRightStickY(unsigned int gamepadId = 0);

		float GetLeftTrigger(unsigned int gamepadId = 0);

		float GetRightTrigger(unsigned int gamepadId = 0);

	private:
		bool ProcessKeyboardInput();
		bool ProcessGamepadInput();
	};

}