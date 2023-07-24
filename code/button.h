#ifndef BUTTON_H
#define BUTTON_H

SDL_Texture *generic_dial_needle;
SDL_Texture *compass_dial_needle;

class button
{
public:
	button();
	button(string label, color textColor, int posX, int posY, int fontSize);

	button(const button& other);

	string getLabel() const { return m_label; }
	color textColor() const  { return m_textColor; }
	color backgroundColor() const  { return m_backgroundColor; }
	color highlightColor() const  { return m_highlightColor; }
	color clickColor() const { return m_clickColor; }
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }
	int fontsize() const { return m_fontsize; }
	int framesUnclick() const { return m_framesTillUnclick; }
	bool showBorder() const { return m_showBorder; }
	int arrow() const { return m_drawArrow; }
	int highlightRadius() const { return m_hightlightRadius; }
	bool buttonIsCircle() const { return m_buttonIsCircle; }
	string tooltip() const { return m_tooltip; }

	void setTooltip(string tooltip) { m_tooltip = tooltip; }
	void setCircle(bool circle) { m_buttonIsCircle = circle; }
	void setHighlightRadious(int radius) { m_hightlightRadius = radius; }

	void setFontSize(int size);
	void setLabel(string newLabel);
	void setPos(int posX, int posY);
	void setArrow(int arrow) { m_drawArrow = arrow; }
	void setBorder(bool borderStatus) { m_showBorder = borderStatus; }

	void setTextColor(color text) { m_textColor = text; }
	void setBackgroundColor(color background) { m_backgroundColor = background; }
	void setHighlightColor(color highlight) { m_highlightColor = highlight; }

	bool isMouseTouching(int mouseX, int mouseY);

	int derivedSizeY() { return (80 * m_fontsize / 24); }
	int derivedSizeX() { return (30 * m_label.size() * m_fontsize / 24); }

	bool draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture = nullptr);

	void draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle, SDL_Texture *optionalTexture = nullptr);

	button& operator=(const button& other);
private:
	string m_label;
	color m_textColor;
	color m_backgroundColor;
	color m_highlightColor;
	color m_clickColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_fontsize;
	int m_framesTillUnclick;
	bool m_showBorder;
	string m_tooltip;
	int m_drawArrow; 		//-1 = no. 0 = up, 1 = right. 2 = down. 3 = left
	void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture = nullptr);
	void drawTextOrTexture(SDL_Renderer *ren, color textColor, SDL_Texture *optionalTexture = nullptr);	//to make the doDraw function easier to read and less complicated
	void drawArrow(SDL_Renderer *ren, color arrowColor);

	int m_hightlightRadius;
	bool m_buttonIsCircle;

};

class textbox
{

public:
	textbox();
	textbox(string label, color textColor, int posX, int posY, int fontSize, int maxChars);
	textbox(const textbox& other);

	string text() const { return m_text; }
	color textColor() const { return m_textColor; }
	color backgroundColor() const { return m_backgroundColor; }
	void setTextColor(color tcolor) { m_textColor = tcolor; }
	void setBackgroundColor(color bcolor) { m_backgroundColor = bcolor; }

	int posX() const { return m_posX; }
	int posY() const { return m_posY; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }
	int fontsize() const { return m_fontsize; }
	int maxChars() const { return m_maxChars; }
	void replaceText(string text) { m_text = text;}

	bool isMouseTouching(int mouseX, int mouseY);
	void setDefaultText(string newText) { m_text = newText; }
	void setPos(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
	}

	//important for on the fly ui scaling
	void setFontSize(int newsize);

	int derivedSizeY() { return (80 * m_fontsize / 24); }
	int derivedSizeX() { return (30 * m_maxChars * m_fontsize / 24); }

	//call this one to draw the textbox
	string draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

	void select() { m_isSelected = true; }
	void deselect() { m_isSelected = false; }

	textbox& operator=(const textbox& other);
private:
	void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);
	void drawCursor(SDL_Renderer *ren);
	void appendText(string keyboardInput);
	string m_text;

	color m_textColor;
	color m_backgroundColor;

	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_fontsize;
	int m_maxChars;
	int m_timeTillNextKey;

	bool m_isSelected;
	int m_framesTillCursorBlink;
	bool m_cursorVisible;
	int m_frameWait;

};

class progressBar
{
public:
	progressBar();
	progressBar(int x, int y, int sizeX, int sizeY, color barColor, int max, bool gradient = false);

	void setMainColor(color whatColor) { m_mainColor = whatColor; }
	color mainColor() const { return m_mainColor; }
	void setSecondaryColor(color whatColor) { m_leftColor = whatColor; }
	color secondaryColor() const { return m_leftColor; }
	void setboarderColor(color whatColor) { m_boarderColor = whatColor; }
	color boarderColor() const { return m_boarderColor; }

	void setPos(int px, int py) { m_posX = px; m_posY = py; }
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }

	void setSize(int sx, int sy) { m_sizeX = sx; m_sizeY = sy; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	bool hasGradient() const { return m_gradient; }
	void setGradient(bool grad) { m_gradient = grad; }

	void setValue(int number) { m_value = number; }
	int getValue() const { return m_value; }

	void setMax(int number) { m_max = number; }
	int getMax() const { return m_max; }

	//progress bars are non-interactive gui elements
	void draw(SDL_Renderer *ren);

	progressBar& operator=(const progressBar& other);
private:
	color m_mainColor;
	color m_leftColor;
	color m_boarderColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	bool m_gradient;

	int m_value;
	int m_max;
};

//a vertical scroll view. You know, the kind of thing that looks like:
/*

----------------------------------
|   blah blah blah             |--
|   blah blah blah             |^^
|   blorf blorf blorf          |!!
|   example example            |!!
|   foo foo foo                |\/
|   bar                        |--
|---------------------------------
*/

//note that the vertical scroll view class is pretty new and there might still be bugs
class verticalScrollView
{
public:
	verticalScrollView();

	//make a constructor with nearly every parameter
	verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth, color backgroundColor, color barColor, color highlightColor, color textColor);

	//make a more minified one
	verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth);

	verticalScrollView(const verticalScrollView& other);

	void setBackgroundColor(color whatColor) { m_backgroundColor = whatColor; }
	color backgroundColor() const { return m_backgroundColor; }
	void setBarColor(color whatColor) { m_barColor = whatColor; }
	color barColor() const { return m_barColor; }
	void setHighlightColor(color whatColor) { m_hightlightColor = whatColor; }
	color highlightColor() const { return m_hightlightColor; }
	void setTextColor(color whatColor) { m_textColor = whatColor; }
	color textColor() const { return m_textColor; }


	//calculates the text size automatically.
	void setTextSize(int size) { m_textSize = size; }
	int textSize() const { return m_textSize; }

	void setPos(int px, int py);
	int posX() const { return m_posX; }
	int posY() const { return m_posY; }

	void setSize(int sx, int sy) { m_sizeX = sx; m_sizeY = sy; }
	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	void setBarWidth(int newWidth) { m_barWidth = newWidth; }
	int barWidth() const { return m_barWidth; }

	void setBarPos(int pos) { m_barPos = pos; }
	int barPos() const { return m_barPos; }

	//returns string of selected thing
	string draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

	verticalScrollView& operator=(const verticalScrollView& other);

	void addElement(string elementText);

	//removes all elements from the scroll view
	void removeAllElements();

	//deselects whatever is currently selected
	void deselect();


private:
	color m_backgroundColor;
	color m_barColor;
	color m_hightlightColor;
	color m_textColor;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	int m_barWidth;

	//the text size is calculated automatically
	void calculateTextSize();
	int m_textSize;

	//housekeeping variables used internally based on stuff. Not meant to be accessed from the outside
	int m_barHeight;
	int m_barPos;
	int m_mouseVerticalOffset;
	bool m_holdingClick;
	int m_selectedIndex;

	//i'm going to try to work smart not hard by making the vertical scroll view contain a vector of buttons. That way part of the code is already managed by button objects
	vector<button> m_elements;

	//separate the scroll bar and the non scroll bar drawing code to make everything easier for the programmer to figure out wtf is going on
	void drawScrollBar(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);
	void setStupidBool(bool value) { m_holdingClick = value; }

	//figure out how many different scroll positions there are
	int getNumPositions();

};

//a horizontal slider. if you want a vertical slider, make a child class
class slider
{
	public:
		slider();
		slider(color textColor, int posX, int posY, int sizeX, int sizeY);
		slider(const slider &other);
		slider& operator=(const slider& other);

		color getBarColor() const { return m_barColor; }
		void setBarColor(color newColor) { m_barColor = newColor; }

		color getSliderColor() const { return m_sliderColor; }
		void setSliderColor(color newColor) { m_sliderColor = newColor; }

		int posX() const { return m_posX; }
		int posY() const { return m_posY; }
		int sizeX() const { return m_sizeX; }
		int sizeY() const { return m_sizeY; }
		void setPos(int x, int y);
		void setSizeX(int x) { m_sizeX = x; }
		void setSizeY(int y) { m_sizeY = y; }

		void setValue(double val) { m_sliderValue = val; }
		double getValue() const { return m_sliderValue; }
		void setKnobWidth(int newWidth) { m_knobWidth = newWidth; }
		int getKnobWidth() const { return m_knobWidth; }

		int draw(SDL_Renderer *ren, int mouseX, int mouseY, int lastmouse);

	protected:
		color m_barColor;
		color m_sliderColor;
		int m_posX;
		int m_posY;
		int m_sizeX;
		int m_sizeY;
		double m_sliderValue;	//between 0.0 and 1.0
		bool m_holdingClick;

		bool isMouseTouching(int mouseX, int mouseY);

	private:
		void doDraw(SDL_Renderer *ren, int mouseX, int mouseY, int lastmouse);
		int m_knobWidth;
};

//==========================================================
//dial ui element
//========================================================
class dial
{

public:

	dial();
	dial(int size, int posX, int posY, int maxVal, SDL_Texture *texture, double minAngle = 0, double maxAngle = 360);
	dial(const dial& other);


	dial& operator=(const dial& other);

	int posX() const { return m_posX; }
	int posY() const { return m_posY; }
	void setPos(int px, int py) { m_posX = px; m_posY = py; }

	int sizeX() const { return m_sizeX; }
	int sizeY() const { return m_sizeY; }

	color getDialColor() const { return m_dialColor; }
	void setDialColor(color newColor) { m_dialColor = newColor; }

	double maxVal() const { return m_maxVal; }
	void setMaxVal(double newMax) { m_maxVal = newMax; }

	void setMinDegrees(double newVal) { m_minDegrees = newVal; }
	void setMaxDegrees(double newVal) { m_maxDegrees = newVal; }
	double minDegrees() const { return m_minDegrees; }
	double maxDegrees() const { return m_maxDegrees; }

	SDL_Texture* getTexture() const { return m_elementTexture; }
	SDL_Texture* getDialTexture() const { return m_dialTexture; }
	void setTexture(SDL_Texture *newTexture) { m_elementTexture = newTexture; }
	void setNeedleTexture(SDL_Texture *newTexture) { m_dialTexture = newTexture; }

	int getRadius() const { return m_radius; }
	void setRadius(int newValue) { m_radius = newValue; m_sizeY = m_radius*2; m_sizeX = m_radius*2; }

	void getCenter(int &x, int &y) { y = m_posY + m_radius; x = m_posX + m_radius; }

	double value() const { return m_currentValue; }
	//allows you to set a value manually
	void setValue(double newValue);
	double degrees() const { return m_degreesOfLastClick; }

	double draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

private:
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;

	double m_maxVal;

	double m_minDegrees;
	double m_maxDegrees;

	int m_radius;
	color m_dialColor;
	SDL_Texture *m_elementTexture;
	SDL_Texture *m_dialTexture;

	double m_currentValue;
	double m_degreesOfLastClick;
};

//ui elements intended for use in map view
//boy, do I sure love programming ui crap /s

class markerPoint
{
public:
	markerPoint();
	markerPoint(double posX, double posY, int markerNum);

	void setPos(double x, double y);
	double posX() const { return m_worldPosX; }
	double posY() const { return m_worldPosY; }
	string getCaption() const { return m_caption; }

	//returns 0 if mouse not touching. returns 1 if mouse touching. This is intended to be used for deleting from map view
	int draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, int correctX, int correctY, bool cursorHighlight = false);

	markerPoint& operator=(const markerPoint& other);

private:
	double m_worldPosX;
	double m_worldPosY;
	string m_caption;
};

class rulerLine
{
public:
	rulerLine();
	rulerLine(double posX, double posY);
	rulerLine(double posX1, double posY1, double posX2, double posY2);

	double posX1() const { return m_worldPosX1; }
	double posX2() const { return m_worldPosX2; }
	double posY1() const { return m_worldPosY1; }
	double posY2() const { return m_worldPosY2; }
	bool secondPointPlaced() const { return m_secondPointPlaced; }
	double distance() const { return m_length; }

	void setFirstPoint(double x, double y) { m_worldPosX1 = x; m_worldPosY1 = y; }
	void setSecondPoint(double x, double y) { m_worldPosX2 = x; m_worldPosY2 = y; m_secondPointPlaced = true; }
	void swapPoints();

	//returns 0 if mouse not touching. returns 1 if mouse touching. This is intended to be used for deleting from map view
	int draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool lengthOnOtherEnd = false, bool cursorSelect = false);

	rulerLine& operator=(const rulerLine& other);
protected:
	double m_worldPosX1;
	double m_worldPosY1;
	double m_worldPosX2;
	double m_worldPosY2;
	bool m_secondPointPlaced;
	double m_length;

	void calculateDistance();
};

class protractorAngle
{
public:
	protractorAngle();
	protractorAngle(double posX1, double posY1);

	double posX1() const { return m_firstLine.posX1(); }
	double posY1() const { return m_firstLine.posY1(); }

	double posX2() const { return m_firstLine.posX2(); }
	double posY2() const { return m_firstLine.posY2(); }

	double posX3() const { return m_secondLine.posX1(); }
	double posY3() const { return m_secondLine.posX1(); }

	bool firstLinePlaced() const { return m_firstLine.secondPointPlaced(); }
	bool secondLinePlaced() const { return m_secondLine.secondPointPlaced(); }
	double getAngle() const { return m_angle; }

	rulerLine getFirstLine() const { return m_firstLine; }
	rulerLine getSecondLine() const { return m_secondLine; }

	void setFirstLineSecondPoint(double x, double y) { m_firstLine.setSecondPoint(x,y); m_secondLine.setFirstPoint(x, y); }
	void setSecondLineSecondPoint(double x, double y) { m_secondLine.setSecondPoint(x,y); m_secondLinePlaced = true; calculateAngle(); }

	//returns 0 if mouse not touching. returns 1 if mouse touching. This is intended to be used for deleting from map view
	int draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool cursorSelect = false);

	protractorAngle& operator=(const protractorAngle& other);
protected:
	rulerLine m_firstLine;
	rulerLine m_secondLine;
	double m_angle;
	bool m_secondLinePlaced;

	void calculateAngle();
};

class compassCircle
{
public:
	compassCircle();
	compassCircle(double posX, double posY);
	rulerLine getLine() const { return m_theLine; }

	//returns 0 if mouse not touching. returns 1 if mouse touching. This is intended to be used for deleting from map view
	int draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool cursorSelect = false);
	compassCircle& operator=(const compassCircle& other);
	rulerLine m_theLine;
private:
};

//it actually outputs in degrees not radians
double angleBetweenLinesInRadians(rulerLine line1, rulerLine line2);

//=============================================================================================
//more ui elements. these either extend existing classes or are made out of existing classes
//=============================================================================================

//damn making this stupid ui element took all day
//that thing that goes like: [<][info][>] and you can click the forward or backwards button
class sideScroll
{
	public:
		//its recommended that you don't use this one
		sideScroll();

		//use this constructor because it pre-sets a lot of the boring stuff for you. note: width is in characters not pixels
		sideScroll(int posX, int posY, int fontSize, int width);

		sideScroll(const sideScroll& other);

		color backgroundColor() const  { return m_backgroundColor; }
		bool hasBackground() const { return m_background; }
		int posX() const { return m_posX; }
		int posY() const { return m_posY; }
		int sizeX() const;				//sizex is derived
		int sizeY() const { return m_sizeY; }
		int fontsize() const { return m_fontsize; }
		bool showBorder() const { return m_showBorder; }
		string tooltip() const { return m_tooltip; }
		int maxChars() const { return m_maxChars; }

		void setTooltip(string tooltip) { m_tooltip = tooltip; }
		string getTooltip() const { return m_tooltip; }

		void setFontSize(int size);
		void setPos(int posX, int posY);
		void setBorder(bool borderStatus) { m_showBorder = borderStatus; }
		bool hasBorder() const { return m_showBorder; }

		//const version of left button for copy constructor
		button leftButtonConst() const { return m_leftButton; }
		//const version of right button for copy constructor
		button rightButtonConst() const { return m_rightButton; }

		//index and list stuff
		void addItem(coloredString item);

		//get index of selected item
		int getIndex() const { return m_selectedIndex; }

		void setBackgroundColor(color background) { m_backgroundColor = background; }

		bool isMouseTouching(int mouseX, int mouseY);

		//int derivedSizeY() { return (80 * m_fontsize / 24); }
		//int derivedSizeX() { return (30 * m_label.size() * m_fontsize / 24); }

		//draw the object. returns selected index
		int draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse);

		//im too lazy and hate ui design to much to implement a texturing/themeing feature for this ui element right now
		//void draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle, SDL_Texture *optionalTexture = nullptr);

		sideScroll& operator=(const sideScroll& other);
	private:
		button m_leftButton;		//the left button
		button m_rightButton;		//the right button
		bool m_background;			//background of the label and display area
		color m_backgroundColor;	//background color of the label and display area
		int m_posX;					//position of the upper left bounds of the element
		int m_posY;
		//int m_sizeX;				//sizeX is derived and not stored
		int m_sizeY;				//size of the element including buttons
		int m_fontsize;				//size of the font in the label area
		bool m_showBorder;			//whether or not to show a border around the label area
		string m_tooltip;			//tooltip to display when mouse is hovering over element, if applicable
		int m_selectedIndex;		//index of selected item

		int m_maxChars;				//in order to derive x size, we need a target number of characters

		//make the list element contain a vector of colored strings
		vector<coloredString> m_elements;
};

extern SDL_Event testEvent;
extern bool exitGame;
SDL_Event keyboardEvent;

#include "button.hpp"

#endif 
