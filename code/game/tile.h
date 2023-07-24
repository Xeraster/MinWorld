#ifndef TILE_H
#define TILE_H

class tile
{
    public:
        tile();
        terrain* terrainTile;

        //each tile gets 1 building or 1 plant. only 1 of those can be active at a time and if both are active, buildings take precedence over plants
        thing *buildingOrPlant; //the slot where either a building or a plant can go. putting anything other than a building or a plant here is undefined

        //there can be any number of "floor level" buildings on a tile. They all go here
        //vector<floor*> floorObjects

        //things and pawns are not stored in the tile data so if you came here looking for it, you're wrong

        //returns true if terrain tile is anything other than the null sky block
        bool isRealBlock();

        void setPos(int x, int y, int z) { m_xpos = x; m_ypos = y; m_zpos = z; }

        void drawTile(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);

        //returns how suitable for farming this tile is
        float getFertilityOfTile();

    private:
        int m_xpos;
        int m_ypos;
        int m_zpos;
};

#include "tile.hpp"
#endif