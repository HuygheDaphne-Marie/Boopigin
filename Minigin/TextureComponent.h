#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace boop
{
	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(const std::string& texturePath);
		~TextureComponent();
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
	
	private:
		Texture2D* m_pTexture;
	};
}

