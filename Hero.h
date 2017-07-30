#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer);
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		void Hero::TryToShoot(PlayerState& playerState);

	};
}

