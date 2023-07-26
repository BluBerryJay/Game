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
			PlayerDead,
			GameOver
		};
	public:
		// Inherited via Game
		virtual bool Initiliaze() override;
		virtual void ShutDown() override;
		virtual void Update(float dt) override;
		virtual void Draw(Renderer& rend) override;
		void SetState(eState state) { m_state = state; };
	private:
		eState m_state = eState::Title;
		float m_spawnTimer = 0;
		float m_spawnTime = 3.0f;
		std::shared_ptr<kiko::Font> m_font;
		std::shared_ptr<kiko::Text> m_scoreText;
		std::shared_ptr<kiko::Text> m_titleText;



	};
}