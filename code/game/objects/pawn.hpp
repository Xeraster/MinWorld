pawn :: pawn()
{

}

//overload for spawning a thing from thing type pointer
pawn :: pawn(pawnType *thePawn, int x, int y, int z, int seed)
{
    m_type = thePawn;
    m_posX = x;
    m_posY = y;
    m_posZ = z;

    m_stack = 1;//set to 1, pawns can't be stacked
    m_health = m_type->hitPoints();
    m_onFire = false;
    m_interacted = false;
    m_rotation = 0.0f; //only buildings, weapons, apparel, pawns and corpses can do rotation

    m_state.m_isAlive = true;
    m_growthProgress = 1.0f;//for now just lock it to 1.0

    populateNeeds();
}

//copy constructor
pawn :: pawn(const pawn& rhs)
{
    //thing specific stuff (since pawn extends thing)
    m_posX = rhs.getPosX();
    m_posY = rhs.getPosY();
    m_posZ = rhs.getPosZ();
    m_stack = 1;    //pawns don't "stack"
    m_health = rhs.getPawnType()->hitPoints();
    m_onFire = rhs.fire();
    m_rotation = rhs.getRotation();
    m_interacted = rhs.interacted();

    //pawn specific stuff
    m_type = rhs.getPawnType();
    m_state = rhs.getPawnState();
    m_controls = rhs.getPawnControls();
    m_growthProgress = rhs.getGrowthProgress();

    //still need to copy over needs and inventory
    m_needs.clear();
    for (int i = 0; i < rhs.numPawnNeeds(); i++)
    {
        //copy all the needs in the rhs pawn's vector to this pawn
        m_needs.push_back(rhs.getNeedAt(i));
    }

    //todo: do the same for inventory (when I implement it)

}

//equals operator
pawn pawn :: operator=(const pawn& rhs)
{
    //thing specific stuff (since pawn extends thing)
    m_posX = rhs.getPosX();
    m_posY = rhs.getPosY();
    m_posZ = rhs.getPosZ();
    m_stack = 1;    //pawns don't "stack"
    m_health = rhs.getPawnType()->hitPoints();
    m_onFire = rhs.fire();
    m_rotation = rhs.getRotation();
    m_interacted = rhs.interacted();

    //pawn specific stuff
    m_type = rhs.getPawnType();
    m_state = rhs.getPawnState();
    m_controls = rhs.getPawnControls();
    m_growthProgress = rhs.getGrowthProgress();

    //still need to copy over needs and inventory
    m_needs.clear();
    for (int i = 0; i < rhs.numPawnNeeds(); i++)
    {
        //copy all the needs in the rhs pawn's vector to this pawn
        m_needs.push_back(rhs.getNeedAt(i));
    }

    //todo: do the same for inventory (when I implement it)

    //return *this because that's what you do for operator=
    return *this;
}

//clears whatever is in m_needs and reapplys them from pawnTYpe
void pawn :: populateNeeds()
{
    //first, clear them
    m_needs.clear();

    //load them all to this pawn object
    for (int i = 0; i < m_type->numNeeds(); i++)
    {
        //TODO: Get a copy constructor and all the required stuff to get this to work
        need newNeed = need(m_type->getNeedAt(i), 69420+i);
        m_needs.push_back(newNeed);
        //m_type->getNeedAt(i)
    }

    cout << m_needs.size() << " needs have been added to pawn instance with a def of " << m_type->defname() << endl;
}

//call this to draw the pawn to the screen. Since I'll almost certainly have to do some arcane c++ sorcery to make this work as modularly as in similar c# based games, it's very important that the function names and overloads match that of the thing class
void pawn :: drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel)
{
    //calculate all the position values
    int screenPosX = m_posX - playerCameraX;
    int screenPosY = m_posY - playerCameraY;

    //do whatever this is
    int drawposX = ((screenPosX) * zoomLevel) + (gscreenx / 2);
    int drawposY = ((screenPosY) * zoomLevel) + (gscreeny / 2);

    //if player z level is same as the object's zlevel
    if (playerCameraZ+50 == m_posZ)
    {
        //designate a mask pointer and a texture pointer
        SDL_Texture *textureToUse = m_type->getTextureByRotation(m_rotation);
        SDL_Texture *textureToUseMask = m_type->getMaskByRotation(m_rotation);

        //assign texture pointer based on rotation


        if (m_type->maskInFront())
        {
            //draw the normal texture and then the "mask" (which I guess isn't a real mask but whatever)
            renderTextureEx(textureToUse, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation);
            if (textureToUseMask != nullptr)
            {
                renderTextureAndMask(textureToUseMask, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation, m_type->skinColor());
            }
        }
        else
        {
            //draw the "mask" first and then the normal texture
            if (textureToUseMask != nullptr)
            {
                renderTextureAndMask(textureToUseMask, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation, m_type->skinColor());
            }
            renderTextureEx(textureToUse, ren, drawposX, drawposY, zoomLevel, zoomLevel, m_rotation);
        }
    }
}

//this gets run once per tick.
void pawn :: tickThing(unsigned int seed)
{
    //lol this is going to be a huge pain

    //uuuh I have to make a lot more objects and write a lot more code before pawns can be autonomous lol

    //update the pawnState with everything
    //hmm maybe all the "pawn driving" should be done in pawn after all

}

//run this on tick to decrement needs at the correct rate
void pawn :: tickNeeds()
{
    
}