#pragma once
#include "mge/core/XMLComponent.h"
#include <vector>

class TileComponent;

class GridComponent : public XMLComponent
{
public:
	GridComponent();
	virtual ~GridComponent();

	void Awake();
	void SetWidth(int width);
	void SetHeight(int height);
	void SetTileRadius(int r);


	int Width() const;
	int Height() const;
	int TileRadius() const;

	void AddTile(TileComponent* tile);
	void Parse(rapidxml::xml_node<>* compNode) override;

	TileComponent* GetTileAt(int x, int y);

private:

	int m_width = 0;
	int m_height = 0;
	int m_tileRadius = 0;

	std::vector< std::vector<TileComponent*> > m_tileGrid;


};