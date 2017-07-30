#include "Bullet.h"

using namespace DungeonGame;

void Bullet::Initialize(SDL_Renderer* pRenderer, BulletData* pBulletData)
{
	m_pBulletData = pBulletData;

	std::string textureFilename = "images/Feather.bmp";

	Sprite::Initialize(Sprite::LoadTexture(pRenderer, textureFilename.c_str()));
	m_Size = Vector2d(TILE_SIZE_H/2, TILE_SIZE_W/2);
}

void Bullet::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{

	m_Position = m_pBulletData->Position - m_Size * 0.5f;
	m_bVisible = m_pBulletData->bAlive;

	Vector2d enemyToPlayer = m_pBulletData->Position - playerState.m_CurrentPosition;
	float distance = enemyToPlayer.GetLength();

	/*if (distance < 180.0f)
	{
		const float MOVEMENT_SPEED = 80.0f * deltaSeconds;
		enemyToPlayer.Normalize();
		m_pBulletData->Position = m_pBulletData->Position + enemyToPlayer *MOVEMENT_SPEED;
	}

	if (m_pBulletData->bAlive && playerState.BulletColliderWithPlayer(m_pBulletData))
	{

		m_pBulletData->bAlive = false;

		playerState.m_Inventory.push_back(m_pBulletData->Type);

	} */

	if (m_pBulletData->bAlive)
	{
		m_pBulletData->secondsAlive += deltaSeconds;
		if (m_pBulletData->secondsAlive >= 1.0f)
		{
			m_pBulletData->bAlive = false;
		}

		const float BULLET_SPEED = 600.0f * deltaSeconds;
		Vector2d bulletDirection = Vector2d(0.0f, 1.0f);
		m_pBulletData->Position = m_pBulletData->Position + m_pBulletData->direction * BULLET_SPEED;

		if (worldState.BulletCollidesWithItem(m_pBulletData))
		{
			m_pBulletData->bAlive = false;
		}
	}


}