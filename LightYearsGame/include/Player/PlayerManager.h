#pragma once

#include <Core/Core.h>

namespace ly
{
	class Player;

	class PlayerManager
	{
	public:
		static PlayerManager& Get();

		Player& CreateNewPlayer();
		Player* GetPlayer(int index = 0);
		const Player* GetPlayer(int index = 0) const;

	protected:
		PlayerManager() = default;

	private:
		Vector<Player> m_Players;

	private:
		static Scope<PlayerManager> s_Instance;
	};
}