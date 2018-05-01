#pragma once
#include "TextComp.h"

namespace dae {
	class FpsComp :public TextComp
	{
	public:

		explicit FpsComp(std::shared_ptr<Font> font, SDL_Color textColor = SDL_Color{ 255,255,255 });

		void Update(float deltaTime) override;
		unsigned int updateTresshold=10;
	private:
		//Hide parent functions
		void SetOffset(const float x, const float y) { (void)x, y; };
		void SetText(const std::string& text) { (void)text; };

		unsigned int m_Counter = 0;
		float m_totalTime = 0.f;
	};
}
