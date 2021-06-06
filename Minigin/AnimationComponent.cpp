#include "MiniginPCH.h"
#include "AnimationComponent.h"

#include <SDL_render.h>

#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

boop::AnimationComponent::AnimationComponent(const std::string& texturePath, int frameWidth, int frameHeight,
                                             int displayWidth, int displayHeight)
	: m_pTexture(ResourceManager::GetInstance().LoadTexture(texturePath))
	, m_pTransform(nullptr)
	, m_SrcRect({0,0,frameWidth,frameHeight})
	, m_DstWidth(displayWidth)
	, m_DstHeight(displayHeight)
	, m_CurrentFrame(0)
{
	int totalWidth;
	int totalHeight;
	
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &totalWidth, &totalHeight);

	m_Rows = totalHeight / frameHeight;
	m_Cols = totalWidth / frameWidth;

	if (m_DstWidth == 0)
	{
		m_DstWidth = frameWidth;
	}
	if (m_DstHeight == 0)
	{
		m_DstHeight = frameHeight;
	}
}

void boop::AnimationComponent::Startup()
{
	m_pTransform = m_pOwner->GetComponentOfType<TransformComponent>();
	SetFrame(m_CurrentFrame);
}

void boop::AnimationComponent::Render() const
{
	glm::vec3 pos{};
	if (m_pTransform != nullptr)
	{
		pos = m_pTransform->GetPosition();
	}

	Renderer::GetInstance().RenderTexture(*m_pTexture, m_SrcRect, pos.x, pos.y, 
		static_cast<float>(m_DstWidth), static_cast<float>(m_DstHeight));
}

unsigned int boop::AnimationComponent::GetFrameCount() const
{
	return m_Rows * m_Cols;
}

unsigned int boop::AnimationComponent::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

void boop::AnimationComponent::SetFrame(unsigned int frame)
{
	const int frameRow = frame / m_Cols;
	const int frameCol = frame % m_Cols;

	if ((frameRow + 1) > m_Rows || (frameCol + 1) > m_Cols)
		return; // This frame does not exist

	m_SrcRect.x = m_SrcRect.w * frameCol;
	m_SrcRect.y = m_SrcRect.h * frameRow;
	m_CurrentFrame = frame;
}

int boop::AnimationComponent::GetWidth() const
{
	return m_DstWidth;
}

int boop::AnimationComponent::GetHeight() const
{
	return m_DstHeight;
}
