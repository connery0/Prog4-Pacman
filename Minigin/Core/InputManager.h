#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "string"
#include <map>
#include "vector"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		LeftTrigger,
		RightTrigger,
		Left,
		Right,
		Up,
		Down,
		Start
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		void Initialize();
		bool UpdateKeyboardStates();
		bool UpdateGamepadStates();
		void Update();
		bool ProcessInput();

		bool IsPressed(ControllerButton button);
		bool IsPressed(int keyboardCode);

		void AddInput(ControllerButton button, bool** valueToBind);
		void AddInput(int keyboardCode, bool** valueToBind);
		void RemoveInput(bool** BindingToRemove);

		void Destroy();
		
	private:
		void RemoveKeys();

		 XINPUT_STATE currentState;
		 BYTE *m_pKeyboardState;

		 std::vector<std::pair<int, bool**>> m_KeyboardInputActions;
		 std::vector<std::pair<ControllerButton, bool**>> m_ControllerInputActions;

		 std::vector<bool**> m_KeysToRemove;
		 bool m_Initialized;
		bool pressed = true;
		bool notPressed = false;
	};




}
