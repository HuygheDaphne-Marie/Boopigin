#include "MiniginPCH.h"
#include "TextComponent.h"

#include <SDL_ttf.h>

#include "Renderer.h"
#include "TransformComponent.h"

boop::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
	: m_Text(text),
	m_Color(color),
	m_NeedsUpdate(true),
	m_pFont(font),
	m_pTextTexture(nullptr)
{
}

boop::TextComponent::~TextComponent()
{
	delete m_pTextTexture;
}

void boop::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		delete m_pTextTexture; // Todo: this is shit, get a manager & printer (Honestly not sure if it's worth the effort anymore)
		m_pTextTexture = new Texture2D(texture);
		m_NeedsUpdate = false;
	}
}

void boop::TextComponent::Render() const
{
	if (m_pTextTexture != nullptr)
	{		
		TransformComponent* pTransform = m_pOwner->GetComponentOfType<TransformComponent>();
		const auto pos = pTransform->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void boop::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
