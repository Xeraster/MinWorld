#ifndef RANDOMFUNCTIONS_H
#define RANDOMFUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "color.h"
using namespace std;

extern int gscreenx;
extern int gscreeny;
typedef struct
{
	int radius;
	int distance;
	color whatColorIsPlanet;
} planetMetaData;

//I've decided I'm going to put the game's graphics quality vairables HERE
//I already can't find "menuQuality" so I'm designating right below this line as the proper place to put them

string metricWeightsSmall[] = { "grams", "mg", "μg", "ng", "pg", "fg", "yg", "zg" };
//metricWeightsSmall[0] = "mg";
//metricWeightsSmall[1] = "μg";
//metricWeightsSmall[2] = "ng";
//metricWeightsSmall[3] = "pg";
//metricWeightsSmall[4] = "fg";
//metricWeightsSmall[5] = "yg";
//metricWeightsSmall[6] = "zg";

color *colorArray = new color[6];

//random number generator
uint32_t betterRand(uint32_t seed);

SDL_Texture* loadTextureToRam(string texturePath, SDL_Renderer *ren);

//load texture into ram with texture access flag
SDL_Texture* loadTextureToRam_TA(string texturePath, SDL_Renderer* ren);

//get color of pixel as pos x,y on a texture access stream enabled texture
color pixelAtPos(SDL_Texture *tex, SDL_Renderer* ren, SDL_Window* win, int x, int y);

//renders a texture to a position on the screen
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

//renders a texture with the ability to scale and rotate. Only problem, it's substantially more expensive so use sparingly
void renderTextureEx(SDL_Texture *tex, SDL_Renderer *ren, int posX, int posY, int targetSizeX, int targetSizeY, double angle);

//render a texture but color it to the target color in places where the mask texture is white 255,255,255,255
void renderTextureAndMask(SDL_Texture *tex, SDL_Renderer *ren, int posX, int posY, int targetSizeX, int targetSizeY, double angle, SDL_Texture *mask, color maskColor);

//orders you a pizza. not really it draws a pixel
void drawPixel(SDL_Renderer *ren, int x, int y, color whatColor);

//24 bit unsigned 8 bit int color version of draw pixel. Squeeze every last bit of performance out of the 3d renderer
void drawPixel(SDL_Renderer *ren, int x, int y, color24 whatColor);

//draws a line
void drawLine(SDL_Renderer *ren, color whatColor, int x1, int y1, int x2, int y2);

//returns x size of screen
int screenSizeX(SDL_Window *win);

//returns y size of screen
int screenSizeY(SDL_Window *win);

void drawText(SDL_Renderer *ren, int fontSize, color TextColor, string textString, int x, int y);

void drawText(SDL_Renderer *ren, int fontSize, coloredString textString, int x, int y);

//return = number of rows it used
int drawTextWrapped(SDL_Renderer *ren, int fontSize, color TextColor, string textString, int x, int y, int pixelsBeforeWrap);

int getTextRows(string text, int fontSize, int pixelsBeforeWrap);

void drawRect(SDL_Renderer *ren, color whatColor, int x, int y, int sizeX, int sizeY);

void drawRectFilled(SDL_Renderer *ren, color whatColor, int x, int y, int sizeX, int sizeY);

void drawTriangle(SDL_Renderer *ren, color whatColor, int x1, int y1, int x2, int y2, int x3, int y3);

//draw an equilateral triangle. Intended to be used for menus. dir 0 = up. 1 = right. 2 = down. 3 = left
void drawEquilateralTriangle(SDL_Renderer *ren, color whatColor, int posX, int posY, int dir, int size, bool filled = false);

//draw an isosceles triangle. Intended to be used for menus. dir 0 = up. 1 = right. 2 = down. 3 = left
void drawIsoscelesTriangle(SDL_Renderer *ren, color whatColor, int posX, int posY, int dir, int size, int height, bool filled = false);

void drawCircle(SDL_Renderer *ren, color circleColor, int radius, int xPos, int yPos, bool filled);

void drawEmptyCircle(SDL_Renderer *ren, color circleColor, int radius, int xPos, int yPos);

void initQuickAccessColors();

//im making these 2 functions for use in zoom 1 mode for better performance
color seedToStarColor(uint32_t seed);

int seedToStarSize(uint32_t seed);

planetMetaData getPlanetDataFromSeed(uint32_t seed, planetMetaData yeah);

//makes a gradient in the specified bounds. The constructor without color will default to making a sky gradient
void drawGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, int numSteps = 10);
void drawGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color topColor, color bottomColor, int numSteps = 10);

//draw a sidways gradient. It goes sideways unlike drawGradient which goes vertical
void drawSidewaysGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color leftColor, color rightColor, int numSteps = 10);

//the gradient that progress bars use. It goes sideways
void drawCuttableSidewaysGradient(SDL_Renderer *ren, int x1, int y1, int x2, int y2, color leftColor, color rightColor, int cuttoff, int numSteps = 10);

//converts the 3drenderer's native 16 color variables into a full 32-bit color value
color colorByteToRGB(short stupidColor);

bool stringToBool(string input)
{
	if (input == "0" || input == "false") return false;
	else return true;
}

string boolToString(bool theBool)
{
	if (theBool) return "true";
	else return "false";
}

string gramsToReadable(double grams, bool showExact = false);

//loads the fonts into ram and keeps so they can be referenced each time the drawText function needs them
int loadFonts();

//put this at the end of the program to make valgrind shut up
int deleteFonts();

//SDL scancodes go in. ascii codes come out
char SDLcrap_to_char(const Uint8 *sdl_crap);

//caps lock global variable
bool capsLock = false;

string makeLowercase(string input);

string makeUppercase(string input);

void capitalizeFirstLetter(string &input);

int getTextYSize(int fontSize) { return (80 * fontSize / 24); }

int getTextXSize(int fontSize, int numChars) { return (30 * numChars * fontSize / 24); }

//converts a double to a string with a dollar sign in front that only has 2 decimal places
string doubleToMoney(double input)
{
	return "$" + to_string(input).substr(0, to_string(input).size() - 4);
}

string doubleToString(double input, int decimals = 1)
{
	if (to_string(input).size() - 6 + decimals > to_string(input).size())
	{
		return "doubleToString() error";
	}
	return to_string(input).substr(0, to_string(input).size() - 6 + decimals);
}

//to reduce garbage in the moreDetailedSubmarineInfo() function
coloredString lessOrBigger(int original, int compare);

coloredString lessOrBigger(double original, double compare, int decimalPlaces = 1);

//a 2d collision function. Mainly used for gui mouse collisions but suitable for probably every possible 2d box collision use
bool isColliding2D(int posX, int posY, int sizeX, int sizeY, int mouseX, int mouseY);

//converts a string to a number that can be used for a seed
int numberFromString(string input);

Uint32 colorToUint32(color input)
{
	return (input.getBlue()) + (input.getGreen() << 8) + (input.getRed() << 16) + (255 << 24);
}

//takes a double in meters and converts it into a nice string
string doubleToMeters(double value);

//takes a color an outputs the inverted of it
color invertColor(color uninverted);

double worldToMapX(double zoom, double mapX, double inX, int mapSizeX, double mapScale);
double worldToMapY(double zoom, double mapY, double inY, int mapSizeY, double mapScale);
double mapToWorldX(double zoom, double posX, double mapX);
double mapToWorldY(double zoom, double posY, double mapY);

//it actually outputs in degrees between 2 numerical angles. inputs in degrees not radians
double diffAngles(double angle1, double angle2);

//======================================================
//	save stuff
//======================================================
void writeElement(XMLElement *baseElement, string elementName, string elementValue);
void writeElement(XMLElement *baseElement, string elementName, int elementValue);
void writeElement(XMLElement *baseElement, string elementName, bool elementValue);
void writeElement(XMLElement *baseElement, string elementName, double elementValue);
void writeElement(XMLElement *baseElement, string elementName, float elementValue);

//TTF_Font* Sans;

//there can only be 1 event handler per frame or else they will fight each other
//this results in typing text being a pain in the ass since some keypressed don't seem to "register"
//the more event handlers per frame, the worse the problem gets
string lastCharTyped;
bool backspaceAsserted;
bool enterAsserted;

vector<TTF_Font*> fonts;

//void drawCrewIconLarge(vector<SDL_Texture*> crewLargeTextures, crewMember crewPerson, SDL_Renderer *ren, int x, int y);

#include "randomFunctions.hpp"

#endif