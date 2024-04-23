#pragma once

#include <Framework/World.h>

namespace ly
{
	class MainMenuHUD;

	class MainMenuLevel : public World
	{
	public:
		MainMenuLevel();

	private:
		virtual void BeginPlay();

		void StartGame();
		void QuitGame();

	private:
		WeakRef<MainMenuHUD> m_MainMenuHUD;
	};
}