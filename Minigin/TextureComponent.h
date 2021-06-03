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
		explicit TextureComponent(const std::string& texturePath, float width, float height);
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;

		void SetTexture(const std::string& texturePath);
		void SetDimensions(float width, float height);
		[[nodiscard]] int GetHeight() const;
		[[nodiscard]] int GetWidth() const;
	
	private:
		std::shared_ptr<Texture2D> m_pTexture{};

		bool m_AreDimensionsSet = false;
		float m_Width{};
		float m_Height{};
	};
}

