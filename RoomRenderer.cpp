#include "RoomRenderer.h"

using namespace DungeonGame;

void RoomRenderer::Initialize(SDL_Renderer* pRenderer)
{
	m_pFloorTexture = LoadTexture(pRenderer, "images/Floor.bmp");
	m_pWallTexture = LoadTexture(pRenderer, "images/Wall.bmp");
}

void RoomRenderer::Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation)
{
	const std::vector<unsigned int>& tiles = worldState.m_Tiles;

	int columnsRendered = 0;
	int rowsRendered = 0;

	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		unsigned int tileType = tiles[i];

		SDL_Texture* pCurrTexture = nullptr;
		//TODO: Figure out what texture I need
		switch (tileType)
		{
		case 1:
			pCurrTexture = m_pFloorTexture;
			break;
		case 2:
			pCurrTexture = m_pWallTexture;
			break;
		}


		if (pCurrTexture)
		{
			SDL_Rect destRect =
			{
				columnsRendered * TILE_SIZE_W + baseTransformation.X, //X
				rowsRendered * TILE_SIZE_H + baseTransformation.Y , //Y
				96, //W
				96, //H
			};

			SDL_RenderCopy(pRenderer, pCurrTexture, nullptr, &destRect);

			
		}
		columnsRendered++;
		if (columnsRendered % worldState.m_TilesPerRow == 0)
		{
			rowsRendered++;
			columnsRendered = 0;
		}
		
	}
}