#include "Framework/AssetManager.h"

namespace ly
{
	Scope<AssetManager> AssetManager::s_Instance = nullptr;

	AssetManager::AssetManager()
		: m_RootDirectory{}
	{
	}

	AssetManager& AssetManager::Get()
	{
		if (!s_Instance)
			s_Instance = Scope<AssetManager>(new AssetManager);

		return *s_Instance;
	}

	Ref<sf::Texture> AssetManager::LoadTexture(const std::string& filepath)
	{
		if (m_LoadedTextureMap.find(filepath) != m_LoadedTextureMap.end())
			return m_LoadedTextureMap[filepath];

		Ref<sf::Texture> texture = CreateRef<sf::Texture>();
		if (texture->loadFromFile(m_RootDirectory + filepath))
		{
			m_LoadedTextureMap[filepath] = texture;
			return texture;
		}

		return nullptr;
	}

	Ref<sf::Font> AssetManager::LoadFont(const std::string& filepath)
	{
		if (m_LoadedFontMap.find(filepath) != m_LoadedFontMap.end())
			return m_LoadedFontMap[filepath];

		Ref<sf::Font> font = CreateRef<sf::Font>();
		if (font->loadFromFile(m_RootDirectory + filepath))
		{
			m_LoadedFontMap[filepath] = font;
			return font;
		}

		return nullptr;
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		m_RootDirectory = directory;
	}

	void AssetManager::CleanCycle()
	{
		for (auto it = m_LoadedTextureMap.begin(); it != m_LoadedTextureMap.end();)
		{
			if (it->second.use_count() == 1)
				it = m_LoadedTextureMap.erase(it);
			else
				it++;
		}

		for (auto it = m_LoadedFontMap.begin(); it != m_LoadedFontMap.end();)
		{
			if (it->second.use_count() == 1)
				it = m_LoadedFontMap.erase(it);
			else
				it++;
		}
	}

}