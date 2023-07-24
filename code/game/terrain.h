#ifndef TERRAIN_H
#define TERRAIN_H

class terrain
{
    public:
        terrain();
        terrain(XMLElement *terrainElement, SDL_Renderer *ren);
        void testDraw(SDL_Renderer *ren, SDL_Window *win);

        string defName() const { return m_defName; }
        string label() const { return m_label; }
        string description() const { return m_description; }
        SDL_Texture* getTex() const { return tex; }

        float movementSpeed() const { return m_movementSpeed; }
        float commonality() const { return m_commonality; }
        float beauty() const { return m_beauty; }
        float fertility() const { return m_fertility; }
        float support() const { return m_support; }

        terrain& operator=(terrain& other);

    private:
        string m_defName;
        string m_label;
        string m_description;
        SDL_Texture *tex;
        //textureEntry tex;

        float m_movementSpeed;
        float m_commonality;    //how common is the terrain type
        float m_beauty;
        float m_fertility;
        float m_support; // what weight of building can it support
};

//load everything in Data/Terrain
void loadAllTerrain(SDL_Renderer *ren);

terrain* skyNullBlock;

terrain* getTerrainByDefName(string name);

//shit idk, I guess store all the different defs in vectors, idfk
vector<terrain> terrainDatabase;

#include "terrain.hpp"
#endif