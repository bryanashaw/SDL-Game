#include "Hero.h"

using namespace DungeonGame;

void Hero::Initialize(SDL_Renderer* pRenderer)
{
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Images/Hero01.bmp"));
	m_Size = Vector2d(32.0f, 62.0f);
}

void Hero::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	const float HERO_PIXELS_PER_SECOND = 300.0f *deltaSeconds;

	m_bVisible = playerState.m_bAlive;

	Vector2d newPosition = playerState.m_CurrentPosition + playerState.m_DesiredDirection * HERO_PIXELS_PER_SECOND;

	if (worldState.GetTileTypeAtPosition(newPosition) == 1)
	{
		playerState.m_CurrentPosition = newPosition;
	}

	m_Position = playerState.m_CurrentPosition - Vector2d(m_Size.X * 0.5f, m_Size.Y * 0.85f);



	

	//Shooting Logic
	{
		playerState.m_ShotCooldownSeconds -= deltaSeconds;
		if (playerState.m_ShotCooldownSeconds < 0.0f)
		{
			playerState.m_ShotCooldownSeconds = 0.0f;
		}
		if (playerState.m_bWantsToShoot)
		{
			TryToShoot(playerState);
		}
	}
	if (playerState.m_hp <= 0)
	{
		playerState.m_bAlive = false;
	}
	if (!playerState.m_bAlive)
	{
		playerState.Reset();
		worldState.Reset();
	}
}

void Hero::TryToShoot(PlayerState& playerState)
{
	if (playerState.m_ShotCooldownSeconds == 0.0f)
	{
		for (unsigned int i = 0; i < playerState.m_Bullets.size(); i++)
		{
			BulletData& currBullet = playerState.m_Bullets[i];
			if (!currBullet.bAlive)
			{
				playerState.m_ShotCooldownSeconds = 0.2f;

				currBullet.bAlive = true;
				currBullet.secondsAlive = 0.0f;
				currBullet.Position = playerState.m_CurrentPosition;

				currBullet.direction = Vector2d(0.0f, 1.0f);
				if (playerState.m_DesiredDirection != Vector2d(0.0f, 0.0f))
				{
					currBullet.direction = playerState.m_DesiredDirection;
				}

				break;
			}
		}
	}

}