#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Bullet : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer, BulletData* pBulletData);
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		BulletData* m_pBulletData;
	};
}