#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
namespace kiko
{
	class SpaceGame : public Game

	{
	public:
		enum class eState
		{
			Title,
			StartGame,
			StartLevel,
			Game,
			PlayerDeadStart,
			PlayerDead,
			GameOverStart,
			GameOver

		};
	public:
		// Inherited via Game
		virtual bool Initiliaze() override;
		virtual void ShutDown() override;
		virtual void Update(float dt) override;
		virtual void Draw(Renderer& rend) override;
		void SetState(eState state) { m_state = state; };
		virtual void EmitTest();
	private:
		eState m_state = eState::Title;
		float m_enemySpawnTimer = 0;
		float m_enemyFastSpawnTimer = 0;
		float m_heartSpawnTimer = 0;

		float m_spawnTime = 3.0f;

		float m_stateTimer = 0;

		float m_gameTimer = 0;
		std::shared_ptr<kiko::Font> m_UIfont;
		std::shared_ptr<kiko::Font> m_titleFont;

		std::shared_ptr<kiko::Text> m_scoreText;
		std::shared_ptr<kiko::Text> m_titleText;
		std::shared_ptr<kiko::Text> m_livesText;
		std::shared_ptr<kiko::Text> m_gameOverText;
		std::shared_ptr<kiko::Text> m_funnyText;



	};
}