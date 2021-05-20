#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>

namespace boop
{
	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(const std::string& texturePath);
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;

		void SetTexture(const std::string& texturePath);
	
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}

