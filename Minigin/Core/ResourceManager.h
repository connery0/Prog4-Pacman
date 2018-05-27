#pragma once
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Initialize(std::string&& data);

		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	};

}
