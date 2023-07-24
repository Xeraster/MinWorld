#ifndef PLAYERINFO_H
#define PLAYERINFO_H

//i had to make these global to avoid an error that said "use of deleted function ‘playerInfo& playerInfo::operator=(playerInfo&&)"
//this program is so dumb that its causing gcc to break apart at the seams
const double MAXZOOMLEVEL = 50000;      //the closest the player is allowed to zoom in
const double MINZOOMLEVEL = 0.01;       //the furthest the player is allowed to zoom out

extern const Uint8 *lastKey;
class playerInfo
{
    public:
        playerInfo();
        playerInfo(planet *startPlanet, double startX, double startY);

        //sets the planet to whatever
        void setPlanet(planet *whatever)
        {
            m_viewPlanet = whatever;
        }

        double getPlayerPosX() const { return m_posX; }
        double getPlayerPosY() const { return m_posY; }
        double getPlayerPosZ() const { return m_posZ; }

        double getZoomAmt() const { return m_zoomAmt; }
        int getZlevel() const { return m_zLevel; }

        void getLookedAtChunkNumber(int *chunkPosX, int *chunkPosY);
        void managePlayerInput(int mouseX, int mouseY, Uint32 lastMouse);

        void setSeed(int number) { m_seed = number; }
        int getSeed() const { return m_seed; }

        //takes mouse position and converts it to work position
        positionEntry getWorldPosOfMouse(int mouseX, int mouseY, double cameraZoom);

        void renderPlayerScreen();

    private:
        //draws everything
        void drawPlanetComplete(int zLevel, double zoomAmt);

        //draws chunks but does so in a minimal way. Intended for a world map mode
        void drawPlanetMinimal(int zLevel, double zoomAmt);

        //returns true if provided chunk is/should be on the screen or not. Works even if chunk is uninitialized
        bool isChunkOnScreen(chunk *theChunk);

        //the maximum number of chunks that can fit on the screen on the x axis at the current zoom level and screen size
        double maxChunksOnScreenX();

        //the maximum number of chunks that can fit on the screen on the y axis at the current zoom level and screen size
        double maxChunksOnScreenY();

        //player's viewing position
        //unlike dwarf fortress, the player can move "between tiles" to get a more smooth feel to the movement. world sizes are very big. Hopefully doubles are good enough
        double m_posX;
        double m_posY;
        double m_posZ;
        planet* m_viewPlanet;
        bool m_mapMode; //if in "map mode" the contents of each biome are just a solid color and none of the graphics are rendered.

        //random seed to use when generating stuff
        int m_seed;

        //ui stuff
        double m_zoomAmt;
        int m_zLevel;
        double multFactor;//exponential zoom housekeeping variable
};

#include "playerInfo.hpp"
#endif