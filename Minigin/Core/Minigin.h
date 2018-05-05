#pragma once
#include "../Scenes/SceneManager.h"
#include "InputManager.h"
#include "../ObjComp/BaseObject.h"

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		
	private:
		//mutable SceneManager m_scenemanager;
		//mutable dae::InputManager m_input;
	};
}