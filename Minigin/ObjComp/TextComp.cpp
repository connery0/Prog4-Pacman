#include "MiniginPCH.h"
#include "TextComp.h"
#include "../Core/Renderer.h"
#include "SDL_ttf.h"
#include "../Core/Font.h"
#include "../ObjComp/BaseObject.h"
#include "../ObjComp/Transform.h"

using namespace dae;

TextComp::TextComp(const std::string& text, std::shared_ptr<Font> font, SDL_Color textColor): 
	m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), m_Color(textColor), m_OffsetX(0.f), m_OffsetY(0.f)
{
}

void TextComp::Update(float deltaTime)
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

void TextComp::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pParentObject->T()->GetPosition();
		Renderer::GetInstance().RenderTextureNoOffset(*m_Texture, pos.first + m_OffsetX, pos.second + m_OffsetY,m_pParentObject->T()->getRotationDeg());
	}
}

void TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComp::SetOffset(const float x, const float y)
{
	m_OffsetX = x;
	m_OffsetY = y;
}

void TextComp::SetColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}
