#ifndef CHUNK_H
#define CHUNK_H

class chunk
{
    public:
        chunk();
        void generateTiles(int sizeX, int sizeY, int sizeZ);

        void freeTiles(int sizeX, int sizeY, int sizeZ);

        void setId(int number) { m_chunkId = number; }
        int getId() const { return m_chunkId; }

        void setBiome(biome *b) { chunkBiome = b;  }
        biome *getBiome() const { return chunkBiome; }

        void setSeed(int seed) { m_planetSeed = seed; }
        void setSides(int newSize) { chunkSideSize = newSize; }
        void setWorldPos(int x, int y) { worldX = x; worldY = y;}
        int getChunkSideSize() const { return chunkSideSize; }//return how many tiles there are per side

        void getPosOfChunk(int *x, int *y) { *x = worldX;  *y = worldY; }
        int getPosX() const { return worldX; }
        int getPosY() const { return worldY; }

        int zLevelOfHighestValidTerrain(int posX, int posY);

        //environment and weather getters/setters
        void setAverageTemperature(double newTemp) { m_averageTemp = newTemp; }
        double getAverageTemperature() const { return m_averageTemp; }

        //insert a lake onto chunk
        void insertLake(int seed);

        //spawns a plant into the chunk. pos is in chunk position and not world position
        void spawnPlant(string defName, int chunkPosX, int chunkPosY, int chunkPosZ, int seed);

        //spawns a plant into the chunk. pos is in chunk position and not world position. overload for passing plant pointer instead of defname for better performance during chunk generation
        void spawnPlant(plantType *thePlant, int chunkPosX, int chunkPosY, int chunkPosZ, int seed);

        //spawns building into chunk. pos is in chunk position not world position.
        building* spawnBuilding(buildingType *theBuilding, int chunkPosX, int chunkPosY, int chunkPosZ, int seed);

        /*spawns thing into chunk. pos is in chunk position not world position. 
        Keep in mind "thing" is only the base class. Make sure the thing you're trying to spawn is *actually* just a "thing" and not a child thingType 
        */
        thing *spawnThing(thingType *theThing, int chunkPosX, int chunkPosY, int chunkPosZ, int seed);

        pawn *spawnPawn(pawnType *thePawn, int chunkPosX, int chunkPosY, int chunkPosZ, int seed);

        //run this upon chunk creation to procedurally spawn in all the plants
        void generatePlantsFromSeed(int seed);

        void drawChunk(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);

        //does the same as drawChunk but only with the bare minimal information. It can even draw chunks that aren't initialized
        void drawUninitialisedChunk(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel, int tilesPerChunk);

        //get the chunk's map color
        color getColor() const { return chunkBiome->mapColor(); }

        bool operator==(const chunk& rhs);

    private:
        //a 3d array of chunks
        tile ***m_tiles;
        //vector tiles
        biome* chunkBiome;
        int m_chunkId;

        bool m_initialized;

        //the same seed as the planet the chunk is on. Each chunk hashes its own copy of the seed in its own way
        int m_planetSeed;
        int chunkSideSize;
        int worldX;
        int worldY;

        //environment and weather data
        double m_averageTemp;   //yearly average temperature of the chunk

        //"draw" a horizontal-only line onto chunk. low-ish resource method of manipulating terrain
        void horizontalLine(terrain *type, int startx, int starty, int zlevel, int length);

        /*you simply can't save every plant or item ever generated to the world. Dynamic objects will be tied to the chunk.
        only after the player has interacted with the item in a meaningful way does it get copied to the world thing vector and become a
        more permanent "world thing"
        chunk things get deleted as soon as their parent chunk gets deleted. world things exist until they are physically destroyed by
        ingame means (i.e. a tree getting chopped down or a wall block getting breeched)
        */
        //thing storages
        vector<thing*> m_chunkThings;
        vector<plant> m_chunkPlants;
        vector<building> m_chunkBuildings;

        list<thing> m_chunkThingsL;
        list<plant> m_chunkPlantsL;
        list<building> m_chunkBuildingsL; // use list instead of vector because resizing a list doesn't change object reference addresses
        list<pawn> m_chunkPawnsL;

        //returns true if the given plant kind can grow on the provided tile
        bool canPlantGrowHere(plantType *type, int chunkX, int chunkY, int chunkZ);

        //returns true if given chunk position is already occupied by a plant
        bool isSpaceOccupiedByPlant(int chunkX, int chunkY, int chunkZ);
};

#include "chunk.hpp"
#endif