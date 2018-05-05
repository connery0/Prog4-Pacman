#include "MiniginPCH.h"
#include "TextureComp.h"
#include "../Core/Renderer.h"
#include "../Core/ResourceManager.h"
#include "../ObjComp/BaseObject.h"


dae::TextureComp::TextureComp(const std::string& filename)
{
	m_Texture=dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComp::Render() const
{
	auto pos = m_pParentObject->TGetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y,m_pParentObject->TGetRotation());
}
