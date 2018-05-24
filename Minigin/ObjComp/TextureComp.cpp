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
