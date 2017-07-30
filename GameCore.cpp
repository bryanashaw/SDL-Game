#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "Bullet.h"

namespace DungeonGame
{
	std::vector<Sprite*> g_spriteList;
	Vector2d g_cameraPosition;
	const unsigned int BULLET_COUNT = 3;

	void GhostData::OnHitByBullet(BulletData* pBullet)
	{
		hp--;
		if (hp <= 0)
		{
			bAlive = false;
		}
	}

	/*Sprite backgroundSprite;
	Hero heroSprite;
	
	std::vector<Enemy> enemySprites;*/

	void PlayerState::Initialize()
	{
		//TODO: Initialize PlayerState stuff here

		for (unsigned int i = 0; i < BULLET_COUNT; i++)
		{
			BulletData bullet = {};
			bullet.bAlive = false;
			m_Bullets.push_back(bullet);

		}

		Reset();
	}

	void PlayerState::Reset()
	{
		//TODO: Reseet PlayerState stuff to default values
		m_CurrentPosition = Vector2d(2.0f * TILE_SIZE_W,  1.0f *TILE_SIZE_H);
		m_bAlive = true;

		m_hp = 1;

		m_bHasFinishedGame = false;
		m_bWantsToShoot = false;
		m_ShotCooldownSeconds = 0.0f;

		for (unsigned int i = 0; i < m_Bullets.size(); i++)
		{
			BulletData& bulletData = m_Bullets[i];
			bulletData.bAlive = false;

		}

	}
	bool PlayerState::ItemColliderWithPlayer(ItemData* pItem)
	{
		Vector2d itemToPlayer = pItem->Position - m_CurrentPosition;
		float distance = itemToPlayer.GetLength();
		return distance < 48.0f;
	}

	bool PlayerState::EnemyColliderWithPlayer(GhostData* pEnemy)
	{
		Vector2d itemToPlayer = pEnemy->Position - m_CurrentPosition;
		float distance = itemToPlayer.GetLength();
		return distance < 48.0f;
	}

	

	void WorldState::Initialize()
	{
		//TODO: Initialize WorldState stuff here
		m_TilesPerRow = 16;
		m_Tiles =
		{
			0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 2, 1, 1, 1, 1, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 0, 2, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0,
			0, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0,
			0, 2, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,


		};

		Reset();
	}

	void WorldState::Reset()
	{
		//TODO: Reseet WorldState stuff to default values

		m_Items.clear();
		m_Ghosts.clear();

/*		ItemData item01 = {};
		item01.bAlive = true;
		item01.Type = Item_Book;
		item01.Position = Vector2d(6.0f * TILE_SIZE_H, 5.0f * TILE_SIZE_W);
		m_Items.push_back(item01); */

		ItemData item02 = {};
		item02.bAlive = true;
		item02.Type = Item_Rune;
		item02.Position = Vector2d(6.0f * TILE_SIZE_H, 4.0f * TILE_SIZE_W);
		m_Items.push_back(item02);

		GhostData enemy01 = {};
		enemy01.bAlive = true;
		enemy01.hp = 5;
		enemy01.Position = Vector2d(4.0f * TILE_SIZE_H, 3.0f * TILE_SIZE_W);
		m_Ghosts.push_back(enemy01);

		GhostData enemy02 = {};
		enemy02.bAlive = true;
		enemy02.hp = 5;
		enemy02.Position = Vector2d(5.0f * TILE_SIZE_H, 3.0f * TILE_SIZE_W);
		m_Ghosts.push_back(enemy02);

		GhostData enemy03 = {};
		enemy03.bAlive = true;
		enemy03.hp = 5;
		enemy03.Position = Vector2d(6.0f * TILE_SIZE_H, 4.0f * TILE_SIZE_W);
		m_Ghosts.push_back(enemy03);
	}

	unsigned int WorldState::GetTileTypeAtPosition(const Vector2d& inPosition)
	{
		int col = (int)(inPosition.X / TILE_SIZE_W);
		int row = (int)(inPosition.Y / TILE_SIZE_H);

		int index = row * m_TilesPerRow + col;
		if (index >= 0 && index < m_Tiles.size())

		{
			return m_Tiles[index];
		}

		return 1;
	}

	bool WorldState::BulletCollidesWithItem(BulletData* pBullet)
	{
		bool bhasCollided = false;

		for (unsigned int i = 0; i < m_Ghosts.size(); i++)
		{

			GhostData& currGhost = m_Ghosts[i];

			if (currGhost.bAlive)
			{

				Vector2d bulletToItem = pBullet->Position - currGhost.Position;
				float distance = bulletToItem.GetLength();
				if (distance < 48.0f)
				{
					currGhost.OnHitByBullet(pBullet);
					bhasCollided = true;
					break;
				}

			}
		}
		return bhasCollided;
	}

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState)
	{
		worldState.Initialize();
		playerState.Initialize();
		g_cameraPosition = Vector2d();

		//Background
		Sprite* pBackgroundSprite = new Sprite;
		pBackgroundSprite->Initialize(Sprite::LoadTexture(pRenderer, "Images/HighresScreenshot00002.bmp"));
		pBackgroundSprite->m_Size = Vector2d(WINDOW_WIDTH *3, WINDOW_HEIGHT*3);
		pBackgroundSprite->m_Position = Vector2d(-WINDOW_WIDTH/2, -WINDOW_HEIGHT/2);
		g_spriteList.push_back(pBackgroundSprite);

		//Room
		RoomRenderer* pRoom = new RoomRenderer;
		pRoom->Initialize(pRenderer);
		g_spriteList.push_back(pRoom);

		/* //Background
		backgroundSprite.Initialize(Sprite::LoadTexture(pRenderer, "Images/HighresScreenshot00002.bmp"));
		backgroundSprite.m_Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT); */

		for (unsigned int i = 0; i < worldState.m_Items.size(); i++)
		{
			Item* pItem = new Item;
			pItem->Initialize(pRenderer, &worldState.m_Items[i]);
			g_spriteList.push_back(pItem);
		}

		for (unsigned int i = 0; i < playerState.m_Bullets.size(); i++)
		{
			Bullet* pBullet = new Bullet;
			pBullet->Initialize(pRenderer, &playerState.m_Bullets[i]);
			g_spriteList.push_back(pBullet);
		}

		/*Item* pItem = new Item;
		pItem->Initialize(pRenderer, &worldState.m_Items[0]);
		g_spriteList.push_back(pItem); */

		//Hero
		Hero* pHero = new Hero;
		pHero->Initialize(pRenderer);
		pHero->m_Position.X = 128.0f;
		g_spriteList.push_back(pHero);

		/* //Hero
		heroSprite.Initialize(pRenderer);
		heroSprite.m_Position.X = 128.0f; */


		
		//Enemies
		for (unsigned int i = 0; i < worldState.m_Ghosts.size(); i++)
		{
			Enemy* pEnemy = new Enemy;
			pEnemy->Initialize(pRenderer, &worldState.m_Ghosts[i]);
			pEnemy->m_Position.X = 256.0f;
			pEnemy->m_Position.Y = 32.0f * i;
			pEnemy->m_Position = Vector2d(4.0f * TILE_SIZE_H, 3.0f * TILE_SIZE_W);
			g_spriteList.push_back(pEnemy);
		}


		/*//Enemies
		for (unsigned int i = 0; i < 100; i++)
		{
			enemySprites.push_back(Enemy());
			enemySprites[i].Initialize(pRenderer);
			enemySprites[i].m_Position.X = 256.0f;
			enemySprites[i].m_Position.Y = 32.0f * i;
		}

		//Enemy
		/*enemySprite.Initialize(pRenderer);
		enemySprite.m_Position.X = 256.0f;*/

	}

	void GetInput(const WorldState& worldState, PlayerState& playerState)
	{
		//playerState.m_DesiredDirection = Vector2d(0.0f, 0.0f);

		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.m_bHasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.m_bHasFinishedGame = true;
					break;
				case SDLK_UP:
					playerState.m_DesiredDirection.Y = -1.0f;
					break;
				case SDLK_DOWN:
					playerState.m_DesiredDirection.Y = 1.0f;
					break;
				case SDLK_RIGHT:
					playerState.m_DesiredDirection.X = 1.0f;
					break;
				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = -1.0f;
					break;
				case SDLK_SPACE:
					playerState.m_bWantsToShoot = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_UP:
				case SDLK_DOWN:
					playerState.m_DesiredDirection.Y = 0.0f;
					break;
				case SDLK_RIGHT:
				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = 0.0f;
					break;
				case SDLK_SPACE:
					playerState.m_bWantsToShoot = false;
					break;
				}
			}
		}
	}

	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
	{
		//Update Game
		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Update(deltaSeconds, worldState, playerState);
			
		}
		g_cameraPosition = Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - playerState.m_CurrentPosition;





		
		/*backgroundSprite.Update(deltaSeconds, worldState, playerState);
		heroSprite.Update(deltaSeconds, worldState, playerState);

		for (unsigned int i = 0; i < enemySprites.size(); i++)
		{
			enemySprites[i].Update(deltaSeconds, worldState, playerState);
		}
		//enemySprite.Updatev; */
	}

	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState)
	{
		SDL_RenderClear(pRenderer);



		//Render Game
		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Render(pRenderer, worldState, playerState, g_cameraPosition);
		}

		/*backgroundSprite.Render(pRenderer, worldState, playerState);
		heroSprite.Render(pRenderer, worldState, playerState);

		for (unsigned int i = 0; i < enemySprites.size(); i++)
		{
 			enemySprites[i].Render(pRenderer, worldState, playerState);
		}
		//enemySprite.Render(pRenderer, worldState, playerState); */

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame()
	{
		//Cleanup Game
		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Cleanup();
			delete g_spriteList[i];
		}

		/*backgroundSprite.Cleanup();
		heroSprite.Cleanup();

		for (unsigned int i = 0; i < enemySprites.size(); i++)
		{
			enemySprites[i].Cleanup();
		}
		//enemySprite.Cleanup(); */
		Sprite::ClearTextures();
	}
}