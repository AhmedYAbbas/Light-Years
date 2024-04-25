#include <Framework/Application.h>

#include "Widget/GameplayHUD.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/Player.h"
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
		m_WidgetSpacing{10.f},
		m_WinLoseText{""},
		m_FinalScoreText{""},
		m_RestartButton{"Restart"},
		m_QuitButton{"Quit"}
	{
		m_FrameRateText.SetTextSize(30);
		m_PlayerLifeCountText.SetTextSize(20);
		m_PlayerScoreText.SetTextSize(20);
		m_RestartButton.SetTextSize(20);
		m_QuitButton.SetTextSize(20);

		m_WinLoseText.SetVisibility(false);
		m_FinalScoreText.SetVisibility(false);
		m_RestartButton.SetVisibility(false);
		m_QuitButton.SetVisibility(false);
	}

	void GameplayHUD::Draw(sf::RenderWindow& window)
	{
		m_FrameRateText.NativeDraw(window);
		m_PlayerHealthBar.NativeDraw(window);
		m_PlayerLifeIcon.NativeDraw(window);
		m_PlayerLifeCountText.NativeDraw(window);
		m_PlayerScoreIcon.NativeDraw(window);
		m_PlayerScoreText.NativeDraw(window);

		m_WinLoseText.NativeDraw(window);
		m_FinalScoreText.NativeDraw(window);
		m_RestartButton.NativeDraw(window);
		m_QuitButton.NativeDraw(window);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		HUD::Tick(deltaTime);
		int frameRate = (int)(1 / deltaTime) + 1;
		const std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		m_FrameRateText.SetString(frameRateStr);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (m_RestartButton.HandleEvent(event))
			return true;
		
		if (m_QuitButton.HandleEvent(event))
			return true;

		return HUD::HandleEvent(event);
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

		m_WinLoseText.SetTextSize(40);
		m_WinLoseText.SetWidgetPosition({windowSize.x / 2.f - m_WinLoseText.GetBounds().width / 2.f, 100.f});

		m_FinalScoreText.SetTextSize(40);
		m_FinalScoreText.SetWidgetPosition({windowSize.x / 2.f - m_FinalScoreText.GetBounds().width / 2.f, 200.f});

		m_RestartButton.SetWidgetPosition({windowSize.x / 2.f - m_RestartButton.GetBounds().width / 2.f, windowSize.y / 2.f});
		m_QuitButton.SetWidgetPosition(m_RestartButton.GetWidgetPosition() + sf::Vector2f {0.f, 50.f});

		m_RestartButton.OnButtonClicked.Bind(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		m_QuitButton.OnButtonClicked.Bind(GetWeakRef(), &GameplayHUD::QuitButtonClicked);

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

	void GameplayHUD::RestartButtonClicked()
	{
		OnRestartButtonClicked.Broadcast();
	}

	void GameplayHUD::QuitButtonClicked()
	{
		OnQuitButtonClicked.Broadcast();
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
		m_WinLoseText.SetVisibility(true);
		m_FinalScoreText.SetVisibility(true);
		m_RestartButton.SetVisibility(true);
		m_QuitButton.SetVisibility(true);

		const unsigned int score = PlayerManager::Get().GetPlayer()->GetScore();
		m_FinalScoreText.SetString("Score: " + std::to_string(score));
		m_FinalScoreText.SetTextSize(40);

		const auto windowSize = Application::Get().GetWindowSize();

		if (playerWon)
			m_WinLoseText.SetString("You Won!");
		else
			m_WinLoseText.SetString("You Lost!");

		m_WinLoseText.SetWidgetPosition({windowSize.x / 2.f - m_WinLoseText.GetBounds().width / 2.f, 100.f});
		m_FinalScoreText.SetWidgetPosition({windowSize.x / 2.f - m_FinalScoreText.GetBounds().width / 2.f, 200.f});
	}
}