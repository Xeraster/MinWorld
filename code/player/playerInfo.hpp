playerInfo :: playerInfo()
{
    //nothing is set up yet, yays
    m_posX = 0;
    m_posY = 0;
    m_posZ = 0.0f;

    //default view settings
    m_zoomAmt = 20.0f;
    m_zLevel = 0;
    multFactor = 1;
}

playerInfo :: playerInfo(planet *startPlanet, double startX, double startY)
{
    m_viewPlanet = startPlanet;
    m_posX = startX;
    m_posY = startY;
    m_posZ = 0.0f;

    //default view settings
    m_zoomAmt = 20.0f;
    m_zLevel = 0;
    multFactor = 1;
}

void playerInfo :: getLookedAtChunkNumber(int *chunkPosX, int *chunkPosY)
{
    *chunkPosX = m_posX / m_viewPlanet->getSizeX();
    *chunkPosY = m_posY / m_viewPlanet->getSizeY();
}

void playerInfo :: managePlayerInput(int mouseX, int mouseY, Uint32 lastMouse)
{
    //go up (W) or down (S)?
    if (lastKey[SDL_SCANCODE_W])
    {
        m_posY -= 1.0f;
    }
    else if (lastKey[SDL_SCANCODE_S])
    {
        m_posY += 1.0f;
    }
    
    //go left (A) or right (D)?
    if (lastKey[SDL_SCANCODE_A])
    {
        m_posX -= 1.0f;
    }
    else if (lastKey[SDL_SCANCODE_D])
    {
        m_posX += 1.0f;
    }

    //I really need to get a better way of doing toggle keys, this is a crude testing way and it sucks
    if (lastKey[SDL_SCANCODE_M])
    {
        //toggle map mode
        m_mapMode = !m_mapMode;
        cout << "m_mapMode = " << boolToString(m_mapMode) << endl;
    }

    //zlevel and zoom handling
    if (wheelUp && lastKey[SDL_SCANCODE_LCTRL])
    {
        m_zLevel++;
    }
    else if (wheelDown && lastKey[SDL_SCANCODE_LCTRL])
    {
        m_zLevel--;
    }
    //all of the view zooming has to generally conform to integer values in order to look right
    else if (wheelUp && m_zoomAmt <= MAXZOOMLEVEL)
    {
        m_zoomAmt+=multFactor;
        //if number too high, clamp it to max
        if (m_zoomAmt > MAXZOOMLEVEL)
        {
            m_zoomAmt = MAXZOOMLEVEL;
        }
    }
    else if (wheelDown && m_zoomAmt >= MINZOOMLEVEL)
    {
        m_zoomAmt-=multFactor;
        //if number too low, clamp it to min
        if (m_zoomAmt < MINZOOMLEVEL)
        {
            m_zoomAmt = MINZOOMLEVEL;
        }
    }

    multFactor = 0.1f*m_zoomAmt/0.5f;
    if (multFactor < 0.2f)
    {
        multFactor = 0.2f;
    }

    //you really can't have non integer values at closer zooms
    if (m_zoomAmt > 4.0f)
    {
        multFactor = floor(multFactor);
        m_zoomAmt = floor(m_zoomAmt);

        //sometimes multFactor gets rounded to 0 in the far to near zoom transition period
        if (multFactor < 1.0f)
        {
            multFactor = 1.0f;
        }
    }
    

    //should I reeally be rendering the planet from the player input function?
    //drawPlanetComplete();
    //guess not
}

//takes mouse position and converts it to work position
positionEntry playerInfo :: getWorldPosOfMouse(int mouseX, int mouseY, double cameraZoom)
{
    //get looked at chunk number first
    int cx; //chunk x position
    int cy; //chunk y position

    //figure out which chunk the player is looking at
    //getLookedAtChunkNumber(&cx, &cy);

    positionEntry returnEntry;
    //returnEntry.posZ = m_posZ;      //z position = whatever z level the player view is set to
    //chunkWorldX = GLOBAL_TILES_PERCHUNK * cx;

    //at zoom level 1 at a resolution of 800x600, tile layout is 40x30
    //that means its 20 pixels per tile at zoom = 1.0f
    returnEntry.posX = (m_posX) + ((mouseX-(gscreenx/2))/m_zoomAmt);
    returnEntry.posY = (m_posY) + ((mouseY-(gscreeny/2))/m_zoomAmt);
    returnEntry.posZ = m_posZ;      //z position = whatever z level the player view is set to

    return returnEntry;
}

void playerInfo :: drawPlanetComplete(int zLevel, double zoomAmt)
{
    int chunkx;
    int chunky;
    getLookedAtChunkNumber(&chunkx, &chunky);
    m_viewPlanet->loadChunksBasedOnPosition(chunkx, chunky);

    for (int i = 0; i < m_viewPlanet->loadedChunks.size(); i++)
	{
		m_viewPlanet->loadedChunks.at(i)->drawChunk(ren, win, getPlayerPosX(), getPlayerPosY(), m_zLevel, m_zoomAmt);
	}
}

void playerInfo :: drawPlanetMinimal(int zLevel, double zoomAmt)
{
    //if (isChunkOnScreen(&m_viewPlanet->getChunk(5, 50)))
    //{
    //    cout << "chunk is on screen" << endl;
    //}
    //m_viewPlanet->getChunk(5, 50).drawUninitialisedChunk(ren, win, getPlayerPosX(), getPlayerPosY(), m_zLevel, m_zoomAmt, m_viewPlanet->TILESPERCHUNK);

    //instead of looping through every single chunk, only loop through what could be displayed on the screen + a few more.
    //get the number of the chunk that the player is looking at
    int chunkx;
    int chunky;
    getLookedAtChunkNumber(&chunkx, &chunky);
    int chunksXdir = maxChunksOnScreenX() + 2; //2 more than maximum chunks on the screen in the x direction
    int chunksYdir = maxChunksOnScreenY() + 2; //2 more than the maximum chunks on the screen in the y direction

    //figure out the mins and maxs
    int startx = chunkx - chunksXdir;
    int endx = chunkx + chunksXdir;
    int starty = chunky - chunksYdir;
    int endy = chunky + chunksYdir;

    //if any mins or maxs are out of bounds, clamp them to be in-bounds
    if (startx < 0) startx = 0;
    if (endx > m_viewPlanet->TILESPERCHUNK) endx = m_viewPlanet->TILESPERCHUNK;
    if (starty < 0) starty = 0;
    if (endy > m_viewPlanet->TILESPERCHUNK) endy = m_viewPlanet->TILESPERCHUNK;

    //for (int x = 0; x < m_viewPlanet->TILESPERCHUNK; x++)
    for (int x = startx; x < endx; x++)
    {
        //for(int y = 0; y < m_viewPlanet->TILESPERCHUNK; y++)
        for(int y = starty; y < endy; y++)
        {
            if (isChunkOnScreen(&m_viewPlanet->getChunk(x, y)))
            {
                //cout << "chunk is on screen" << endl;
                m_viewPlanet->getChunk(x, y).drawUninitialisedChunk(ren, win, getPlayerPosX(), getPlayerPosY(), m_zLevel, m_zoomAmt, m_viewPlanet->TILESPERCHUNK);
            }
        }
    }
    //it could still be better. Just because it runs well on a Ryzen 5 doesn't mean it'll run well on an Athlon Xp
}

//returns true if provided chunk is/should be on the screen or not. Works even if chunk is uninitialized
bool playerInfo :: isChunkOnScreen(chunk *theChunk)
{
    //based on this
    //drawRectFilled(ren, getColor(), (screenPosX*zoomLevel) + (gscreenx/2), (screenPosY*zoomLevel) + (gscreeny/2), zoomLevel*tilesPerChunk, zoomLevel*tilesPerChunk);

    //the compiler probably automatically does this optimization i doubt it matters
    int tilesPerChunk = theChunk->getChunkSideSize();

    //yay, more floating point operations to waste cpu time doing
    int screenPosX = (theChunk->getPosX()*tilesPerChunk) - getPlayerPosX();
    int screenPosY = (theChunk->getPosY()*tilesPerChunk) - getPlayerPosY();

    //i really really don't think this is suitable for running on all 100x100 chunks in a world on each frame. there's just no way.
    //fortunately there are better ways to use this function besides just checking every single loaded chunk
    if ((screenPosX*m_zoomAmt) + (gscreenx/2) > gscreenx)
    {
        return false;
    }
    else if((screenPosX*m_zoomAmt) + (gscreenx/2) + m_zoomAmt*tilesPerChunk < 0)
    {
        return false;
    }
    else if ((screenPosY*m_zoomAmt) + (gscreeny/2) > gscreeny)
    {
        return false;
    }
    else if((screenPosY*m_zoomAmt) + (gscreeny/2) + m_zoomAmt*tilesPerChunk < 0)
    {
        return false;
    }

    //seems to be working
    //cout << "max chunks x = " << maxChunksOnScreenX() << endl;
    //cout << "max chunks y = " << maxChunksOnScreenY() << endl;

    return true;
}

//the maximum number of chunks that can fit on the screen on the x axis at the current zoom level and screen size
double playerInfo :: maxChunksOnScreenX()
{
    //how many tiles are in 1 chunk
    int tileschunk = m_viewPlanet->TILESPERCHUNK;

    //figure out the size of the chunks in pixels
    int chunkScreenSize = m_zoomAmt*tileschunk;

    return static_cast<double>(gscreenx)/static_cast<double>(chunkScreenSize);
}

//the maximum number of chunks that can fit on the screen on the y axis at the current zoom level and screen size
double playerInfo :: maxChunksOnScreenY()
{
    int tileschunk = m_viewPlanet->TILESPERCHUNK;

    //figure out the size of the chunks in pixels
    int chunkScreenSize = m_zoomAmt*tileschunk;

    return static_cast<double>(gscreeny)/static_cast<double>(chunkScreenSize);
}

void playerInfo :: renderPlayerScreen()
{
    //if not in map mode, render entire chunk
    if (!m_mapMode)
    {
        drawPlanetComplete(m_zLevel, m_zoomAmt);
    }
    //if not in map mode, only render chunks minimally
    else
    {
        drawPlanetMinimal(m_zLevel, m_zoomAmt);
    }

    //draw the ui stuff
    string timeDateString = printPlanetDateTime();
    drawText(ren, textSizeExtraSmall, color(255,255,255), printPlanetDateTime(), gscreenx - getTextXSize(textSizeSmall, timeDateString.length()), gscreeny - 100);
}

void playerInfo :: doPlayerTick()
{
    //cout << m_viewPlanet->getDaysInYear() << endl;
    m_viewPlanet->doTick();
}

//takes the planet's date and time and parses it into a string
string playerInfo :: printPlanetDateTime()
{
    //only do it if there's a valid planet being pointed to
    if (m_viewPlanet != nullptr)
    {
        string theString = to_string(m_viewPlanet->getDateTime().hour) + "H ";
        theString += "Day: " + to_string(m_viewPlanet->getDateTime().day);
        theString += "  Y: " + to_string(m_viewPlanet->getDateTime().year);

        return theString;
    }
    else
    {
        return "nullptr error";
    }
}