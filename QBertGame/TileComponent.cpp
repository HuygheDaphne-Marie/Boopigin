#include "TileComponent.h"
#include <TextureComponent.h>

using namespace boop;

TileComponent::TileComponent(const std::string& walkedTexturePath)
	: m_WalkedTexturePath(walkedTexturePath)
{
}

void TileComponent::OnWalked() const
{
	// Todo: might need more work done here
	m_pOwner->GetComponentOfType<TextureComponent>()->SetTexture(m_WalkedTexturePath);
}
