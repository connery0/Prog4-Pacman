#include "MiniginPCH.h"
#include "TextureComp.h"
#include "../Core/Renderer.h"
#include "../Core/ResourceManager.h"
#include "BaseObject.h"
#include "Transform.h"
#include <SDL.h>


dae::TextureComp::TextureComp(const std::string& filename)
{
	m_Texture=dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComp::Render() const
{
	auto pos = m_pParentObject->T()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y,m_pParentObject->T()->getRotationDeg());
}

void dae::TextureComp::addParent(BaseObject* parentObj)
{
	BaseComponent::addParent(parentObj);
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	parentObj->T()->SetSize(static_cast<float>(dst.w),static_cast<float>(dst.h));	
}
