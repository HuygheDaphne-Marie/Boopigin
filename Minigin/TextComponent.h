#pragma once
#include <SDL_pixels.h>

#include "Component.h"
#include "Font.h"
#include "Texture2D.h"

namespace boop
{	
	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text, Font* font, const SDL_Color& color = {255, 255, 255});
		~TextComponent();
		
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		//inline static const std::string name = "TextComponent";

	private:
		std::string m_Text;
		SDL_Color m_Color;
		
		bool m_NeedsUpdate;
		Font* m_pFont;
		Texture2D* m_pTextTexture;
	};
}

