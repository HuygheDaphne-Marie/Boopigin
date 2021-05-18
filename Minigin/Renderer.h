#pragma once
#include <SDL_video.h>

#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace boop
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
	private:
		static int GetOpenGLDriverIndex();
		
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
	};
}

