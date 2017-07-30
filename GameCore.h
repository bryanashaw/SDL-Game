#pragma once
#include "SDL.h"
#include <vector>

namespace DungeonGame
{
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;

	const float TILE_SIZE_W = 96.0f;
	const float TILE_SIZE_H = 96.0f;

	struct BulletData;

	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{
		}

		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{
		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d &rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d &other) const
		{
			return Vector2d(*this) += other;
		}

		Vector2d& operator-=(const Vector2d &rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d &other) const
		{
			return Vector2d(*this) -= other;
		}

		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}

		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}
	};

	enum ItemType
	{
		Item_None,
		Item_Book,
		Item_Rune,
	};
	struct ItemData
	{
		bool bAlive;
		ItemType Type;
		Vector2d Position;
	};
	struct BulletData
	{
		Vector2d Position;
		bool bAlive;
		Vector2d direction;
		float secondsAlive;
	};

	struct GhostData
	{
		bool bAlive;
		Vector2d Position;
		int hp;

		void OnHitByBullet(BulletData* pBullet);

		bool bPatrolReverse;
		Vector2d PatrolStart;
		Vector2d PatrolEnd;
	};

	class PlayerState
	{
	public:
		void Initialize();
		void Reset();

		bool m_bAlive;

		bool ItemColliderWithPlayer(ItemData* pItem);
		bool EnemyColliderWithPlayer(GhostData* pEnemy);

		bool m_bHasFinishedGame;
		bool m_bWantsToShoot;

		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;

		std::vector<ItemType>m_Inventory;

		int m_hp;
		
		std::vector<BulletData>m_Bullets;
		float m_ShotCooldownSeconds;

	};

	class WorldState
	{
	public:
		void Initialize();
		void Reset();

		unsigned int GetTileTypeAtPosition(const Vector2d& inPosition);

		unsigned int m_TilesPerRow;
		std::vector<unsigned int> m_Tiles;
		Vector2d m_TileSize;

		bool BulletCollidesWithItem(BulletData* pBullet);

		std::vector<ItemData> m_Items;
		std::vector<GhostData> m_Ghosts;
	};

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState);
	void GetInput(const WorldState& worldState, PlayerState& playerState);
	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState);
	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState);
	void CleanupGame();
}