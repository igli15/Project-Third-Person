#include "GridComponent.h"
#include <iostream>
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "game/Balloon.h"
#include "game/components/BalloonComponent.h"
#include "game/components/GridElement.h"
#include "mge/util/Utils.h"

GridComponent::GridComponent()
{
}


GridComponent::~GridComponent()
{
}

void GridComponent::InitGrid()
{
	for (int i = 0; i < m_ballonTilePositions.size(); i++)
	{
		m_ballonTiles.push_back(GetTileOnPos(m_ballonTilePositions[i]));
	}
}

void GridComponent::Awake()
{

}

void GridComponent::Update(float timeStep)
{
	if (m_balloonClock.getElapsedTime().asSeconds() >= m_balloonSpawntime)
	{
		SpawnBalloon();
		m_balloonClock.restart();
	}
}

void GridComponent::SetWidth(int width)
{
	m_width = width;
}

void GridComponent::SetHeight(int height)
{
	m_height = height;
}

void GridComponent::SetTileRadius(float r)
{
	m_tileRadius = r;
}

int GridComponent::Width() const
{
	return m_width;
}

int GridComponent::Height() const
{
	return m_height;
}

int GridComponent::TileRadius() const
{
	return m_tileRadius;
}

void GridComponent::AddTile(TileComponent * tile)
{
	for (size_t i = 0; i < m_height; i++)
	{
		if (m_tileGrid.at(i).size() < m_width)
		{
			m_tileGrid.at(i).push_back(tile);
			tile->SetGridPos(glm::vec2(m_tileGrid.at(i).size() -1 ,i));
			return;
		}
	}
}

void GridComponent::Parse(rapidxml::xml_node<>* compNode)
{
	std::cout << "Parsing Grid Component...." << std::endl;

	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::cout << a->name() << " : " << a->value() << std::endl;
		std::string attributeName = a->name();
		if (attributeName == "gridSizeX")
		{
			SetWidth(atoi(a->value()));
		}
		else if (attributeName == "gridSizeY")
		{
			SetHeight(atoi(a->value()));
		}
		else if (attributeName == "tileRadius")
		{
			SetTileRadius(strtof(a->value(), 0));
		}
		else if (attributeName == "playerPosOffsetX")
		{
			m_tilePosOffsetX = strtof(a->value(), 0);
		}
		else if (attributeName == "playerPosOffsetY")
		{
			m_tilePosOffsetY = strtof(a->value(), 0);
		}
		else if (attributeName == "balloonSpawnTime")
		{
			m_balloonSpawntime = strtof(a->value(), 0);
		}
	}

	/*if (strcmp(compNode->first_node()->name(), "BallonTilePositions") == 0)
	{
		rapidxml::xml_node<>* posNode = compNode->first_node();
		for (rapidxml::xml_node<>* pos = posNode->first_node(); pos != nullptr; pos = pos->next_sibling())
		{
			glm::vec3 tilePos;

			sscanf(pos->first_attribute()->value(), "(%f,%f,%f)", &tilePos.x, &tilePos.y, &tilePos.z);

			m_ballonTilePositions.push_back(tilePos);
		}
	}*/

	m_tileGrid.resize(m_height, std::vector<TileComponent*>());
}

TileComponent * GridComponent::GetTileAt(int x, int y)
{
	if (x >= m_width || y >= m_height || x < 0 || y < 0) return nullptr;

	return m_tileGrid[y][x];
}

TileComponent * GridComponent::GetTileOnPos(glm::vec3 playerPos)
{
	int x = glm::floor((playerPos.x + m_tilePosOffsetX)  / (m_tileRadius * 2.0f));
	int y = glm::floor((playerPos.z + m_tilePosOffsetY) / (m_tileRadius * 2.0f));

	//std::cout << "X: " << x << std::endl;
	//std::cout << "Y: " << y << std::endl;


	if (x < 0 || x >= m_width) return nullptr;
	if (y < 0 || y >= m_height) return nullptr;

	return GetTileAt(x,y);
}

std::vector<TileComponent*> GridComponent::GetNeighbourTiles(glm::vec3 playerPos, glm::vec3 enemyPos, int amount, bool horizontal, bool positiveDir, const std::function<void()>& onEnemyFoundCallback)
{
	std::vector<TileComponent*> tiles;
	TileComponent* currentTile = GetTileOnPos(playerPos);


	if (currentTile == nullptr) return tiles;

	//std::cout <<"MYPOS: "<< playerPos << std::endl;
	//std::cout << "ENEMYPOS: " << enemyPos << std::endl;

	for (int i = 1; i <= amount; i++)
	{
		if (horizontal)
		{
			if (positiveDir && currentTile->GridPos().x + i < m_width)
			{
				if (!GetTileAt(currentTile->GridPos().x + i, currentTile->GridPos().y)->IsPaintable()) return tiles;
				
				TileComponent* enemyTile = GetTileOnPos(enemyPos);
				if (enemyTile != nullptr)
				{
					auto condition = glm::equal(enemyTile->GridPos(), GetTileAt(currentTile->GridPos().x + i, currentTile->GridPos().y)->GridPos());
					if (condition.x && condition.y)
					{
						onEnemyFoundCallback();
					}
				}
				tiles.push_back(GetTileAt(currentTile->GridPos().x + i, currentTile->GridPos().y));
			}
			else if (!positiveDir && ((currentTile->GridPos().x - i) >= 0))
			{
				if (!GetTileAt(currentTile->GridPos().x - i, currentTile->GridPos().y)->IsPaintable()) return tiles;
				TileComponent* enemyTile = GetTileOnPos(enemyPos);

				if (enemyTile != nullptr)
				{
					auto condition = glm::equal(enemyTile->GridPos(), GetTileAt(currentTile->GridPos().x - i, currentTile->GridPos().y)->GridPos());

					if (condition.x && condition.y)
					{
						onEnemyFoundCallback();
					}
				}

				tiles.push_back(GetTileAt(currentTile->GridPos().x - i, currentTile->GridPos().y));
			}
		}
		else
		{
			if (positiveDir && currentTile->GridPos().y + i < m_height)
			{
				if (!GetTileAt(currentTile->GridPos().x, currentTile->GridPos().y + i)->IsPaintable()) return tiles;

				TileComponent* enemyTile = GetTileOnPos(enemyPos);
				if (enemyTile != nullptr)
				{
					auto condition = glm::equal(enemyTile->GridPos(), GetTileAt(currentTile->GridPos().x, currentTile->GridPos().y + i)->GridPos());
					if (condition.x && condition.y)
					{
						onEnemyFoundCallback();
					}
				}
				tiles.push_back(GetTileAt(currentTile->GridPos().x , currentTile->GridPos().y + i));
			}
			else if (!positiveDir && currentTile->GridPos().y - i >= 0)
			{
				if (!GetTileAt(currentTile->GridPos().x, currentTile->GridPos().y - i)->IsPaintable()) return tiles;

				TileComponent* enemyTile = GetTileOnPos(enemyPos);
				if (enemyTile != nullptr)
				{
					auto condition = glm::equal(enemyTile->GridPos(), GetTileAt(currentTile->GridPos().x, currentTile->GridPos().y - i)->GridPos());
					if (condition.x && condition.y)
					{
						onEnemyFoundCallback();
					}
				}
				tiles.push_back(GetTileAt(currentTile->GridPos().x , currentTile->GridPos().y - i));
			}
		}
	}

	return tiles;
}


std::vector<TileComponent*> GridComponent::GetTilesInTriangleRange(glm::vec3 playerPos, glm::vec3 enemyPos, int rows, bool horizontal,
	bool positiveDir, const std::function<void()>& onEnemyFoundCallback)
{
	std::vector<TileComponent*> tiles;
	TileComponent* currentTile = GetTileOnPos(playerPos);
	TileComponent* enemyTile = GetTileOnPos(enemyPos);

	
	if (currentTile == nullptr) return tiles;

	//Getting direction of triangle shooting
	int xDelta =  horizontal ? 1 : 0;
	int yDelta = !horizontal ? 1 : 0;

	if (!positiveDir)
	{
		xDelta *= -1;
		yDelta *= -1;
	}

	for (int rowIndex = 1; rowIndex < rows; rowIndex++)
	{
		//Geting originTile for each row
		TileComponent* gateTile = GetTileAt(currentTile->GridPos().x + rowIndex*xDelta, currentTile->GridPos().y+rowIndex*yDelta);

		//If gateTile is out of grid then stop shooting
		if (gateTile == nullptr) return tiles;

		//Getting row use rectangle painting
		std::vector<TileComponent*> newTiles = GetTilesInARange(gateTile, !horizontal?(rowIndex * 2 - 1):1, horizontal ? (rowIndex * 2 - 1) : 1);

		//Adding new painted tiles to final list
		tiles.insert(tiles.end(), newTiles.begin(), newTiles.end());
	}

	if (enemyTile == nullptr) return tiles;
	for (int i = 0; i < tiles.size(); i++)
	{
		//Checling if enemy stayed on one of the painted tiles
		auto condition = glm::equal(enemyTile->GridPos(),tiles[i]->GridPos());
		if (condition.x && condition.y&&tiles[i]->IsPaintable())
		{
			onEnemyFoundCallback();
		}
	}


	return tiles;
}

std::vector<TileComponent*> GridComponent::GetTilesInARange(glm::vec3 pos, int width, int height)
{
	std::vector<TileComponent*> tiles;
	TileComponent* currentTile = GetTileOnPos(pos);

	TileComponent* startingTile;
	
	int gridX = 0;
	int gridY = 0;

	gridX = currentTile->GridPos().x + width/2;
	gridY = currentTile->GridPos().y + height / 2;


	if ((currentTile->GridPos().y + height / 2) >= m_height)
	{
		height -= (currentTile->GridPos().y + height / 2) - m_height;
		gridY = m_height - 1;
	}

	if ((currentTile->GridPos().x + width / 2) >= m_width)
	{
		width -= (currentTile->GridPos().x + width / 2) - m_width;
		gridX = m_width - 1;
	}
	startingTile = GetTileAt(gridX, gridY);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			TileComponent* tile = GetTileAt(startingTile->GridPos().x - j, startingTile->GridPos().y - i);

			if(tile != nullptr)
			tiles.push_back(tile);
		}
	}


	return tiles;
}

std::vector<TileComponent*> GridComponent::GetTilesInARange(TileComponent* tile, int width, int height)
{
	std::vector<TileComponent*> tiles;
	TileComponent* currentTile = tile;

	TileComponent* startingTile;

	int gridX = 0;
	int gridY = 0;

	gridX = currentTile->GridPos().x + width / 2;
	gridY = currentTile->GridPos().y + height / 2;


	if ((currentTile->GridPos().y + height / 2) >= m_height)
	{
		height -= (currentTile->GridPos().y + height / 2) - m_height;
		gridY = m_height - 1;
	}

	if ((currentTile->GridPos().x + width / 2) >= m_width)
	{
		width -= (currentTile->GridPos().x + width / 2) - m_width;
		gridX = m_width - 1;
	}

	startingTile = GetTileAt(gridX, gridY);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			TileComponent* tile = GetTileAt(startingTile->GridPos().x - j, startingTile->GridPos().y - i);

			if (tile != nullptr)
				tiles.push_back(tile);
		}
	}


	return tiles;
}

void GridComponent::IncreaseTileCount(TileType type)
{
	if (type == TileType::ICE)
	{
		m_iceTileCount += 1;
	}
	else if (type == TileType::LAVA)
	{
		m_lavaTileCount += 1;
	}
	std::cout << std::endl << "STATS: " << std::endl;
	std::cout << "ICE    : " << m_iceTileCount<< std::endl;
	std::cout << "LAVA   : " <<m_lavaTileCount << std::endl;
	std::cout << "NEUTRAL: " <<(m_width*m_height)-m_iceTileCount-m_lavaTileCount<< std::endl;
}

void GridComponent::DecreaseTileCount(TileType type)
{
	if (type == TileType::ICE)
	{
		m_iceTileCount -= 1;
	}
	else if (type == TileType::LAVA)
	{
		m_lavaTileCount -= 1;
	}
}

float GridComponent::GetTileCount(TileType type)
{
	if (type == TileType::ICE)
	{
		return (float)m_iceTileCount/(m_width*m_height) *100.0f;
	}
	else if (type == TileType::LAVA)
	{
		return(float)m_lavaTileCount / (m_width*m_height) *100.0f;
	}
}

void GridComponent::SpawnBalloon()
{
	int occupiedCount = 0;

	for (int i = 0; i < m_ballonTiles.size(); i++)
	{
		if (!m_ballonTiles[i]->IsFree()) occupiedCount += 1;
	}

	if (occupiedCount >= m_ballonTiles.size()) return;

	int randomIndex = Utils::RandomRange(0, m_ballonTiles.size() - 1);

	TileComponent* randomTile = m_ballonTiles[randomIndex];

	while (!randomTile->IsFree())
	{
		randomIndex = Utils::RandomRange(0, m_ballonTiles.size() - 1);
		randomTile = m_ballonTiles[randomIndex];
	}

	Balloon* balloon = m_gameObject->GetWorld()->Instantiate<Balloon>();

	balloon->transform->SetLocalPosition(randomTile->GetGameObject()->transform->WorldPosition());

	randomTile->SetGridElement(balloon->GetBalloonComponent());
}
