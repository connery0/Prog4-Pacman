#pragma once
#include "TextureComp.h"

//Special instance of a texture that adjusts the parents hitbox to its size
namespace  dae{
	class TextureColliderComp:public TextureComp
	{
	public:
		TextureColliderComp(const std::string& filename);

		virtual void addParent(BaseObject* parentObj) override;
	};

}
