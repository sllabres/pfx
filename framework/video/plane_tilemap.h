
#pragma once

#include "plane.h"
#include "atlas_paletted.h"
#include "animation.h"

class TilemapPlane : public Plane
{

	protected:
		Display* owner;
		int* tilemap;

		void CreateTilemap();

	public:
		Atlas* tileset;
		Size<int> tilesize;
		Size<int> tilemapsize;
		List<Animation*> animations;
		bool index0isempty;

		TilemapPlane(Display* Owner, Atlas* TileSet, Size<int> TileSize);
		TilemapPlane(Display* Owner, Atlas* TileSet, Size<int> TileSize, Size<int> MapSize);
		~TilemapPlane();

		void EventOccured(Event* What) override;
		void Update() override;
		void Render() override;

		int GetMapData(Point<int> At);
		void SetMapData(Point<int> At, int Frame);
};
