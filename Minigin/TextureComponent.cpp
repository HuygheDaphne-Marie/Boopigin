#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "TransformComponent.h"

boop::TextureComponent::TextureComponent(const std::string& texturePath)
	: m_pTexture(nullptr)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

boop::TextureComponent::~TextureComponent()
{
	delete m_pTexture; // Todo: this should be manager's responsibility, not the component's
}

void boop::TextureComponent::Render() const
{
	const auto pTransform = m_pOwner->GetComponentOfType<TransformComponent>();
	const auto pos = pTransform->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
