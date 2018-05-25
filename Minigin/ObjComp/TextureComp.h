#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace  dae{
	class TextureComp:public BaseComponent
	{
	public:
		TextureComp(const std::string& filename,bool centerTexture=true);
		void ChangeTexture(const std::string& filename);

		void Render() const override;

	protected:
		std::shared_ptr<Texture2D> m_Texture;
		bool m_centerTexture;
	};

}