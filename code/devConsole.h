#ifndef DEVCONSOLE_H
#define DEVCONSOLE_H

bool in_game = false;

//should this be a class or just a combobulation of functions? I'm picking class because it seems like a good idea. AITA?
class devConsole
{
public:
	devConsole();

	void setScreenSize(int x, int y);

	void draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, int screenSizeX, int screenSizeY);

	void printString(string stringToPrint);

	void saveGame(string input);

private:

	color m_backgroundColor;
	color m_textColor;
	int m_screenX;
	int m_screenY;
	int m_textSize;
	int m_numLines;

	textbox m_inputLine;

	bool m_showConsole;
	bool m_enterDeAssertedYet;

	bool isIngame() { if (in_game) return true; }

	//list<string> m_consoleOutput;
	list<coloredString> m_consoleOutput;

	bool parseInput(string input);

	//void appendTextToConsole(string text);

	void printChunksxAxis(string input);
	void printChunksyAxis(string input);

	void appendTextToConsole(coloredString text);

	void throwError(string reason);
};

#include "devConsole.hpp"
#endif