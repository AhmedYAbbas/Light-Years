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
		void CleanCycle();

	protected:
		AssetManager();

	private:
		static Scope<AssetManager> s_Instance;
		Dict<std::string, Ref<sf::Texture>> m_LoadedTextureMap;
	};
}