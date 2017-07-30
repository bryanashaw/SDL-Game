#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Enemy : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer, GhostData* pGhostData);
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		GhostData* m_pEnemyData;

		//virtual void Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation = Vector2d());
	};
}