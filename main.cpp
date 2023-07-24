#include "code/xml/tinyxml2.h" 				//tinyxml2 for xml support
#include "code/xml/tinyxml2.cpp" 			//tinyxml2 for xml support

#include "SDL2/SDL.h" 						//SDL for graphics, font and image scaling
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

//graphical rendering will never be threaded so i'm making win and ren global this time around
SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture *tex;

//std stuff
//============================================

#include <iostream>
#include <thread>
#include <cstdlib>
#include <time.h>
#include <string>
#include <math.h>
#include <fstream>
#include <filesystem>
using namespace std;
using namespace tinyxml2;

#include <tgmath.h>
#include <vector>
#include <list>
#include <type_traits>

//===========================================

#include "code/color.h"
#include "code/LTimer.h"
#include "code/coloredString.h"
#include "code/randomFunctions.h"

//a basic position struct you can use for general purpose reasons
struct positionEntry
{
	int posX;
	int posY;
	int posZ;
};

#include "code/game/objects/thingType.h"
#include "code/game/objects/thing.h"

const int GLOBAL_TILES_PERCHUNK = 100;
#include "code/textureEntry.h"
#include "code/game/terrain.h"
//#include "code/game/plant.h"
#include "code/game/biome.h"
#include "code/game/tile.h"
#include "code/game/chunk.h"
#include "code/game/planet.h"

//user input globals
bool canClickMouse = true;
const Uint8 *lastKey = SDL_GetKeyboardState(NULL);
bool wheelUp = false;
bool wheelDown = false;
#include "code/player/playerInfo.h"

#include "code/button.h"
#include "code/devConsole.h"
SDL_Event testEvent;//this needs to be under the devconsole include and above the menus include
playerInfo playerData;
#include "code/menus.h"

//whatever the current screen resolution is
int gscreenx = 800;
int gscreeny = 600;

//framerate tracking globals
LTimer fpsTimer;
LTimer capTimer;
string timeText;
const int SCREEN_FPS = 60;
const double SCREEN_TICKS_PER_SECOND = 60;
const int SCREEN_TICKS_PER_FRAME = SCREEN_TICKS_PER_SECOND / SCREEN_FPS;
int countedFrames = 0;
char s[256];

//game state globals
bool exitGame = false;



//initialize the dev console
devConsole console;

//the info for the player and stuff
planet newPlanet;
buildingType *testBuilding;

//the game update function
void update();

int main()
{
    /* initialize random seed: */
	int testSeed = 69420;
  	srand (time(NULL));

    cout << "test" << endl;

    //initialize the SDL renderer
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	TTF_Init();
	win = SDL_CreateWindow("MinWorld", 100, 100, gscreenx, gscreeny, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//SDL_SetWindowResizable(win, SDL_TRUE);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	//SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//tell the dev console what the screen size is
	console.setScreenSize(screenSizeX(win), screenSizeY(win));

	//load the fonts into ram
	loadFonts();

	//enable blending. May be useful to add option to disable blending for better performance
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	//time to print out sdl renderer info
	cout << "number of render drivers = " << SDL_GetNumRenderDrivers() << endl;

	//set up the main menu
	setupMainMenu();

	//achieving the correct load order is everything

	cout << "get ready for a possible crash" << endl;
	loadAllThingTypes(ren);
	cout << "there are " << thingTypeDatabase.size() << " thing types loaded in the thingType database" << endl;

	loadAllTerrain(ren);
	//loadAllPlants(ren);
	loadAllBiomes(ren);

	cout << "making new planet" << endl;
	//planet newPlanet;
	newPlanet.setAvgTemp(4.0f);
	newPlanet.setDaysInYear(340);
	newPlanet.setTempVariance(25.0f);
	newPlanet.generateWorld(100, 100);
	newPlanet.setSeed(42069);

	cout << "the world is " << newPlanet.getWorldSizeX() << "x" << newPlanet.getWorldSizeY() << " tiles in size" << endl;

	playerData = playerInfo(&newPlanet, 555.0f, 5000.0f);
	playerData.setSeed(69420);

	//plant newPlant(getPlantTypeByDefName("Tree"), 20, 50, 1);
	thing newTest;

	/*std::string imagePath = "Textures/Qualifications/flak_gunner.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/

	//well well well, it has come to this
	//testBuilding = getBuildingTypeByDefName("Well");
	//color testColor("FF0000");


	fpsTimer.start();
	while (exitGame == false)
	{
		capTimer.start();
		update();   //update no longer has ren and win passed to it


		//Calculate and correct fps
        double avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.0f/*SCREEN_TICKS_PER_SECOND*/ );
        if( avgFPS > 2000000 )
        {
        	avgFPS = 0;
        }
        timeText = "FPS: " + to_string(avgFPS);

        // Update Title & Present Screen Buffer
		snprintf(s, 256, "MinWorld- FPS: %3.2f", avgFPS);
		SDL_SetWindowTitle(win, s);

		//handle all the events at the end of update even it there are many
		//SDL_Event testEvent;

		//there can only be 1 event handler per frame or else they will fight each other
		//this results in typing text being a pain in the ass and not working well since some keypressed don't seem to "register"
		//what is really happening is that there's no guarentee the keypress will register on the event handler you want
		//the more event handlers per frame, the worse the problem gets
		lastCharTyped = "";
		backspaceAsserted = false;
		enterAsserted = false;
		wheelDown = false;
		wheelUp = false;
		while (SDL_PollEvent(&testEvent) == 1)
		{
			if (testEvent.type == SDL_TEXTINPUT)
       	 	{
       	 		lastCharTyped = testEvent.text.text;
       	 	}

       	 	if (testEvent.type == SDL_MOUSEWHEEL)
       	 	{
       	 		//cout << "SDL mouse wheel event" << endl;
       	 		if (testEvent.wheel.y > 0) wheelUp = true;
       	 		else wheelDown = true;
       	 	}

			if (testEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				exitGame = true;
			}

			if (testEvent.type == SDL_WINDOWEVENT && testEvent.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				cout << "window resized to " << screenSizeX(win) << "," << screenSizeY(win) << endl;
				gscreenx = screenSizeX(win);
				gscreeny = screenSizeY(win);
				// screenSizeX(win), screenSizeY(win)
				// if window gets reizes, reset the gscreen globals and then call mainmenu's widget resize function

				on_resize();
			}
		}

		//const Uint8 *lastKey = SDL_GetKeyboardState(NULL);
		lastKey = SDL_GetKeyboardState(NULL);
    	//if (m_timeTillNextKey <= 0)
    	//{
    		if (lastKey[SDL_SCANCODE_BACKSPACE]) 
    		{
    			backspaceAsserted = true;
    		}
    		else if(lastKey[SDL_SCANCODE_RETURN] || lastKey[SDL_SCANCODE_KP_ENTER])
    		{
    			enterAsserted = true;
    		}
    	//}

		//this only deals with fps counting/tracking and does not control the framerate. Do not touch if you don't know what you're doing
		if (fpsTimer.getTicks() > SCREEN_TICKS_PER_SECOND * 3)
		{
			//cout << "fps ticks since last frame:" << fpsTimer.getTicks() << endl;
			fpsTimer.stop();
			fpsTimer.start();
			countedFrames = 0;
		}

		//figure out a way to make it delay if the entire frame was cmpleted in 16.6667 milliseconds or less
		//much like The Powder Toy, the framerate will be locked to 60fps.
		unsigned int msSinceLastFrame = capTimer.getTicks();//kinda sucks you only get millisecond integer precision. That's going to cost like a 4% performance hit at 60fps
		capTimer.stop();
		//since we can't check for 16.66667, check for 16. This means monitors with 60fps will run at 60fps but refresh rate settings higher than 60fps will run at 62.5 fps
		if (msSinceLastFrame < 16)
		{
			cout << "frame delay. Frame finished rendering in " << to_string(16-msSinceLastFrame) << "ms early" << endl;
			SDL_Delay(16-msSinceLastFrame);
			//whatever. At least I found a way to cap frames at 16ms instead of 17ms. 62.5 is a better framerate than 58.8235
		}

	}

	//the end of the game loop. This is where the deletion of sdl textures in every object type should go in order to prevent valgrind from complaining
	//I need for valgrind to report stuff that actually matters

	return 0;
}

//double zoomAmt = 20.0f;
//int zLevel = 0;
// the game update function
void update()
{
		//tick the planet. all the stuff happens during planet tick. try to only signal stuff in player tick rather than make changes. This will make threading work better and easier
		//newPlanet
	//thread test(deletePlayerTorpedos);
		//for drawing the selection box around the mouse
		int mouseBoxX = 80 * (screenSizeX(win)/800);
		int mouseBoxY = 60 * (screenSizeY(win)/600);

		string lastKeyPressed = "shut up";
		int mouseX, mouseY;
		Uint32 lastMouse = SDL_GetMouseState(&mouseX, &mouseY);

		/*if (lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && canClickMouse && zoomedOut && galaxyView && !aStarIsSelected)
		{
			lastKeyPressed = "left mouse is being pressed";
			canClickMouse = false;
			zoomedOut = false;
			largeZoomX = (mouseX - (mouseBoxX/2))+largeZoomX;
			largeZoomY = (mouseY - (mouseBoxY/2))+largeZoomY;
		}
		else if(lastMouse == SDL_BUTTON(SDL_BUTTON_LEFT) && canClickMouse && galaxyView && aStarIsSelected)
		{
			canClickMouse = false;
			solarSystemView = true;
			galaxyView = false;
		}

		if (lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && canClickMouse && !zoomedOut && galaxyView)
		{
			lastKeyPressed = "right mouse is being pressed";
			canClickMouse = false;
			zoomedOut = true;
			largeZoomX = largeZoomX-(screenSizeX(win)/2)+(mouseBoxX/2)-(mouseX - (screenSizeX(win)/2));
			largeZoomY = largeZoomY-(screenSizeY(win)/2)+(mouseBoxY/2)-(mouseY - (screenSizeY(win)/2));
		}
		else if (lastMouse == SDL_BUTTON(SDL_BUTTON_RIGHT) && canClickMouse && solarSystemView)
		{
			canClickMouse = false;
			galaxyView = true;
			solarSystemView = true;
			zoomedOut = false;
		}*/

		//if (!canClickMouse)
		//{
			//ticksSinceLastMouse++;
		//}

		if (!canClickMouse && lastMouse != SDL_BUTTON(SDL_BUTTON_LEFT) && lastMouse != SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			//ticksSinceLastMouse=0;
			canClickMouse = true;
		}

		//const Uint8 *lastKey = SDL_GetKeyboardState(NULL);

		//cout << "windowsize = " << screenSizeX(win) << "x" << screenSizeY(win) << endl;
		uint32_t bluh = 42069;


		//First clear the renderer
		SDL_RenderClear(ren);
		//drawRectFilled(ren, color(255, 0, 0, 10), 0, 0, gscreenx, gscreeny);

		// draw every loaded chunk
		
		/*if (wheelUp && lastKey[SDL_SCANCODE_LCTRL])
		{
			zLevel++;
		}
		else if (wheelDown && lastKey[SDL_SCANCODE_LCTRL])
		{
			zLevel--;
		}
		else if (wheelUp)
		{
			zoomAmt+= 1.0f;
		}
		else if (wheelDown)
		{
			zoomAmt -= 1.0f;
		}*/
		/*for (int i = 0; i < newPlanet.loadedChunks.size(); i++)
		{
			newPlanet.loadedChunks.at(i)->drawChunk(ren, win, playerData.getPlayerPosX(), playerData.getPlayerPosY(), zLevel, zoomAmt);
		}*/


		//uncomment to test biomes, terrains and plants.
		/*for (int i = 0; i < biomeDatabase.size(); i++)
		{
			drawText(ren, 8, color(255, 255, 255), biomeDatabase.at(i).defName(), 2, 50+(i * 20));
			for (int u = 0; u < biomeDatabase.at(i).terrainTypes.size(); u++)
			{
				renderTextureEx(biomeDatabase.at(i).terrainTypes.at(u).terrainType->getTex(), ren, 200 + (u * 50), 50 + (i * 20), 20, 20, 0);
			}
		}

		biome *testBiome = getBiomeByDefName("TemperateForest");
		for (int i = 0; i < testBiome->plantTypes.size(); i++)
		{
			int fontSize = 8 * gscreenx / 800;
			drawText(ren, fontSize, color(255, 255, 255), testBiome->plantTypes.at(i).plantType->defName(), 50, 300 + (i * 30));
			renderTextureEx(testBiome->plantTypes.at(i).plantType->getTex(), ren, 200, 300 + (i * 30), 30, 30, 0);
		}*/

		//is user in game or in the main menus?
		if (normalInGame)
		{
			playerData.managePlayerInput(mouseX, mouseY, lastMouse);
			playerData.renderPlayerScreen();

			//manage the console
			console.draw(ren, mouseX, mouseY, lastMouse, screenSizeX(win), screenSizeY(win));

			//all the debug information that may be useful
			drawText(ren, 8, color(255,255,255), timeText, 2, 0);
			drawText(ren, 8, color(255,255,255), "mouse=" + to_string(mouseX) + "x" + to_string(mouseY), 2, 20);
			positionEntry mouseToWorld = playerData.getWorldPosOfMouse(mouseX, mouseY, playerData.getZoomAmt());
			drawText(ren, 8, color(255, 255, 255), "world pos:" + to_string(playerData.getPlayerPosX()) + "," + to_string(playerData.getPlayerPosY()) + " (" + to_string(mouseToWorld.posX) + "," + to_string(mouseToWorld.posY) + "," + to_string(mouseToWorld.posZ) + ")", 2, 40);
			drawText(ren, 8, color(255,255,255), "loaded chunks:" + to_string(newPlanet.loadedChunks.size()), 2, 80);
			drawText(ren, 8, color(255,255,255), "z level:" + to_string(playerData.getZlevel()), 2, 100);
			drawText(ren, 8, color(255,255,255), "zoomAmt=" + to_string(playerData.getZoomAmt()), 2, 120);

			int chunkx;
			int chunky;
			playerData.getLookedAtChunkNumber(&chunkx, &chunky);
			drawText(ren, 8, color(255,255,255), "chunkNum:" + to_string(chunkx) + "," + to_string(chunky), 2, 60);
		}
		else
		{
			//still allow the console even in main menu mode
			console.draw(ren, mouseX, mouseY, lastMouse, screenSizeX(win), screenSizeY(win));

			//render the main menus
			drawMenus(mouseX, mouseY, lastMouse);
		}

		//terrainDatabase.front().testDraw(ren, win);

		//renderTextureEx(testBuilding->getTex(), ren, 300, 300, 128, 128, 0);
		//renderTextureAndMask(testBuilding->getTex(), ren, 300, 300, 128, 128, 0, testBuilding->getMaskTex(), color(0, 150, 255));
		//renderTextureAndMask(testBuilding->getTex(), ren, 450, 300, 128, 128, 0, testBuilding->getMaskTex(), color(255, 50, 50));

		//renderTextureEx(getPlantTypeByDefName("Dandelion")->getGrowTex())

		//for (int i; i < textureDatabase->size(); i++)
		//{
		//	renderTextureEx(textureDatabase->at(i)->getTexture(), ren, 50 + (i * 20), 50, 50, 50, 0);
		//}

		// Update the screen
		SDL_RenderPresent(ren);
		//test.join();
		//deletePlayerTorpedos();
		//Take a quick break after all that hard work
	int frameticks = capTimer.getTicks();
	//this isn't helpful and it does nothing most of the time
	//if (frameticks < SCREEN_TICKS_PER_FRAME)
	//{
		//this almost never happens
		//capTimer.stop();
		//cout << "captimer sdl delay asserted" << endl;
		//SDL_Delay(SCREEN_TICKS_PER_FRAME - frameticks);
	//}
	//cout << "screen ticks per frame = " << SCREEN_TICKS_PER_FRAME << endl;
	countedFrames++;

	return void();
}