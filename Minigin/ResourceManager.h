#pragma once
#include "Singleton.h"

namespace boop
{
	// Todo: make this actually manage, just about.. anything.
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		/*std::shared_ptr<Texture2D>*/ Texture2D* LoadTexture(const std::string& file) const;
		/*std::shared_ptr<Font>*/ Font* LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
