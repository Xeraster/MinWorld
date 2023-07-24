#ifndef PLANET_H
#define PLANET_H

class planet
{
    public:
        planet();

        //a constructor for a planet that uses all the scenario-specific stuff
        planet(unsigned int seed, double temp, double eccentricity, double axialTilt, double water, double population);

        //copy constructor. putting this in (and making it actually work) makes certain seemingly unrelated things work better although ive been programming c++ for 10 years and never once stopped to think "why does it do that"
        planet(const planet& rhs);

        //destructor. Needs to call the chunk deletion function and in the future probably a lot of other things
        ~planet();

        //create the world. also, the earth is flat becuase that's easier to program. Deal with it. there is now a rudimentary chunk free system in place. Crashing has been debugged and fixed but I haven't checked to see if it actually stops memory leaks or not
        void generateWorld(unsigned int sizeX, unsigned int sizeY);

        //delete all the chunks from memory. Returns true if there were chunks to free. Returns false if there were no chunks loaded
        bool freeAllChunks();

        //getter for m_chunksLoaded. generally this shouldn't be used from outside the classs
        bool areChunksInMemory() const { return m_chunksLoaded; }

        float getAvgTemp() const { return m_averageTemp; }
        void setAvgTemp(float number) { m_averageTemp = number; }

        float getTempVariance() const { return m_tempVariance; }
        void setTempVariance(float number) { m_tempVariance = number; }

        float getSecsPerDay() const { return m_secsPerDay; }
        void setSecsPerDay(unsigned int number) { m_secsPerDay = number; }

        float getDaysInYear() const { return m_daysInYear; }
        void setDaysInYear(unsigned int number) { m_daysInYear = number; }

        void setSeed(int number) { m_seed = number; }
        int getSeed() const { return m_seed; }

        //get planet's x size in chunks
        unsigned int getSizeX() const { return m_sizeX; }

        //get planet's y size in chunks
        unsigned int getSizeY() const { return m_sizeY; }

        //get planet's world sie in coordinates
        double getWorldSizeX();

        //get planet's world size in coordinates
        double getWorldSizeY();

        //TRY TO DERIVE AS MUCH STUFF AS POSSIBLE FROM THIS
        //tiles in the x and y coords of the chunk. e.g. a value of 100 means chunks are 100 x 100 tiles
        const int TILESPERCHUNK = 100;

        vector<chunk*> loadedChunks;

        //pass player chunk position into here to run the chunk loading and freeing system
        void loadChunksBasedOnPosition(int chunkX, int chunkY);

        bool chunkLoaded(int chunkx, int chunky);

        bool chunkExits(chunk *chunkToCheck);

        //convert a chunk array position into a chunk id
        int chunkPosToId(int chunkx, int chunky);

        chunk& getChunk(int chunkx, int chunky) { return m_chunks[chunkx][chunky]; }

        //chunk getChunkPtr(int chunkx, int chunky) { return m_chunks[chunkx][chunky]; }

        biome* chooseBiomeForClimate(int chunkx, int chunky);

        //loads all chunks adjacent to the input chunk
        void loadAdjacentChunks(chunk *loadedChunk);

        //returns true if chunkToCheck is adjacent to centerFocusChunk
        bool isAdjacentToActiveChunk(chunk* centerFocusChunk, chunk* chunkToCheck);

        void doTick();

        planet operator=(const planet& rhs);


    private:
        //a 2d array of chunks
        chunk **m_chunks;
        unsigned int m_sizeX;
        unsigned int m_sizeY;
        bool m_chunksLoaded;//housekeeping variable to keep track of whether or not chunks are in memory

        float m_averageTemp;
        float m_tempVariance;
        unsigned int m_secsPerDay;  //all planet days are "24 hours". The length of an hour depends on the number of seconds in a day divided by 24
        unsigned int m_daysInYear;

        int m_seed;

        float getAvgTempForChunk(unsigned int posX, unsigned int posY);
};

#include "planet.hpp"
#endif