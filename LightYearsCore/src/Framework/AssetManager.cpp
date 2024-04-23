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
		return LoadAsset(filepath, m_LoadedTextureMap);
	}

	Ref<sf::Font> AssetManager::LoadFont(const std::string& filepath)
	{
		return LoadAsset(filepath, m_LoadedFontMap);
	}

	void AssetManager::SetAssetRootDirectory(const std::string& directory)
	{
		m_RootDirectory = directory;
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueRef(m_LoadedTextureMap);
		CleanUniqueRef(m_LoadedFontMap);
	}

}