#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <memory>
#include <SDL_rect.h>

namespace boop
{
	class TransformComponent;

	class AnimationComponent final : public Component
	{
	public:
		explicit AnimationComponent(const std::string& texturePath, int frameWidth, int frameHeight, int displayWidth = 0, int displayHeight = 0);
		~AnimationComponent() override = default;
		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

		void Startup() override;
		void Render() const override;

		[[nodiscard]] unsigned int GetFrameCount() const;
		[[nodiscard]] unsigned int GetCurrentFrame() const;
		void SetFrame(unsigned int frame);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		TransformComponent* m_pTransform;

		SDL_Rect m_SrcRect;
		int m_DstWidth;
		int m_DstHeight;
		
		int m_Rows;
		int m_Cols;

		unsigned int m_CurrentFrame;
	};
}


