#include <iostream>
#include <SDL.h>

#include <functional>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


#include "InputManager.h"



bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.key.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for (auto& gamepad : gamepads) {
		gamepad->ProcessInput();
	}


	for (auto& [binding,command] : bindings) {
		
	}

	return true;
}

bool dae::InputManager::ProcessKeyboardInput()
{

	return false;
}

bool dae::InputManager::ProcessGamepadInput()
{
	return false;
}

bool dae::InputManager::ButtonIsDownThisFrame(unsigned int button , unsigned int gamepadId = 0) const
{
	return gamepads[gamepadId]->ButtonIsDownThisFrame(button);
}

bool dae::InputManager::ButtonIsUpThisFrame(unsigned int button, unsigned int gamepadId = 0) const
{
	return gamepads[gamepadId]->ButtonIsUpThisFrame(button);
}

bool dae::InputManager::ButtonIsPressed(unsigned int button, unsigned int gamepadId = 0) const
{
	return gamepads[gamepadId]->ButtonIsPressed(button);
}

float dae::InputManager::GetLeftStickX(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetLeftStickX();
}

float dae::InputManager::GetLeftStickY(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetLeftStickY();
}

float dae::InputManager::GetRightStickX(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetRightStickX();
}

float dae::InputManager::GetRightStickY(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetRightStickY();
}

float dae::InputManager::GetLeftTrigger(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetLeftTrigger();
}

float dae::InputManager::GetRightTrigger(unsigned int gamepadId = 0)
{
	return gamepads[gamepadId]->GetRightTrigger();
}

bool dae::InputManager::BindCommand(std::unique_ptr<Command> command, InputBinding binding)
{
	auto result = bindings.insert({ binding ,std::move(command)});
	if (binding.inputType == dae::InputBinding::Type::Keyboard) {
		switch (binding.keyboard)
		{
		case dae::InputBinding::Keyboard::Key:
			switch (binding.inputEvent)
			{
			case dae::InputBinding::Event::Triggered:
				std::bind(&dae::InputManager::ButtonIsDownThisFrame,this,std::placeholders::_1);
				break;
			case dae::InputBinding::Event::Pressed:
				std::bind(&dae::InputManager::ButtonIsPressed,this,std::placeholders::_1);
				break;
			case dae::InputBinding::Event::Released:
				std::bind(&dae::InputManager::ButtonIsUpThisFrame,this,std::placeholders::_1);
				break;
			}
			break;
		default:
			break;
		}
	}

	if (binding.inputType == dae::InputBinding::Type::Controller)
	{
		switch (binding.controller)
		{
		case dae::InputBinding::Controller::Button:
			switch (binding.inputEvent)
			{
			case dae::InputBinding::Event::Triggered:
			{
				std::function<bool(unsigned int)> func = std::bind(&dae::Gamepad::ButtonIsDownThisFrame, gamepads[binding.inputsystemId],binding.inputId);
				break;
			}
			case dae::InputBinding::Event::Pressed:
				std::bind(&dae::Gamepad::ButtonIsPressed, gamepads[binding.inputsystemId], binding.inputId);
				break;
			case dae::InputBinding::Event::Released:
				std::bind(&dae::Gamepad::ButtonIsUpThisFrame, gamepads[binding.inputsystemId], binding.inputId);
				break;
			}
			break;
		case dae::InputBinding::Controller::LeftStick:
			break;
		case dae::InputBinding::Controller::RightStick:
			break;
		case dae::InputBinding::Controller::LeftTrigger:
			break;
		case dae::InputBinding::Controller::RightTrigger:
			break;

		default:
			break;
		}
	}

	if (binding.inputType == dae::InputBinding::Type::Mouse)
	{
	}
	return result.second;
}

bool dae::InputManager::UnbindCommand(InputBinding inputBinding)
{
	auto result = bindings.erase(inputBinding);
	return result;
}