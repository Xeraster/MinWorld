//create the world. also, the earth is flat becuase that's easier to program. Deal with it
planet :: planet()
{
    loadedChunks = vector<chunk*>();
    m_chunksLoaded = false;
    cout << "in planet default constructor" << endl;
}

/*
default values for a "balanced normal temperate planet" are as follows:
setAvgTemp 4.0f
setDaysInYear 340
//setTempVariance 25.0f
that's pretty much it. Since this project is in its infancy, this stuff WILL change in the future

*/
//a constructor for a planet that uses all the scenario-specific stuff. default recommended values are temperatur: 4.0f. axial tilt 25.0f
planet :: planet(unsigned int seed, double temp, double eccentricity, double axialTilt, double water, double population)
{
    //just use the member fuctions
    //programming in c++ is like taking a shit after a long night of spicy wings and booze. It feels amazing while doing it but everyone in your apartment can smell it
    setAvgTemp(temp);//default value is 4
	setDaysInYear(eccentricity*60);//eccentricity is just a multiplier. 1 = 1 year is 60 days. 2 = 1 year is 120 days
	setTempVariance(axialTilt);//axial tilt more or less. changes how extreme temperatures get in the coldest and hotest part of the year
	setSeed(seed);

    loadedChunks = vector<chunk*>();
    m_chunksLoaded = false;//the planets always generate their own chunks

    //clear the chunks before generating them. no memory leaks allowed
    //freeAllChunks();
    cout << "in planet var constructor" << endl;
    generateWorld(100, 100);//generate the world. should be memory safe now
    //water not implemented yet
    //population not implemented yet

}

//copy constructor. putting this in (and making it actually work) makes certain seemingly unrelated things work better although ive been programming c++ for 10 years and never once stopped to think "why does it do that"
planet :: planet(const planet& rhs)
{
    m_seed = rhs.getSeed();

    m_averageTemp = rhs.getAvgTemp();
    m_tempVariance = rhs.getTempVariance();
    m_secsPerDay = rhs.getSecsPerDay();
    m_daysInYear = rhs.getDaysInYear();

    loadedChunks = vector<chunk*>();

    //chunk housekeeping values
    m_sizeX = rhs.getSizeX();
    m_sizeY = rhs.getSizeY();
    m_chunksLoaded = false;//the planets always generate their own chunks

    //there, that's basically everything except the raw chunk data
    //clear the chunks before generating them. no memory leaks allowed
    //freeAllChunks();

    cout << "in planet copy constructor" << endl;
    //generate the world. should be memory safe now
    generateWorld(100, 100);//generate world doesn't clear the chunks before over writing. This causes memory leaks. Fix it
}

//destructor. Needs to call the chunk deletion function and in the future probably a lot of other things
planet :: ~planet()
{
    cout << "planet destructor. Free all the chuks before deleting the object to avoid memory leaks" << endl;
    freeAllChunks();
}

//create the world. also, the earth is flat becuase that's easier to program. Deal with it. there is now a rudimentary chunk free system in place. Crashing has been debugged and fixed but I haven't checked to see if it actually stops memory leaks or not
void planet :: generateWorld(unsigned int sizeX, unsigned int sizeY)
{
    if (!freeAllChunks())
    {
        cout << "chunks are not loaded. Empty array will not be freed" << endl;
    }

    m_sizeX = sizeX;
    m_sizeY = sizeY;

    // generate the chunks
    m_chunks = new chunk *[sizeX];
    int chunkId = 0;
    for (int i = 0; i < sizeY; i++)
    {
        m_chunks[i] = new chunk[sizeY];
        for (int u = 0; u < sizeY; u++)
        {
            //cout << "chunkid = " << chunkId << endl;
            m_chunks[i][u].setId(i*u);
            m_chunks[i][u].setBiome(chooseBiomeForClimate(i,u));
            m_chunks[i][u].setSeed(m_seed);
            m_chunks[i][u].setSides(TILESPERCHUNK);
            m_chunks[i][u].setWorldPos(i, u);
            m_chunks[i][u].setAverageTemperature(getAvgTempForChunk(i, u));//calculate average temperature for chunk and save it to the chunk
            // cout << "biome=" << m_chunks[i][u].getBiome()->defName() << endl;
            chunkId++;
        }
    }

    //don't generate the content of the chunks until the player is looking at them

    //loop through all ys just to test temp
    /*for (int y = 0; y < m_sizeY; y++)
    {
        cout << getAvgTempForChunk(3, y) << endl;
    }*/

    //set the housekeeping variable since chunks are stored in arrays
    m_chunksLoaded = true;
}

//delete all the chunks from memory. Returns true if there were chunks to free. Returns false if there were no chunks loaded
bool planet :: freeAllChunks()
{
    //no chunks to free
    if (!m_chunksLoaded)
    {
        cout << "chunks are not loaded. gtfo. nothing to do here" << endl;
        return false;
    }
    //there are chunks that need to be freed
    else
    {
        cout << "freeing all the chunks in the planet" << endl;
        //unload all the active chunks
        loadedChunks.clear();

        //clear all the chunks from memory
        // generate the chunks
        //m_chunks = new chunk *[sizeX];
        //int chunkId = 0;
        for (int i = 0; i < m_sizeY; i++)
        {
            delete [] m_chunks[i];
        }

        //no way this is going to work on the first try
        cout << "deleted some of the chunks" << endl;

        delete [] m_chunks;

        //no way this is going to do anything other than a segfault on the first try
        cout << "deleted the rest of the chunks" << endl;

        m_chunksLoaded = false;

        //if it got to here without crashing, the chunks were sucessfully unloaded. Return true for
        return true;
    }
}

float planet :: getAvgTempForChunk(unsigned int posX, unsigned int posY)
{
    //middle latitude is the hottest
    int middle = static_cast<float>(m_sizeY) / static_cast<float>(2);

    int diff = abs(middle - static_cast<int>(posY));
    float pdiff = static_cast<float>(diff) / static_cast<float>(m_sizeY/2);
    float idiff = 1.0f - (pdiff*2); //make it so that the higher numbers are at the equatoor instead of the higher numbers being at the poles

    //finally got all that shit worked out. Now, apply the temperature settings
    float finalTemp = (idiff * m_tempVariance) + m_averageTemp;

    // float percentOfPlanetFromEquator =
    //  cout << middle << "-" << posY << "=";

    return finalTemp;
}

double planet :: getWorldSizeX()
{
    return m_sizeX * TILESPERCHUNK;
}

double planet :: getWorldSizeY()
{
    return m_sizeY * TILESPERCHUNK;
}

//pass player chunk position into here to run the chunk loading and freeing system
void planet :: loadChunksBasedOnPosition(int chunkX, int chunkY)
{
    //if looking at chunk and chunk not loaded, load chunk
    if (!chunkLoaded(chunkX, chunkY))
    {
        cout << "loaded chunk at position " << chunkX << "," << chunkY << endl;
        loadedChunks.push_back(&getChunk(chunkX, chunkY));
        //loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
        getChunk(chunkX, chunkY).generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);

        //load adjacent chunks to the one at the center of the player's view
        loadAdjacentChunks(&getChunk(chunkX, chunkY));
    }

    //for each loaded chunk
    //if player is not looking at chunk [AND chunk is not adjacent to an active chunk], unload chunk
    int y = loadedChunks.size();
    for (int i = 0; i < loadedChunks.size(); i++)
    {   
        //if chunk is NOT the center looked at chunk AND the chunk is NOT next to an active chunk, unload it from memory
        if (/*chunkPosToId(chunkX, chunkY) != loadedChunks.at(i)->getId() && */!isAdjacentToActiveChunk(&m_chunks[chunkX][chunkY], loadedChunks.at(i)))
        {
            cout << "unloading chunk at position " << loadedChunks.at(i)->getPosX() << "," << loadedChunks.at(i)->getPosY() << endl;
            loadedChunks.at(i)->freeTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
            loadedChunks.erase(loadedChunks.begin()+i);
            //y--;
            cout << "unloaded chunk and didn't crash" << endl;
        }
    }
}

bool planet :: chunkLoaded(int chunkx, int chunky)
{
    bool found = false;
    int idToFind = chunkPosToId(chunkx, chunky);

    for (int i = 0; i < loadedChunks.size(); i++)
    {
        if (loadedChunks.at(i)->getId() == idToFind)
        {
            found = true;
        }
    }

    return found;
}

bool planet :: chunkExits(chunk *chunkToCheck)
{
    bool found = false;
    for (int i = 0; i < loadedChunks.size(); i++)
    {
        if (chunkToCheck == loadedChunks.at(i))
        {
            found = true;
            break;//for performance
        }
    }

    return found;
}

//convert a chunk array position into a chunk id
int planet :: chunkPosToId(int chunkx, int chunky)
{
    return chunkx * chunky;
}

biome* planet :: chooseBiomeForClimate(int chunkx, int chunky)
{
    vector<biome *> potentialBiomes;
    for (int i = 0; i < biomeDatabase.size(); i++)
    {
        float chunkAvgTemp = getAvgTempForChunk(chunkx, chunky);

        //if temp is acceptable for biome, add it to list of acceptable chunks
        if (biomeDatabase.at(i).isTempAcceptable(chunkAvgTemp, m_tempVariance))
        {
            potentialBiomes.push_back(&biomeDatabase.at(i));
        }
    }
    // if no biomes found, assign the wasteland biome.
    if (potentialBiomes.size() == 0)
    {
        //cout << "avgtemp=" << getAvgTempForChunk(chunkx, chunky) << "biome = wasteland" << endl;
        return getBiomeByDefName("Wasteland");
    }
    //else if nonzero number of suitable biomes found, pick one at random
    else
    {
        //this formula is garbage. don't use it
        //int chunkSeed = m_seed + chunkx + chunky;
        
        int chunkSeed = (m_seed + pow(chunkx,2))/chunky;//not perfect but good enough. Does achieve a very random looking spread (for the most part)
        int randIndex = betterRand(chunkSeed) % potentialBiomes.size();

        //take into account biome commonality instead of randomly picking them all with the same selection weight
        bool finalBiomeFound = false;
        while (!finalBiomeFound)
        {
            //its possible and common to have multiple possible biomes for a chunk. We need to get a match score to make it look even more realistic
            //float score = 1;//a value between 0 and 3
            //if (chunkx == 5 && chunky == 50)
            //{
            //    cout << "biome to check is " << potentialBiomes.at(randIndex)->defName() << " and score=" << potentialBiomes.at(randIndex)->biomeMatchScore(m_averageTemp, m_tempVariance) << endl;
            //}

            //if a biome's temperature rage fits really well, give it a bonus
            double matchBonus = potentialBiomes.at(randIndex)->biomeMatchScore(m_averageTemp, m_tempVariance);
            double totalScore = potentialBiomes.at(randIndex)->commonality() + matchBonus;

            chunkSeed++;
            if (totalScore > betterRand(chunkSeed) % 10)
            {
                finalBiomeFound = true;
            }
            else
            {
                //if the weighted random roll failed, generate another rand index
                randIndex = betterRand(chunkSeed*randIndex/2.4124) % potentialBiomes.size();
            }
        }

        //cout << "avgtemp=" << getAvgTempForChunk(chunkx, chunky) << "and randindex=" << randIndex << "biome=" << << endl;
        return potentialBiomes.at(randIndex);
    }
}

//loads all chunks adjacent to the input chunk
void planet :: loadAdjacentChunks(chunk *loadedChunk)
{
    int cx;
    int cy;
    loadedChunk->getPosOfChunk(&cx, &cy);
    cout << "cx=" << cx << " cy=" << cy << endl;

    //load all 8 adjacency combinations
    if (!chunkLoaded(cx - 1, cy - 1))
    {
        loadedChunks.push_back(&getChunk(cx - 1, cy - 1));
        getChunk(cx - 1, cy - 1).generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx - 1, cy))
    {
        loadedChunks.push_back(&getChunk(cx -1 , cy));
        getChunk(cx - 1, cy).generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx - 1, cy + 1))
    {
        loadedChunks.push_back(&getChunk(cx - 1, cy + 1));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx, cy - 1))
    {
        loadedChunks.push_back(&getChunk(cx, cy - 1));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx, cy + 1))
    {
        loadedChunks.push_back(&getChunk(cx, cy + 1));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx + 1, cy - 1))
    {
        loadedChunks.push_back(&getChunk(cx + 1, cy - 1));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx + 1, cy))
    {
        loadedChunks.push_back(&getChunk(cx + 1, cy));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }

    if (!chunkLoaded(cx - 1, cy + 1))
    {
        loadedChunks.push_back(&getChunk(cx - 1, cy + 1));
        loadedChunks.back()->generateTiles(TILESPERCHUNK, TILESPERCHUNK, TILESPERCHUNK);
    }
    else
    {
        cout << "warning: attempted to load an already loaded chunk" << endl;
    }
}


//returns true if chunkToCheck is adjacent to centerFocusChunk
bool planet :: isAdjacentToActiveChunk(chunk* centerFocusChunk, chunk* chunkToCheck)
{
    //get the position of the chunk the player is focused on
    int cfx;
    int cfy;
    centerFocusChunk->getPosOfChunk(&cfx, &cfy);

    //get the position of the chunk to compare
    int cx;
    int cy;
    chunkToCheck->getPosOfChunk(&cx, &cy);

    //if chunk is only 1 chunk away, then its adjacent
    if (abs(cx - cfx) <= 1 && abs(cy - cfy) <= 1)
    {
        return true;
    }
    else return false;
}

void planet :: doTick()
{
    const int FRAMESPERSEC = 60;//ffs figure out a better way to do this

    
}

planet planet :: operator=(const planet& rhs)
{
    m_seed = rhs.getSeed();

    m_averageTemp = rhs.getAvgTemp();
    m_tempVariance = rhs.getTempVariance();
    m_secsPerDay = rhs.getSecsPerDay();
    m_daysInYear = rhs.getDaysInYear();

    loadedChunks = vector<chunk*>();

    //chunk housekeeping values
    m_sizeX = rhs.getSizeX();
    m_sizeY = rhs.getSizeY();
    m_chunksLoaded = false;//the planets always generate their own chunks

    //there, that's basically everything except the raw chunk data

    //clear the chunks before generating them. no memory leaks allowed
    //freeAllChunks();

    //generate the world. should be memory safe now
    cout << "in planet operator=" << endl;
    generateWorld(100, 100);//generate the world. should be memory safe now

    return *this;

}