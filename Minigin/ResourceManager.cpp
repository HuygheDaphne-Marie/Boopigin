#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void boop::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<boop::Texture2D> boop::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath + file;

	const auto findItr = m_Textures.find(fullPath);
	if (findItr != m_Textures.end())
	{
		return findItr->second;
	}
	
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_Textures[fullPath] = std::make_shared<Texture2D>(texture);
	
	return m_Textures[fullPath];
}

std::shared_ptr<boop::Font> boop::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const std::string fontName = GetFontName(file, size);

	const auto findItr = m_Fonts.find(fontName);
	if (findItr != m_Fonts.end())
	{
		return findItr->second;
	}

	const std::shared_ptr<Font> font = std::make_shared<Font>(m_DataPath + file, size);
	m_Fonts[fontName] = font;
	
	return font;
}
//std::shared_ptr<boop::Font> boop::ResourceManager::LoadFont(const std::string& file, unsigned size) const
//{
//	const std::string fontName = GetFontName(file, size);
//
//	const auto findItr = std::find(m_Fonts.begin(), m_Fonts.end(), fontName);
//	if (findItr != m_Fonts.end())
//	{
//		return findItr->second;
//	}
//
//	return nullptr; // Todo: is this smart? 
//}

std::string boop::ResourceManager::GetFontName(const std::string& file, unsigned size) const
{
	return file + "_" + std::to_string(size);
}
