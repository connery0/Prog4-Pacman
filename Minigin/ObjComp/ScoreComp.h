#pragma once
#include "TextComp.h"
#include "memory"

namespace dae {
	class ScoreComp :public TextComp
	{
	public:
		explicit ScoreComp(const std::string& prefix,int playerID, std::shared_ptr<Font> font, SDL_Color textColor = SDL_Color{ 255,255,255 });

		void Update(float deltaTime) override;
	private:
		//Hide parent functions
		void SetText(const std::string& text) { (void)text; };
		const int m_PlayerId;
		int m_lastScore=-1;
		std::string m_Prefix;
	};
}
