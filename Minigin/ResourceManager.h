#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace boop
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		[[nodiscard]] std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		[[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;

		[[nodiscard]] std::string GetFontName(const std::string& file, unsigned int size) const;

		std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts{};
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures{};
	};
}
