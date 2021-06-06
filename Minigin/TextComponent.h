#pragma once
#include <SDL_pixels.h>

#include "Component.h"
#include "Font.h"
#include "Texture2D.h"
#include <memory>

namespace boop
{	
	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = {255, 255, 255});
		~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
		
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);

		[[nodiscard]] int GetWidth() const;
		[[nodiscard]] int GetHeight() const;

	private:
		std::string m_Text;
		SDL_Color m_Color;
		
		bool m_NeedsUpdate;
		std::shared_ptr<Font> m_pFont;
		Texture2D* m_pTextTexture;

		void UpdateTexture();
	};
}

