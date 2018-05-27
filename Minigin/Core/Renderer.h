#pragma once
#include "Singleton.h"

#include <SDL.h>

//struct SDL_Window;
//struct SDL_Renderer;

//struct SDL_Point;
//enum SDL_RendererFlip;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Initialize(SDL_Window* window);
		void Render();
		void Destroy();

		//void RenderTexture(const Texture2D& texture, float x, float y) const;


		void RenderTextureNoOffset(const Texture2D& texture, float x, float y, double angle = 0, SDL_Point* center = 0, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;

		void RenderTexture(const Texture2D& texture, float x, float y, double angle = 0, SDL_Point* center=0, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;

		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, double angle = 0, SDL_Point* center = 0, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

		static int WINDOW_WIDTH;
		static int WINDOW_HEIGHT;
	};
}

