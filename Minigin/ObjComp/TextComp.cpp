#include "MiniginPCH.h"
#include "TextComp.h"
#include "TransformComponent.h"
#include "../Core/Renderer.h"
#include "SDL_ttf.h"
#include "../Core/Font.h"


dae::TextComp::TextComp(const std::string& text, std::shared_ptr<Font> font, SDL_Color textColor)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), m_Color(textColor), m_OffsetX(0.f), m_OffsetY(0.f)
{
}

void dae::TextComp::Update(float deltaTime)
{
	(void)deltaTime;

	if (m_NeedsUpdate)
	{
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

void dae::TextComp::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pParentObject->T()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_OffsetX, pos.y + m_OffsetY);
	}
}

void dae::TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComp::SetOffset(const float x, const float y)
{
	m_OffsetX = x;
	m_OffsetY = y;
}

void dae::TextComp::SetColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}
