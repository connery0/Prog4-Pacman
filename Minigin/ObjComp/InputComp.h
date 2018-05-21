#pragma once
#include "BaseComponent.h"
#include "vector"
#include "../Core/InputManager.h"


class InputComp:public BaseComponent
{
public:
	~InputComp()
	{
		auto& input = dae::InputManager::GetInstance();
		for (auto inputList : m_InputList)
		{
			input.RemoveInput(&inputList.second.isPressed);
		}
		m_InputList.clear();
	};

	bool isDown(int key)
	{
		return (m_InputList[key].isPressed && *m_InputList[key].isPressed);
	}
	
	//KeyBoard
	void addInput(int key, int keyCode)
	{
		if(m_InputList.count(key)>0)
		{
			m_InputList[key] = inputStruct{ keyCode };
			dae::InputManager::GetInstance().AddInput(m_InputList[key].keyboardKeyCode,&m_InputList[key].isPressed);
		}else
		{
			rebindInput(key,keyCode);
		}

	}
	void rebindInput(int key, int newKeyCode)
	{
		dae::InputManager::GetInstance().RemoveInput(&m_InputList[key].isPressed);

		m_InputList[key] = inputStruct{newKeyCode};
		dae::InputManager::GetInstance().AddInput(m_InputList[key].keyboardKeyCode, &m_InputList[key].isPressed);
	}

	//Controller
	void addInput(int key, dae::ControllerButton keyCode)
	{
		if (m_InputList.count(key)>0)
		{
			m_InputList[key] = inputStruct{ keyCode };
			dae::InputManager::GetInstance().AddInput(m_InputList[key].controllerKey, &m_InputList[key].isPressed);
		}
		else
		{
			rebindInput(key, keyCode);
		}

	}
	void rebindInput(int key, dae::ControllerButton newKeyCode)
	{
		dae::InputManager::GetInstance().RemoveInput(&m_InputList[key].isPressed);

		m_InputList[key] = inputStruct{ newKeyCode };
		dae::InputManager::GetInstance().AddInput(m_InputList[key].controllerKey, &m_InputList[key].isPressed);
	}

protected:

	dae::InputManager m_input;

	struct inputStruct
	{
		bool usesKeyboard=true;//false = controller
		int keyboardKeyCode;
		dae::ControllerButton controllerKey;
		bool* isPressed = nullptr; //managed by inputManager
		inputStruct(){};
		inputStruct(int keyCode): usesKeyboard(true),keyboardKeyCode(keyCode){};
		inputStruct(dae::ControllerButton button): usesKeyboard(false), controllerKey(button) {};
	};

	std::map<int, inputStruct> m_InputList;

};

