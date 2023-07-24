thing :: thing()
{
    m_type = nullptr;
}

//overload for spawning a thing from thing type pointer
thing :: thing(thingType *theThing, int x, int y, int z, int seed)
{
    m_type = theThing;
    m_posX = x;
    m_posY = y;
    m_posZ = z;

    m_stack = 1;
    m_health = m_type->hitPoints();
    m_onFire = false;
    m_interacted = false;
    m_rotation = 0.0f; // things don't do rotation. only buildings, weapons, apparel, pawns and corpses can do rotation
}

//modifies the number of things in this stack. returns 0 if success. returns 1 if failed for some reason
int thing :: setStackSize(int newAmt)
{
    if (newAmt <= m_type->maxStackSize() && newAmt > 0)
    {
        m_stack = newAmt;
        return 0;
    }
    else if (newAmt == 0)
    {
        m_stack = newAmt;
        cout << "warning: tried to set stack size of thing of type " << m_type->defName() << " to 0. This is not allowed, you should be deleting the thing instead of setting its stack sie to zero." << endl;
        return 1;
    }
    else
    {
        m_stack = newAmt;
        cout << "warning: tried to set invalid stack amount for thing of type " << m_type->defName() << ". The requested size was " << newAmt << " and the max stack size of this item is " << m_type->maxStackSize() << endl;
        return 1;
    }
}

//draws the stack quantity label below any thing. Recommended for use on any child thing that uses stack sizes
void thing :: drawQtyLabel(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    int screenPosX = m_posX - playerCameraX;
    int screenPosY = m_posY - playerCameraY;
    int drawposX = ((screenPosX) * zoomLevel) + (gscreenx / 2);
    int drawposY = ((screenPosY) * zoomLevel) + (gscreeny / 2);

    drawText(ren, 8, color(200, 200, 200), to_string(m_stack) ,drawposX, drawposY);
}

void thing :: drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    //cout << "test" << endl;
    int screenPosX = m_posX - playerCameraX;
    int screenPosY = m_posY - playerCameraY;

    int drawposX = ((screenPosX) * zoomLevel) + (gscreenx / 2);
    int drawposY = ((screenPosY) * zoomLevel) + (gscreeny / 2);

    if (playerCameraZ+50 == m_posZ/* || (m_posZ == 50 && playerCameraZ > m_posZ)*/)
    {
        //cout << "m_stack = " << m_stack;
        SDL_Texture *textureToUse;
        SDL_Texture *textureToUseMask;

        // do this if stack size = 1 OR item doesn't use the 1-2-3 texture convention
        if (!m_type->usesTexStack() || m_stack == 1)
        {
            textureToUse = m_type->getThingTex();
            textureToUseMask = m_type->getMaskTex();
            //cout << " using tex A" << endl;
        }
        else if (m_stack == m_type->maxStackSize())
        {
            textureToUse = m_type->getThingTexC();
            textureToUseMask = m_type->getMaskTexC();
            //cout << " using tex C" << endl;
        }
        else
        {
            textureToUse = m_type->getThingTexB();
            textureToUseMask = m_type->getMaskTexB();
            //cout << " using tex B" << endl;
        }

        if (m_type->maskInFront())
        {
            //draw the normal texture and then the "mask" (which I guess isn't a real mask but whatever)
            renderTextureEx(textureToUse, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation);
            if (textureToUseMask != nullptr)
            {
                renderTextureAndMask(textureToUseMask, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation, m_type->getStuffColor());
            }
        }
        else
        {
            //draw the "mask" first and then the normal texture
            if (textureToUseMask != nullptr)
            {
                renderTextureAndMask(textureToUseMask, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation, m_type->getStuffColor());
            }
            renderTextureEx(textureToUse, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation);
        }
    }

    drawQtyLabel(ren, win, playerCameraX, playerCameraY, playerCameraZ, zoomLevel);
}

//=======================================================================
//plant related stuff
//=======================================================================

plant :: plant()
{
    
}

plant :: plant(string typeDef, int x, int y, int z, int seed)
{
    m_type = getPlantTypeByDefName(typeDef);

    m_posX = x;
    m_posY = y;
    m_posZ = z;

    //growth progress to float in steps of 1/1000ths
    m_growthProgress = (betterRand(seed) % 1000) / 1000.0f;
    m_stack = 1;
    m_health = m_type->hitPoints();
    m_onFire = false;
    m_interacted = false;
    m_rotation = 0.0f; // plants can't do rotation
}

plant :: plant(plantType *thePlant, int x, int y, int z, int seed)
{
    m_type = thePlant;

    m_posX = x;
    m_posY = y;
    m_posZ = z;

    //growth progress to float in steps of 1/1000ths
    m_growthProgress = (betterRand(seed) % 1000) / 1000.0f;
    //cout << "plant growth = " << m_growthProgress << endl;
    m_stack = 1;
    m_health = m_type->hitPoints();
    m_onFire = false;
    m_interacted = false;
    m_rotation = 0.0f; // plants can't do rotation
}

void plant :: drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    int screenPosX = m_posX - playerCameraX;
    int screenPosY = m_posY - playerCameraY;
    //cout << playerCameraZ << endl;

    if (playerCameraZ+50 == m_posZ/* || (m_posZ == 50 && playerCameraZ > m_posZ)*/)
    {
        SDL_Texture *textureToUse;
        if (m_growthProgress > 0.67f)
        {
            textureToUse = m_type->getTex();
        }
        else
        {
            textureToUse = m_type->getGrowTex();
        }
        renderTextureEx(textureToUse, ren, (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2), zoomLevel, zoomLevel, 0);
    }
    //cout << "draw plant at pos " << (screenPosX*zoomLevel) + (gscreenx/2) << "," << (screenPosY*zoomLevel) + (gscreeny/2) << endl;
}

//=======================================================================
//building related stuff
//=======================================================================

//overload for creating a thing of type building from a given buildingType def name
building :: building(string typeDef, int x, int y, int z, int seed)
{
    m_type = getBuildingTypeByDefName(typeDef);
    m_posX = x;
    m_posY = y;
    m_posZ = z;

    m_rotation = 0.0f; // if no rotation specified, set to zero

    m_madeFromStuff = (buildingType *)m_type->isMadeFromStuff();
    m_stack = 1;
    m_health = m_type->hitPoints();
    m_onFire = false;
}

//overload for creating a thing of type building from a given buildingType pointer
building :: building(buildingType *theBuilding, int x, int y, int z, int seed)
{
    m_type = theBuilding;
    m_posX = x;
    m_posY = y;
    m_posZ = z;

    m_rotation = 0.0f; // if no rotation specified, set to zero

    m_madeFromStuff = (buildingType *)m_type->isMadeFromStuff();
    m_stack = 1;
    m_health = theBuilding->hitPoints();
    m_onFire = false;
}

/*maybe this will solve the bullshit "variables not holding value" problem
i think maybe this is what vector push back looks for*/
building :: building(const building &rhs)
{
    cout << "TEST: Code is in building object intantiation copy constructor" << endl;
    m_posX = rhs.getPosX();
    m_posY = rhs.getPosY();
    m_posZ = rhs.getPosZ();

    m_rotation = rhs.getRotation();
    m_stack = rhs.stack();
    m_health = rhs.health();
    m_onFire = rhs.fire();

    m_madeFromStuff = rhs.madeFromStuff();
    m_type = rhs.getType();
}

void building :: drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    float screenPosX = m_posX - playerCameraX;
    float screenPosY = m_posY - playerCameraY;
    //cout << playerCameraZ << endl;

    int rot = getRotation();
    int sizex = m_type->footprintX();
    int sizey = m_type->footprintY();


    float yAdjust = 0;
    float xAdjust = 0;

    //draw a testing boundary box
     if (rot == 270 || rot == 90)
    {
        drawRect(ren, color(100, 100, 100), (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2), (zoomLevel * sizey), (zoomLevel * sizex));

        //if thing is rotated at a 90-degree like angle, position needs to be adjusted
        xAdjust = -1.0f / static_cast<float>(sizey);
        yAdjust = -xAdjust;
        //yAdjust = 
        //cout << "xAdjust=" << xAdjust << endl;
    }
    else
    {
        drawRect(ren, color(100, 100, 100), (screenPosX * zoomLevel) + (gscreenx / 2), (screenPosY * zoomLevel) + (gscreeny / 2), (zoomLevel * sizex), (zoomLevel * sizey));

        //0 or 180, no rotational position adjustment is needed
    }

    //positioning starts getting complicated due to a) rotation and b) sizes larger than 1 tile
    int drawposX = ((screenPosX + xAdjust) * zoomLevel) + (gscreenx / 2);
    int drawposY = ((screenPosY + yAdjust) * zoomLevel) + (gscreeny / 2);
    int drawSizeX = zoomLevel * sizex;
    int drawSizeY = zoomLevel * sizey;

    //cout << "rotation of thing of type " << m_type->defName() << " is " << m_rotation << endl;

    if (m_type->maskInFront())
    {
        //draw the normal texture and then the "mask" (which I guess isn't a real mask but whatever)
        renderTextureEx(m_type->getTex(), ren, drawposX, drawposY, drawSizeX, drawSizeY, rot);
        if (m_type->getMaskTex() != nullptr)
        {
            renderTextureAndMask(m_type->getMaskTex(), ren, drawposX, drawposY, drawSizeX, drawSizeY, rot, color(0xa8, 0x8f, 0x59));
        }
    }
    else
    {
        //draw the "mask" first and then the normal texture
        if (m_type->getMaskTex() != nullptr)
        {
            renderTextureAndMask(m_type->getMaskTex(), ren, drawposX, drawposY, drawSizeX, drawSizeY, rot, color(0xa8, 0x8f, 0x59));
        }
        renderTextureEx(m_type->getTex(), ren, drawposX, drawposY, drawSizeX, drawSizeY, rot);
    }


}

building& building :: operator=(const building& other)
{
    cout << "TEST: Code is in building copy constructor" << endl;
    m_posX = other.getPosX();
    m_posY = other.getPosY();
    m_posZ = other.getPosZ();

    m_rotation = other.getRotation();
    m_stack = other.stack();
    m_health = other.health();
    m_onFire = other.fire();

    m_madeFromStuff = other.madeFromStuff();
    m_type = other.getType();

    return *this;
}

//get a list of occupied tiles for this building
void building :: getOccupiedTiles(vector<positionEntry> *tiles)
{
    //it's trivial if the building has a rotation of either 0 or 180
    int rot = m_rotation;
    if (rot == 0 || rot == 180)
    {
        cout << "building of type " << m_type->defName() << "occupies the following tiles: ";
        for (int x = 0; x < m_type->footprintX(); x++)
        {
            for (int y = 0; y < m_type->footprintY(); y++)
            {
                positionEntry thisPosition;
                thisPosition.posX = m_posX + x;
                thisPosition.posY = m_posY + y;
                thisPosition.posZ = m_posZ;         //for now, all buildings can only be 1 block high on the z axis
                tiles->push_back(thisPosition);
                cout << thisPosition.posX << "," << thisPosition.posY << "," << thisPosition.posZ << "  ";
            }
        }
        cout << endl;
    }
    //if building is rotated 90 or 270, it's a little bit more invovled
    else
    {
        cout << "building of type " << m_type->defName() << "occupies the following tiles: ";
        for (int x = 0; x < m_type->footprintY(); x++)
        {
            for (int y = 0; y < m_type->footprintX(); y++)
            {
                positionEntry thisPosition;
                thisPosition.posX = m_posX + x;
                thisPosition.posY = m_posY + y;
                thisPosition.posZ = m_posZ;         //for now, all buildings can only be 1 block high on the z axis
                tiles->push_back(thisPosition);
                cout << thisPosition.posX << "," << thisPosition.posY << "," << thisPosition.posZ << "  ";
            }
        }
        cout << endl;
    }
}