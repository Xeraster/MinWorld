#ifndef BIOME_H
#define BIOME_H

//terrain comes with 2 sets of biome specific data: terrain def and commonality
struct terrainEntry
{
    terrain *terrainType;
    float commonality;
};

struct plantEntry
{
    //plant *plantType;
    plantType *plant;
    float commonality;
};

class biome
{
    public:
        biome();
        biome(XMLElement *biomeElement);

        string defName() const { return m_defName; }
        string label() const { return m_label; }
        string description() const { return m_description; }
        color mapColor() const { return m_mapColor; }

        float survivability() const { return m_survivabilty; }
        float commonality() const { return m_commonality; }

        vector<terrainEntry> terrainTypes;
        vector<terrainEntry> undergroundTerrainTypes;
        vector<plantEntry> plantTypes;

        //outputs whether or not a biome is suitable for a chunk with the specified parameters
        bool isTempAcceptable(float temperature, float variance=0.0f);

        //returns a score of how well the biome matches the specified parameters. Unreliable at low values. Do not use for determining the boolean value of if a biome is suitable for a chunk or not. There is actually already a function for that that works well.
        double biomeMatchScore(float temperature, float variance);

    private:
        string m_defName;
        string m_label;
        string m_description;
        color m_mapColor;

        float m_survivabilty;
        float m_commonality;
        float m_tempMax;
        float m_tempMin;
        float m_moveDifficulty;
        float m_forageability;
        float m_diseaseFrequency;
        float m_wind;
        float m_water;
        float m_clouds;
        float m_elevation;

        //vector<plant> spawnablePlants
        //vector<pawnType> spawnableAnimals
};

/*load everything in Data/Biomes/
note that in this iteration of the engine, there can be more than 1 biome per xml file*/
void loadAllBiomes(SDL_Renderer *ren);

biome* getBiomeByDefName(string name);

//shit idk, I guess store all the different defs in vectors, idfk
vector<biome> biomeDatabase;

#include "biome.hpp"
#endif