#include "Widget/GameplayHUD.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerSpaceship.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: m_FrameRateText{"Frame Rate:"},
		m_PlayerHealthBar{},
		m_PlayerLifeIcon {"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
		m_PlayerLifeCountText{""},
		m_PlayerScoreIcon {"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
		m_PlayerScoreText{""},
		m_NormalHealthBarColor{128, 255, 128},
		m_CriticalHealthBarColor{255, 0, 0},
		m_CriticalThreshold{0.3},
		m_WidgetSpacing{10.f}
	{
		m_FrameRateText.SetTextSize(30);
		m_PlayerLifeCountText.SetTextSize(20);
		m_PlayerScoreText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& window)
	{
		m_FrameRateText.NativeDraw(window);
		m_PlayerHealthBar.NativeDraw(window);
		m_PlayerLifeIcon.NativeDraw(window);
		m_PlayerLifeCountText.NativeDraw(window);
		m_PlayerScoreIcon.NativeDraw(window);
		m_PlayerScoreText.NativeDraw(window);
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

		sf::Vector2f nextWidgetPosition = m_PlayerHealthBar.GetWidgetPosition();
		nextWidgetPosition += {m_PlayerHealthBar.GetBounds().width + m_WidgetSpacing, 0.f};
		m_PlayerLifeIcon.SetWidgetPosition(nextWidgetPosition);

		nextWidgetPosition += {m_PlayerLifeIcon.GetBounds().width + m_WidgetSpacing, 0.f};
		m_PlayerLifeCountText.SetWidgetPosition(nextWidgetPosition);
		
		nextWidgetPosition += {m_PlayerLifeCountText.GetBounds().width + m_WidgetSpacing * 4, -2.f};
		m_PlayerScoreIcon.SetWidgetPosition(nextWidgetPosition);
		
		nextWidgetPosition += {m_PlayerScoreIcon.GetBounds().width + m_WidgetSpacing, 0.f};
		m_PlayerScoreText.SetWidgetPosition(nextWidgetPosition);

		RefreshHealthBar();
		SetupPlayerStatus();
	}

	void GameplayHUD::OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth)
	{
		m_PlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth <= m_CriticalThreshold)
			m_PlayerHealthBar.SetForegroundColor(m_CriticalHealthBarColor);
		else
			m_PlayerHealthBar.SetForegroundColor(m_NormalHealthBarColor);
	}

	void GameplayHUD::OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::OnPlayerLifeCountUpdated(int count)
	{
		m_PlayerLifeCountText.SetString(std::to_string(count));
	}

	void GameplayHUD::OnPlayerScoreChanged(int score)
	{
		m_PlayerScoreText.SetString(std::to_string(score));
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
			OnPlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::SetupPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lifeCount = player->GetLifeCount();
			m_PlayerLifeCountText.SetString(std::to_string(lifeCount));
			player->OnLifeChanged.Bind(GetWeakRef(), &GameplayHUD::OnPlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			m_PlayerScoreText.SetString(std::to_string(playerScore));
			player->OnScoreChanged.Bind(GetWeakRef(), &GameplayHUD::OnPlayerScoreChanged);
		}
	}
}