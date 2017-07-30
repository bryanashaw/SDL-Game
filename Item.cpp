#include "Item.h"

using namespace DungeonGame;

void Item::Initialize(SDL_Renderer* pRenderer, ItemData* pItemData)
{
	m_pItemData = pItemData;

	std::string textureFilename = "images/Book.bmp";

	switch (m_pItemData->Type)
	{
	case Item_Book:
		textureFilename = "images/Book.bmp";
		break;
	case Item_Rune:
		textureFilename = "images/Rune.bmp";
			break;
	}

	Sprite::Initialize(Sprite::LoadTexture(pRenderer, textureFilename.c_str()));
	m_Size = Vector2d(TILE_SIZE_H, TILE_SIZE_W);
}

void Item::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{

	m_Position = m_pItemData -> Position - m_Size * 0.5f;
	m_bVisible = m_pItemData->bAlive;

	Vector2d enemyToPlayer = m_pItemData->Position - playerState.m_CurrentPosition;
	float distance = enemyToPlayer.GetLength();


	if (distance < 180.0f)
	{
		const float MOVEMENT_SPEED = 80.0f * deltaSeconds;
		enemyToPlayer.Normalize();
		m_pItemData->Position = m_pItemData->Position + enemyToPlayer *MOVEMENT_SPEED;
	}

	if (m_pItemData->bAlive && playerState.ItemColliderWithPlayer(m_pItemData))
	{
	
		m_pItemData->bAlive = false;

		playerState.m_Inventory.push_back(m_pItemData->Type);
		
		playerState.m_bHasFinishedGame = true;

	}
}