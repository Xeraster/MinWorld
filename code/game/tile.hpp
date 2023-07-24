tile :: tile()
{
    
}

//returns true if terrain tile is anything other than the null sky block
bool tile :: isRealBlock()
{
    if (terrainTile == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void tile :: drawTile(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    //int screenPosX = playerCameraX - m_xpos;
    //int screenPosY = playerCameraY - m_ypos;
    int screenPosX = m_xpos - playerCameraX;
    int screenPosY = m_ypos - playerCameraY;

    //cout << "x=" << screenPosX << "y=" << screenPosY << endl;
    //cout << "xpos=" << m_xpos << "ypos=" << m_ypos << endl;
    renderTextureEx(terrainTile->getTex(), ren, (screenPosX*zoomLevel) + (gscreenx/2), (screenPosY*zoomLevel) + (gscreeny/2), zoomLevel, zoomLevel, 0);
}

//returns how suitable for farming this tile is
float tile :: getFertilityOfTile()
{
    if (terrainTile != nullptr)
    {
        //support of 0 or less is water or something
        if (terrainTile->support() >= 0 && terrainTile->defName() != "SkyBlock" && terrainTile->defName() != "Water")
        {
            return terrainTile->fertility();
        }
        else
        {
            return 0.0f;
        }
    }
    else
    {
        return 0.0f;
    }
}