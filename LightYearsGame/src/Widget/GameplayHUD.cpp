#include "Widget/GameplayHUD.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: m_FrameRateText{"Frame Rate:"}
	{
		m_FrameRateText.SetTextSize(30);
	}

	void GameplayHUD::Draw(sf::RenderWindow& window)
	{
		m_FrameRateText.NativeDraw(window);
		m_PlayerHealthBar.NativeDraw(window);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		HUD::Tick(deltaTime);
		int frameRate = (int)(1 / deltaTime) + 1;
		const std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		m_FrameRateText.SetString(frameRateStr);
	}

	void GameplayHUD::Init(const sf::RenderWindow& window)
	{
		auto windowSize = window.getSize();
		m_PlayerHealthBar.SetWidgetPosition({20.f, windowSize.y - 50.f});
		RefreshHealthBar();
	}

	void GameplayHUD::OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
	{
		m_PlayerHealthBar.UpdateValue(currentHealth, maxHealth);
	}

	void GameplayHUD::OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		WeakRef<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
		if (player && !playerSpaceship.expired())
		{
			playerSpaceship.lock()->OnActorDestroyed.Bind(GetWeakRef(), &GameplayHUD::OnPlayerSpaceshipDestroyed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComponent();
			healthComp.OnHealthChanged.Bind(GetWeakRef(), &GameplayHUD::OnPlayerHealthUpdated);
			m_PlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}
}