#include "MiniginPCH.h"
#include "TextureColliderComp.h"
#include "../Core/Renderer.h"
#include "../Core/ResourceManager.h"
#include "Transform.h"
#include <SDL.h>


dae::TextureColliderComp::TextureColliderComp(const std::string& filename, bool centerTexture ):TextureComp(filename,centerTexture)
{
}


void dae::TextureColliderComp::addParent(BaseObject* parentObj)
{
	BaseComponent::addParent(parentObj);
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	parentObj->T()->SetSize(static_cast<float>(dst.w),static_cast<float>(dst.h));	
}
