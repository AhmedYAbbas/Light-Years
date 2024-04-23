#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"

namespace ly
{
	class AssetManager
	{
	public:
		static AssetManager& Get();
		Ref<sf::Texture> LoadTexture(const std::string& filepath);
		Ref<sf::Font> LoadFont(const std::string& filepath);
		void SetAssetRootDirectory(const std::string& directory);
		void CleanCycle();

	protected:
		AssetManager();

	private:
		static Scope<AssetManager> s_Instance;
		Dict<std::string, Ref<sf::Texture>> m_LoadedTextureMap;
		Dict<std::string, Ref<sf::Font>> m_LoadedFontMap;
		std::string m_RootDirectory;
	};
}