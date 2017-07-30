#include "Enemy.h"

using namespace DungeonGame;

void Enemy::Initialize(SDL_Renderer* pRenderer, GhostData* pEnemyData)
{
	m_pEnemyData = pEnemyData;
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Images/Enemy01.bmp"));
	m_Size = Vector2d(96.0f, 96.0f);


}

void Enemy::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{

	m_Position = m_pEnemyData->Position - m_Size * 0.5f;
	m_bVisible = m_pEnemyData->bAlive;

	Vector2d enemyToPlayer = playerState.m_CurrentPosition - m_pEnemyData->Position;
	float distance = enemyToPlayer.GetLength();

	if (m_pEnemyData->bAlive && playerState.EnemyColliderWithPlayer(m_pEnemyData))
	{

		m_pEnemyData->bAlive = false;

		playerState.m_hp--;


		//playerState.m_Inventory.push_back(m_pEnemyData->Type);

	}

	if (distance < 180.0f)
	{
		const float MOVEMENT_SPEED = 80.0f * deltaSeconds;
		enemyToPlayer.Normalize();
		m_pEnemyData->Position = m_pEnemyData->Position + enemyToPlayer *MOVEMENT_SPEED;


	}
}

	/*if (m_pEnemyData->bAlive && playerState.ItemColliderWithPlayer(m_pEnemyData))
	{

		m_pEnemyData->bAlive = false;

		playerState.m_Inventory.push_back(m_pEnemyData->Type);

	}
}*/

/*void Enemy::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	Vector2d enemyToPlayer = m_pGhostData->Position - playerState.m_CurrentPosition;
	float distance = enemyToPlayer.GetLength();

	if (distance < 180.0f)
	{
		const float MOVEMENT_SPEED = 80.0f * deltaSeconds;
		enemyToPlayer.Normalize();
		m_pGhostData->Position = m_pGhostData->Position + enemyToPlayer *MOVEMENT_SPEED;
	}
} */

/*void Enemy::Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation)
{
	Sprite::Render(pRenderer, worldState, playerState, baseTransformation);
	
	if (m_pTexture && m_bVisible)
	{
		SDL_Rect destRect = { 
			(int)(m_Position.X + baseTransformation.X) + 12.0f,
			(int)(m_Position.Y + baseTransformation.Y) + 12.0f,
			(int)m_Size.X * 0.25f,
			(int)m_Size.Y * 0.25f };
		SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &destRect);
	}
}*/