#include "MiniginPCH.h"
#include "FpsComp.h"
#include <SDL_ttf.h>
#include "../Core/Renderer.h"
#include "../Core/Font.h"

dae::FpsComp::FpsComp(std::shared_ptr<Font> font, SDL_Color textColor) :TextComp("FPS: ", font, textColor)
{}

void dae::FpsComp::Update(float deltaTime)
{
	const unsigned int tresshold = 20;


	(void)deltaTime;
	m_Text = "FPS: ";
	if(deltaTime>0)
	{
		++m_Counter;
		m_totalTime+=(1 / deltaTime);
		if(m_Counter>= updateTresshold)
		{
			m_Text += std::to_string(int(m_totalTime / updateTresshold));
			
			m_Counter = 0;
			m_totalTime = 0;
			m_NeedsUpdate = true;
		}
	}else
	{
		m_Text += "...";
		m_NeedsUpdate = true;
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
