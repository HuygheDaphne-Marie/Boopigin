#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace boop
{
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::string& texturePath);
		~TextureComponent();

		void Render() const override;
	
	private:
		Texture2D* m_pTexture;
	};
}

