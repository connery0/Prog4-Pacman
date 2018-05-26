#include "MiniginPCH.h"
#include "InputManager.h"
#include <windows.h>
#include <SDL.h>
#include <algorithm>


void dae::InputManager::Initialize()
{
	if(m_Initialized) return;

	m_pKeyboardState = new BYTE[256];
	GetKeyboardState(m_pKeyboardState);
	m_Initialized = true;
}

bool dae::InputManager::UpdateKeyboardStates()
{
	BOOL keyboardResult=GetKeyboardState(m_pKeyboardState);
	return keyboardResult>0;
}

//TODO: implement if time left, check for multiple controllers
bool dae::InputManager::UpdateGamepadStates()
{
	return false;
}

void dae::InputManager::Update()
{
	if(!m_Initialized)
		Initialize();

	if(m_KeysToRemove.size()>0)
		RemoveKeys();

	UpdateKeyboardStates();
	UpdateGamepadStates();

	for (std::pair<int, bool**> keyBool : m_KeyboardInputActions)
	{
		if (keyBool.second){
			const bool keyIsPressed = IsPressed(keyBool.first);
			
			if(**keyBool.second != keyIsPressed)
			{
				if(keyIsPressed) *keyBool.second = &pressed;
				else *keyBool.second = &notPressed;
			}
		}
	}
	
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);
	for (std::pair<ControllerButton, bool**> keyBool : m_ControllerInputActions)
	{
		if (keyBool.second) {
			const bool keyIsPressed = IsPressed(keyBool.first);

			if (**keyBool.second != keyIsPressed)
			{
				if (keyIsPressed) *keyBool.second = &pressed;
				else *keyBool.second = &notPressed;
			}
		}
	}
}

bool dae::InputManager::IsPressed(ControllerButton button)
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::LeftTrigger:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case ControllerButton::RightTrigger:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::Left:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::Right:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::Up:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::Down:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::Start:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	default: return false;
	}
}

bool dae::InputManager::IsPressed(int keyboardCode)
{
	if(m_pKeyboardState&& keyboardCode >0x07 && keyboardCode<= 0xFE)
	{
		return (m_pKeyboardState[keyboardCode] & 0xF0) != 0;
	}
	return false;
}

void dae::InputManager::AddInput(ControllerButton button, bool** valueToBind)
{
	*valueToBind = &notPressed;
	m_ControllerInputActions.push_back(std::make_pair(button,valueToBind));
}

void dae::InputManager::AddInput(int keyboardCode, bool** valueToBind)
{
	*valueToBind = &notPressed;
	m_KeyboardInputActions.push_back(std::make_pair(keyboardCode, valueToBind));
}

void dae::InputManager::RemoveInput(bool** BindingToRemove)
{
		m_KeysToRemove.push_back(BindingToRemove);
}


void dae::InputManager::RemoveKeys()
{
	for (bool** keyToRemove : m_KeysToRemove)
	{
		m_KeyboardInputActions.erase(
			std::remove_if(m_KeyboardInputActions.begin(), m_KeyboardInputActions.end(),
				[&](const std::pair<int, bool**> keyBool)-> bool { return keyBool.second == keyToRemove; }),
			m_KeyboardInputActions.end()
		);
	}
	for (bool** keyToRemove : m_KeysToRemove)
	{
		m_ControllerInputActions.erase(
			std::remove_if(m_ControllerInputActions.begin(), m_ControllerInputActions.end(),
				[&](const std::pair<ControllerButton, bool**> keyBool)-> bool { return keyBool.second == keyToRemove; }),
			m_ControllerInputActions.end()
		);
	}

	//remove all connections to input manager
	for (bool** keyToRemove : m_KeysToRemove)
	{
		if(*keyToRemove)
			*keyToRemove=nullptr;
	}
	m_KeysToRemove.clear();
}

void dae::InputManager::Destroy()
{
	for (auto keyboardInputAction : m_KeyboardInputActions)
	{
		RemoveInput(keyboardInputAction.second);
	}

	for (auto controllerInput : m_ControllerInputActions)
	{
		RemoveInput(controllerInput.second);
	}

	RemoveKeys();

	m_KeyboardInputActions.clear();
	m_ControllerInputActions.clear();
	SafeDelete(m_pKeyboardState);
	m_Initialized = false;

}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}
