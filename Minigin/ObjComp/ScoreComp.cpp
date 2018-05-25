#include "MiniginPCH.h"
#include "ScoreComp.h"
#include <SDL_ttf.h>
#include "../Core/Renderer.h"
#include "../Core/Font.h"
#include "../GlobalGameMaster/GlobalMaster.h"
#include "string"

dae::ScoreComp::ScoreComp(const std::string& prefix, int playerID,std::shared_ptr<Font> font, SDL_Color textColor) :m_Prefix(prefix), m_PlayerId(playerID), TextComp("FPS: ", font, textColor)
{}

void dae::ScoreComp::Update(float deltaTime)
{
	(void)deltaTime;
	auto& gm = GlobalMaster::GetInstance();
	(void)gm;
	int currentScore = GlobalMaster::GetInstance().m_PlayerScore[m_PlayerId];
	if(m_lastScore<0||m_lastScore!=currentScore)
	{
		m_NeedsUpdate=true;
		m_Text = m_Prefix + std::to_string(currentScore);
	}

	


	if (m_NeedsUpdate) {
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) {
			std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);

		m_NeedsUpdate = false;
	}
}
