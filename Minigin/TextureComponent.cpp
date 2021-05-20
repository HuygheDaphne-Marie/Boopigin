#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "TransformComponent.h"

boop::TextureComponent::TextureComponent(const std::string& texturePath)
	: TextureComponent(texturePath, 0, 0)
{
	m_AreDimensionsSet = false;
}

boop::TextureComponent::TextureComponent(const std::string& texturePath, float width, float height)
	: m_pTexture(ResourceManager::GetInstance().LoadTexture(texturePath))
	, m_Width(width)
	, m_Height(height)
{
	m_AreDimensionsSet = true;
}

void boop::TextureComponent::Render() const
{
	const auto pTransform = m_pOwner->GetComponentOfType<TransformComponent>();
	const auto pos = pTransform->GetPosition();

	if (m_AreDimensionsSet)
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void boop::TextureComponent::SetTexture(const std::string& texturePath)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void boop::TextureComponent::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
	m_AreDimensionsSet = true;
}
