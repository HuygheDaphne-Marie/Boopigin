#include "TileComponent.h"
#include <TextureComponent.h>

using namespace boop;

TileComponent::TileComponent(const std::string& walkedTexturePath, int posX, int posY)
	: m_WalkedTexturePath(walkedTexturePath)
	, m_TileCol(posX)
	, m_TileRow(posY)
{
}

void TileComponent::OnWalked() const
{
	// Todo: might need more work done here
	m_pOwner->GetComponentOfType<TextureComponent>()->SetTexture(m_WalkedTexturePath);
}

int TileComponent::GetRow() const
{
	return m_TileRow;
}

int TileComponent::GetColumn() const
{
	return m_TileCol;
}
