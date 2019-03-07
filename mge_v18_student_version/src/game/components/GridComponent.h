#pragma once
#include "mge/core/XMLComponent.h"
#include <vector>
#include "glm.hpp"
#include <functional>

#include "game/components/TileComponent.h"

class GridComponent : public XMLComponent
{
public:
	GridComponent();
	virtual ~GridComponent();

	void InitGrid();
	void Awake();
	void SetWidth(int width);
	void SetHeight(int height);
	void SetTileRadius(float r);


	int Width() const;
	int Height() const;
	int TileRadius() const;

	void AddTile(TileComponent* tile);
	void Parse(rapidxml::xml_node<>* compNode) override;

	//Get a Tile by array index.
	TileComponent* GetTileAt(int x, int y);

	//Returns the tile based on the provided world position!
	TileComponent* GetTileOnPos(glm::vec3 playerPos);

	/*
		Gets the neighbour tiles from the tile the player is currently on.
		Amount is how much we want to search in the specified direction.
		Horizontal boolean stands if we want to search horizontally or verticaly.
		Positive boolean stands for if we want to go in the positive direction or neigative direction.

		Note: if the border of the map are reached then it will limit the amount to that size.

		It returns a vector of all the tiles found.
	*/
	std::vector<TileComponent*> GetNeighbourTiles(glm::vec3 playerPos,glm::vec3 enemyPos,int amount, bool horizontal, bool positiveDir,const std::function<void()>& onEnemyFoundCallback);


	std::vector<TileComponent*> GetTilesInARange(glm::vec3 playerPos, int width, int height);

	void IncreaseTileCount(TileType type);
	void DecreaseTileCount(TileType type);
	float GetTileCount(TileType type);
	
	void SpawnBalloon();

private:

	int m_width = 0;
	int m_height = 0;
	float m_tileRadius = 0;

	int m_iceTileCount = 0;
	int m_lavaTileCount = 0;

	std::vector< std::vector<TileComponent*> > m_tileGrid;

	std::vector<glm::vec3> m_ballonTilePositions;
	std::vector<TileComponent*> m_ballonTiles;

};