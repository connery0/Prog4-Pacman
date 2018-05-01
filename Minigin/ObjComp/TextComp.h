#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "../Core/ResourceManager.h"
#include <SDL.h>


namespace dae {
	class TextComp:public BaseComponent
	{
	public:
		explicit TextComp(const std::string& text, std::shared_ptr<Font> font, SDL_Color textColor = SDL_Color{255,255,255});

		void Update(float deltaTime) override;
		void Render() const override;


		void SetText(const std::string& text);
		void SetOffset(const float x, const float y);
		void SetColor(SDL_Color color);
	
protected:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_Texture;
	SDL_Color m_Color;
	float m_OffsetX, m_OffsetY;
	};
}
