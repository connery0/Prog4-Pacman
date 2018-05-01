#include "MiniginPCH.h"
#include "Font.h"

dae::Font::Font(const std::string& fullPath, unsigned size)
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(mFont);
}

TTF_Font* dae::Font::GetFont() const
{
	return mFont;
}
