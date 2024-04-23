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
		Ref<sf::Font> LoadFont(const std::string& filepath = "SpaceShooterRedux/Bonus/kenvector_future.ttf");
		void SetAssetRootDirectory(const std::string& directory);
		void CleanCycle();

	protected:
		AssetManager();

	private:
		template<typename T>
		Ref<T> LoadAsset(const std::string filepath, Dict<std::string, Ref<T>>& container)
		{
			if (container.find(filepath) != container.end())
				return container[filepath];

			Ref<T> asset = CreateRef<T>();
			if (asset->loadFromFile(m_RootDirectory + filepath))
			{
				container[filepath] = asset;
				return asset;
			}

			return nullptr;
		}

		template<typename T>
		void CleanUniqueRef(Dict<std::string, Ref<T>>& container)
		{
			for (auto it = container.begin(); it != container.end();)
			{
				if (it->second.use_count() == 1)
				{
					LOG("Cleaning: %s", it->first.c_str());
					it = container.erase(it);
				}
				else
					it++;
			}
		}

	private:
		static Scope<AssetManager> s_Instance;
		Dict<std::string, Ref<sf::Texture>> m_LoadedTextureMap;
		Dict<std::string, Ref<sf::Font>> m_LoadedFontMap;
		std::string m_RootDirectory;
	};
}