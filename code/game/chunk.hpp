chunk :: chunk()
{
    m_initialized = false;
}

void chunk :: generateTiles(int sizeX, int sizeY, int sizeZ)
{
    //search for the bedrock pointer now instead of doing it for every row or every tile or soemthing stupid like that
    terrain* bedrock = getTerrainByDefName("Bedrock");

    //don't do it if the chunk is already initialized
    if (!m_initialized)
    {
        m_tiles = new tile **[sizeX];

        for (int i = 0; i < sizeY; i++)
        {
            m_tiles[i] = new tile *[sizeY];
            for (int u = 0; u < sizeX; u++)
            {
                m_tiles[i][u] = new tile[sizeZ];
                //for each tile, assign a seeded random terrain type to each tile
                for (int v = 0; v < sizeZ; v++)
                {
                    //cout << "got her4" << endl;
                    //its just throwing 64 bit pointers around. the overhead from doing it this way shouldn't be very significant

                    //if zlevel is lowest, make everything be made out of bedrock
                    if (v == 0)
                    {
                        m_tiles[i][u][v].terrainTile = bedrock;

                        //we have to assign each stupid tile a world position also
                        m_tiles[i][u][v].setPos(i+(worldX*chunkSideSize), u+(worldY*chunkSideSize), v);
                    }
                    //if zlevel is less than 0 (0 is the ground surface level), use the underground tileset
                    else if (v < (sizeZ / 2))
                    {
                        //underground chunk generation
                        int randomIndex = betterRand((m_planetSeed + m_chunkId) + i * u + v) % chunkBiome->undergroundTerrainTypes.size();
                        //cout << "randindex=" << randomIndex << chunkBiome->terrainTypes.size() << endl;
                        m_tiles[i][u][v].terrainTile = chunkBiome->undergroundTerrainTypes.at(randomIndex).terrainType;

                        //we have to assign each stupid tile a world position also
                        m_tiles[i][u][v].setPos(i+(worldX*chunkSideSize), u+(worldY*chunkSideSize), v);
                    }
                    //if zlevel is 0, use the surface level tileset
                    else if (v == 50) //only put surface terrain on level 0
                    {
                        //surface level chunk generation
                        int randomIndex = betterRand((m_planetSeed + m_chunkId) + i * u + v) % chunkBiome->terrainTypes.size();
                        //cout << "randindex=" << randomIndex << chunkBiome->terrainTypes.size() << endl;
                        m_tiles[i][u][v].terrainTile = chunkBiome->terrainTypes.at(randomIndex).terrainType;

                        //we have to assign each stupid tile a world position also
                        m_tiles[i][u][v].setPos(i+(worldX*chunkSideSize), u+(worldY*chunkSideSize), v);
                    }
                    else
                    {
                        //assign the sky block to empty sky tiles
                        m_tiles[i][u][v].terrainTile = nullptr;

                        // we have to assign each stupid tile a world position even if its a sky block tile
                        m_tiles[i][u][v].setPos(i+(worldX*chunkSideSize), u+(worldY*chunkSideSize), v);
                    }
                }

            }
        }

        insertLake(m_chunkId);
        //spawnPlant("Tree", 88, 88, 50);
        generatePlantsFromSeed((m_chunkId*8)+9);
        spawnBuilding(getBuildingTypeByDefName("Well"), 88, 88, 50, 69420);
        building* testBench = spawnBuilding(getBuildingTypeByDefName("BasicWorkbench"), 8, 8, 50, 69420);
        building* testBench2 = spawnBuilding(getBuildingTypeByDefName("BasicResearchBench"), 8, 11, 50, 69420);
        //building* testBench2 = spawnBuilding(getBuildingTypeByDefName("BasicResearchBench"), 80, 78, 50, 69420);
        //building* testBench2 = spawnBuilding(getBuildingTypeByDefName("BasicWorkbench"), 85, 85, 50, 69420);
        //spawnBuilding(getBuildingTypeByDefName("BasicResearchBench"), 80, 80, 50, 69420);
        //spawnBuilding(getBuildingTypeByDefName("BasicWorkbench"), 85, 85, 50, 69420);
        testBench->setRotation(270);
        testBench2->setRotation(0);
        vector<positionEntry> positionTestList;
        testBench->getOccupiedTiles(&positionTestList);
        testBench2->getOccupiedTiles(&positionTestList);
        // cout << m_chunkBuildings.at(m_chunkBuildings.size() - 2).getRotation() << endl;
        // cout << m_chunkBuildings.at(m_chunkBuildings.size() - 1).getRotation() << endl;

        //test spawning a thing
        thing* testThing1 = spawnThing(GetThingTypeByDefName("Iron"), 4, 4, 50, 69420);
        thing* testThing2 = spawnThing(GetThingTypeByDefName("Copper"), 4, 5, 50, 69420);
        thing* testThing3 = spawnThing(GetThingTypeByDefName("RubberDuck"), 5, 4, 50, 69420);
        testThing1->setStackSize(12);
        testThing2->setStackSize(999);
        testThing3->setStackSize(1);

        //spawn a test pawn
        spawnPawn(getPawnTypeByDefName("Trilobyte"), 7,7,50,69420);

        m_initialized = true;
    }
}

void chunk :: freeTiles(int sizeX, int sizeY, int sizeZ)
{
    if (m_initialized)
    {
        for (int i = 0; i < sizeY; i++)
        {
            //m_tiles[i] = new tile *[sizeY];
            for (int u = 0; u < sizeX; u++)
            {
                delete m_tiles[i][u];
            }
            delete m_tiles[i];
        }
        delete m_tiles;//idk remove if causes crash. sometimes in c++ it's not possible to both avoid 100% of the memory leaks and 100% of the crashes
    }

    //delete anything that didn't become a world thing
    m_chunkThings.clear();
    m_chunkPlants.clear();

    m_chunkPlantsL.clear();
    m_chunkBuildingsL.clear();

    //be sure to clear the chunk things
    m_initialized = false;
}

int chunk :: zLevelOfHighestValidTerrain(int posX, int posY)
{
    int returnableValue = -1;
    for (int i = GLOBAL_TILES_PERCHUNK - 40; i > 40; i--)
    {
        if (m_tiles[posX][posY][i].terrainTile != nullptr)
        {
            returnableValue = i;
            break;
        }
    }

    return returnableValue;
}

//insert a lake onto chunk
void chunk :: insertLake(int seed)
{
    //lakes are usually made out of water
    terrain *tileToUse = getTerrainByDefName("Water");
    int width = (betterRand(seed) % 25) + 5;
    int idk = (betterRand(seed + 1) % 20) + 5;

    int randXPos = (betterRand(seed+4) % 50) + 20;
    int randYPos = (betterRand(seed + 5) % 60) + 3;

    //cout << "width=" << width << " idk=" << idk << endl;

    //draw the shittiest lake anyone has ever seen
    float i = width * -1;
    for (int x = 0; x < idk; x++)
    {
        int u = width - abs(i);
        horizontalLine(getTerrainByDefName("Water"), randXPos - (u/2), randYPos + x, 50, u*2);
        //i+=static_cast<float>(betterRand(seed+2) % 35)/10;
        i += 1.5f * 10 / idk;
    }
}

//spawns a plant into the chunk. pos is in chunk position and not world position
void chunk :: spawnPlant(string defName, int chunkPosX, int chunkPosY, int chunkPosZ, int seed)
{
    //it has to be in world position not chuink position
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkPosX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkPosY;

    m_chunkPlantsL.push_back(plant(defName, wx, wy, chunkPosZ, 69420));
    m_chunkThings.push_back(&m_chunkPlantsL.back());
    cout << "spawned a " << defName << " at chunk position " << chunkPosX << "," << chunkPosY;
    cout << " (worldpos " << wx << "," << wy << ")" << endl;
}

//spawns a plant into the chunk. pos is in chunk position and not world position. overload for passing plant pointer instead of defname for better performance during chunk generation
void chunk :: spawnPlant(plantType *thePlant, int chunkPosX, int chunkPosY, int chunkPosZ, int seed)
{
    //it has to be in world position not chuink position
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkPosX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkPosY;

    m_chunkPlantsL.push_back(plant(thePlant, wx, wy, chunkPosZ, seed));
    m_chunkThings.push_back(&m_chunkPlantsL.back());
    //cout << "spawned a " << thePlant->defName() << " class plant at chunk position " << chunkPosX << "," << chunkPosY;
    //cout << " (worldpos " << wx << "," << wy << ")" << endl;
}

//spawns building into chunk. pos is in chunk position not worlf position.
building* chunk :: spawnBuilding(buildingType *theBuilding, int chunkPosX, int chunkPosY, int chunkPosZ, int seed)
{
    //it has to be in world position not chunk position for drawing to work, sincee everything is rendered from the player's point of view
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkPosX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkPosY;

    building newBuilding(theBuilding, wx, wy, chunkPosZ, seed);
    //m_chunkBuildings.push_back(building(theBuilding, wx, wy, chunkPosZ, seed));
    //m_chunkThings.push_back(&m_chunkBuildings.back());

    //return &m_chunkBuildings.at(m_chunkBuildings.size() - 1);
    //return *m_chunkThings.at(m_chunkThings.size() - 1);

    m_chunkBuildingsL.push_back(newBuilding);
    m_chunkThings.push_back(&m_chunkBuildingsL.back());
    return &m_chunkBuildingsL.back();
}

/*spawns thing into chunk. pos is in chunk position not world position. 
Keep in mind "thing" is only the base class. Make sure the thing you're trying to spawn is *actually* just a "thing" and not a child thingType 
*/
thing* chunk :: spawnThing(thingType *theThing, int chunkPosX, int chunkPosY, int chunkPosZ, int seed)
{
    //it has to be in world position not chunk position for drawing to work, since everything is rendered from the player's point of view
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkPosX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkPosY;

    thing newThing(theThing, wx, wy, chunkPosZ, seed);
    //m_chunkBuildings.push_back(building(theBuilding, wx, wy, chunkPosZ, seed));
    //m_chunkThings.push_back(&m_chunkBuildings.back());

    //return &m_chunkBuildings.at(m_chunkBuildings.size() - 1);
    //return *m_chunkThings.at(m_chunkThings.size() - 1);
    cout << "spawning a new thing of type " << theThing->defName() << endl;

    m_chunkThingsL.push_back(newThing);
    m_chunkThings.push_back(&m_chunkThingsL.back());//was m_chunkBuildingsL but I changed it because I am 99.999% sure that was a typo
    return &m_chunkThingsL.back();
}

pawn* chunk :: spawnPawn(pawnType *thePawn, int chunkPosX, int chunkPosY, int chunkPosZ, int seed)
{
    //it has to be in world position not chunk position for drawing to work, since everything is rendered from the player's point of view
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkPosX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkPosY;

    pawn newPawn(thePawn, wx, wy, chunkPosZ, seed);

    cout << "spawning a new pawn of type " << thePawn->defname() << endl;
    m_chunkPawnsL.push_back(newPawn);
    m_chunkThings.push_back(&m_chunkPawnsL.back());
    return &m_chunkPawnsL.back();
}

//run this upon chunk creation to procedurally spawn in all the plants
void chunk :: generatePlantsFromSeed(int seed)
{
    //for each plant in the chunk's biomes' plant list, spawn them via weighted random
    for (int p = 0; p < chunkBiome->plantTypes.size(); p++)
    {
        //use commonality variable to decide roughly how many of each plant to make
        int randAmt = betterRand(seed + 9 + p) % (int)(chunkBiome->plantTypes.at(p).commonality * 100);
        int cSoFar = 0;//for debug log output
        //make a random amount of plants based on seed and plant commonality
        int sucessfulSpawns = 0;
        for (int c = 0; c < randAmt; c++)
        {
            bool foundValidSpot = false;
            int retries = 0;
            //not all tiles are suitable for every kind of plant. if attempted tile is unsuitable, retry up to 100 times before giving up
            while (!foundValidSpot && retries < 100)
            {
                int randX = (betterRand(seed + ((10+retries) * c) + p) % 98) + 1;
                int randY = (betterRand(seed + ((11+retries) * c) + p) % 98) + 1;
                //cout << randX << "," << randY << endl;

                if (canPlantGrowHere(chunkBiome->plantTypes.at(p).plant, randX, randY, 50) && !isSpaceOccupiedByPlant(randX, randY, 50))
                {
                    spawnPlant(chunkBiome->plantTypes.at(p).plant, randX, randY, 50, seed + (12 * c) + p);
                    foundValidSpot = true;
                    sucessfulSpawns++;
                }
                retries++;
            }
            if (!foundValidSpot)
            {
                //cout << "could not find suitable spot for plant of type " << chunkBiome->plantTypes.at(p).plant->defName() << "even after " << retries << " retries in biome type " << chunkBiome->defName() << " with chunk position of " << worldX << "," << worldY << endl;
            }
            cSoFar = c;
        }
        cout << "spawned " << sucessfulSpawns << " of " << cSoFar << " plants of type " << chunkBiome->plantTypes.at(p).plant->defName() << " in chunk with id of " << m_chunkId << " and biome type of " << chunkBiome->defName() << endl;
    }
}

void chunk :: drawChunk(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    //for each tile, call its draw function
    for (int i = 0; i < chunkSideSize; i++)
    {
        //m_tiles[i] = new tile *[sizeY];
        for (int u = 0; u < chunkSideSize; u++)
        {
            if (m_tiles[i][u][playerCameraZ+(GLOBAL_TILES_PERCHUNK/2)].isRealBlock())
            {
                m_tiles[i][u][playerCameraZ+(GLOBAL_TILES_PERCHUNK/2)].drawTile(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
            }
            else
            {
                int z = zLevelOfHighestValidTerrain(i, u);
                m_tiles[i][u][z].drawTile(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);

                //the performance of drawing sky transparency over the lowest valid block tanks performance
                //int screenPosX = i - playerCameraX + (worldX*GLOBAL_TILES_PERCHUNK);
                //int screenPosY = u - playerCameraY + (worldY*GLOBAL_TILES_PERCHUNK);
                //cout << "xy=" << screenPosX << "," << screenPosY << endl;
                //color fuck = color(10, 150, 255, (1.0f*playerCameraZ));
                //drawRectFilled(ren, fuck, screenPosX, screenPosY, (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2));
                //drawRectFilled(ren, color(10, 150, 255, 10), screenPosX, screenPosY, (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2));
                //drawRectFilled(ren, color(255, 0, 0, 10), screenPosX, screenPosY, (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2));
                //drawPixel(ren, screenPosX, screenPosY, color(255, 255, 255));
            }
        }
        //delete m_tiles[i];
    }

    //draw every chunk plant if the chunk is loaded
    /*for (int i = 0; i < m_chunkPlants.size(); i++)
    {
        m_chunkPlants.at(i).drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }*/
    for (std::list<plant>::iterator it=m_chunkPlantsL.begin(); it!=m_chunkPlantsL.end(); ++it)
    {
        it->drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }

    //draw every chunk building if the chunk is loaded
    /*for (int i = 0; i < m_chunkBuildings.size(); i++)
    {
        m_chunkBuildings.at(i).drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }*/
    for (std::list<building>::iterator it=m_chunkBuildingsL.begin(); it!=m_chunkBuildingsL.end(); ++it)
    {
        it->drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }

    //draw the generic things
    for (std::list<thing>::iterator it=m_chunkThingsL.begin(); it!=m_chunkThingsL.end(); ++it)
    {
        it->drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }

    //draw all the pawns
    for (std::list<pawn>::iterator it=m_chunkPawnsL.begin(); it!=m_chunkPawnsL.end(); ++it)
    {
        it->drawThing(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
    }
}

//does the same as drawChunk but only with the bare minimal information. It can even draw chunks that aren't initialized
//this is different because it each chunk has to figure out if its on the player's screen or not before being drawn. maybe this will tank performance, maybe it wont. Only 1 way to find out
void chunk :: drawUninitialisedChunk(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel, int tilesPerChunk)
{
    int screenPosX = (worldX*chunkSideSize) - playerCameraX;
    int screenPosY = (worldY*chunkSideSize) - playerCameraY;

    int drawposX = (screenPosX*zoomLevel) + (gscreenx/2);
    int drawposY = (screenPosY*zoomLevel) + (gscreeny/2);

    //"simply" draw a solid color that's the same size as the chunk
    drawRectFilled(ren, getColor(), drawposX, drawposY, zoomLevel*tilesPerChunk, zoomLevel*tilesPerChunk);
    //the biggest differences between this and the tile draw function is zoomLevel*tilesPerChunk and drawRectFilled vs renderTextureEx

    //cout << "drawing uninitialized chunk at " << (screenPosX*zoomLevel) + (gscreenx/2) << "," << (screenPosY*zoomLevel) + (gscreeny/2) << endl;
    //cout << "size of rectangle is " << zoomLevel << " and color=" << getColor() << endl;
    //cout << "biome name is " << chunkBiome->defName() << endl;
    
    //cout << "worldX=" << worldX << ". worldY=" << worldY << endl;
    //renderTextureEx(terrainTile->getTex(), ren, (screenPosX*zoomLevel) + (gscreenx/2), (screenPosY*zoomLevel) + (gscreeny/2), zoomLevel, zoomLevel, 0);

    //now that we got that out of the way, let's draw some chunk information to the tile
    //when zoomAmt is a number higher than 4, draw the text in the upper left corner of the tile but dont try to take up the entire tile
    //when zoomAmt is a number equal to or greater than 4, make the text take up the entire block
    //when zoomAmt is a number less than 0.5, don't draw any text at all
    
    //this part is still WIP
    int fontsize = 12;
    if (zoomLevel > 4)
    {
        //if zoomed in kind of close
        fontsize = (12 * gscreenx / 800);
        drawText(ren, fontsize, color(255,255,255),chunkBiome->label(), drawposX, drawposY);

        //draw additional information if zoomed in closer than 4
        drawText(ren, fontsize-2, color(255,255,255), "avg temp "+to_string(m_averageTemp), drawposX, drawposY + getTextYSize(fontsize) + 2);

    }
    else if (zoomLevel < 1.5)
    {
        //don't draw any chunk map text if zoomed out this far
    }
    else
    {
        drawText(ren, fontsize, color(255,255,255),chunkBiome->label(), drawposX, drawposY);
        drawText(ren, fontsize-2, color(255,255,255), "avg temp "+to_string(m_averageTemp), drawposX, drawposY + getTextYSize(fontsize) + 2);
    }

    //int fontsize = (12 * gscreenx / 800)*zoomLevel/12;//make font size tied to screen x size
    //drawText(ren, fontsize, color(255,255,255),chunkBiome->label(), drawposX, drawposY);
}

bool chunk :: operator==(const chunk& rhs)
{
    if (m_chunkId == rhs.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//"draw" a horizontal-only line onto chunk. low-ish resource method of manipulating terrain
void chunk :: horizontalLine(terrain *type, int startx, int starty, int zlevel, int length)
{
    for (int i = 0; i < length; i++)
    {
        //cout << "line i =" << i << endl;
        m_tiles[startx+i][starty][zlevel].terrainTile = type;
    }
}

//returns true if the given plant kind can grow on the provided tile
bool chunk :: canPlantGrowHere(plantType *type, int chunkX, int chunkY, int chunkZ)
{
    //save pointer to tile we want to check
    tile *tileToCheck = &m_tiles[chunkX][chunkY][chunkZ];
    double pFert = type->minFertility();
    double tFert = tileToCheck->getFertilityOfTile();

    //these compare operations resolve incorrectly for some reason
    if (tFert >= pFert && tFert != 0)
    {
        //cout << type->defName() << " with min fertility of " << type->minFertility() << " can grow on tile " << tileToCheck->terrainTile->defName() << " which has a tile fertility of" << tileToCheck->terrainTile->fertility() << endl;
        return true;
    }
    else
    {
        //cout << type->defName() << " with min fertility of " << type->minFertility() << " can't grow on tile " << tileToCheck->terrainTile->defName() << " which has a tile fertility of" << tileToCheck->terrainTile->fertility() << endl;
        return false;
    }
}

//returns true if given chunk position is already occupied by a plant
bool chunk :: isSpaceOccupiedByPlant(int chunkX, int chunkY, int chunkZ)
{
    //first, convert the provided chunk position into a world position since thats the positioning scheme all things use
    int wx = (worldX * GLOBAL_TILES_PERCHUNK) + chunkX;
    int wy = (worldY * GLOBAL_TILES_PERCHUNK) + chunkY;

    for (int i = 0; i < m_chunkPlants.size(); i++)
    {
        int x = m_chunkPlants.at(i).getPosX();
        int y = m_chunkPlants.at(i).getPosY();
        int z = m_chunkPlants.at(i).getPosZ();

        //if found match then we found what we came for. exit the loop and return the result
        if (x == wx && y == wy && z == chunkZ)
        {
            cout << "tried to spawn a plant where another plant is alread positioned" << endl;
            return true;
        }
    }

    //if no matches were found, the code got to this point so return false
    return false;
}