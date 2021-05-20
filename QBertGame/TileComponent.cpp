#include "TileComponent.h"
#include <TextureComponent.h>

using namespace boop;

TileComponent::TileComponent(const std::string& walkedTexturePath)
	: m_WalkedTexturePath(walkedTexturePath)
{
}

void TileComponent::OnWalked() const
{
	m_pOwner->GetComponentOfType<TextureComponent>()->SetTexture(m_WalkedTexturePath);
}
