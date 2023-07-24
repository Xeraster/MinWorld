button :: button()
{
	color orange(255,128,0);
	m_highlightColor = orange;
	color yellow(255,255,0);
	m_clickColor = yellow;
	m_framesTillUnclick = 0;
	m_showBorder = false;
	m_drawArrow = false;
	m_hightlightRadius = 50;
	m_buttonIsCircle = false;
	m_tooltip = "";
	m_drawArrow = -1;
}

button :: button(string label, color textColor, int posX, int posY, int fontSize)
{
	m_label = label;
	m_textColor = textColor;
	color noColor(0,0,0,0);
	color orange(255,128,0);
	m_highlightColor = orange;
	color yellow(255,255,0);
	m_clickColor = yellow;
	m_backgroundColor = noColor;
	m_posX = posX;
	m_posY = posY;
	m_fontsize = fontSize;
	m_sizeX = (30 * label.length()) * fontSize / 24;
	m_sizeY = 80 * fontSize / 24;
	m_framesTillUnclick = 0;
	m_showBorder = false;
	m_drawArrow = -1;
	m_hightlightRadius = 50;
	m_buttonIsCircle = false;
	m_tooltip = "";
}

button :: button(const button& other)
{
	m_label = other.getLabel();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_highlightColor = other.highlightColor();
	m_clickColor = other.clickColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_framesTillUnclick = other.framesUnclick();
	m_showBorder = other.showBorder();
	m_drawArrow = other.arrow();
	m_hightlightRadius = other.highlightRadius();
	m_buttonIsCircle = other.buttonIsCircle();
	m_tooltip = other.tooltip();
}

button& button :: operator=(const button& other)
{
	m_label = other.getLabel();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_highlightColor = other.highlightColor();
	m_clickColor = other.clickColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_framesTillUnclick = other.framesUnclick();
	m_showBorder = other.showBorder();
	m_drawArrow = other.arrow();
	m_hightlightRadius = other.highlightRadius();
	m_buttonIsCircle = other.buttonIsCircle();
	m_tooltip = other.tooltip();

	return *this;
}

void button :: setFontSize(int size)
{
	m_fontsize = size;
	m_sizeX = (30 * m_label.length()) * m_fontsize / 24;
	m_sizeY = 80 * m_fontsize / 24;
}

void button :: setLabel(string newLabel)
{
	m_label = newLabel;
	m_sizeX = (30 * newLabel.length()) * m_fontsize / 24;
	m_sizeY = 80 * m_fontsize / 24;
}

void button :: setPos(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
}

bool button :: isMouseTouching(int mouseX, int mouseY)
{
	if (mouseX > m_posX && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY)
	{
		return true;
	}
	else if (m_drawArrow == 3 && mouseX > m_posX - ((80 * m_fontsize / 24)/2) - 5 && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY) 
	{
		return true;
	}
	else if (m_drawArrow == 1 && mouseX > m_posX && mouseX < m_posX + m_sizeX + 5 + ((80 * m_fontsize / 24)/2) && mouseY > m_posY && mouseY < m_posY + m_sizeY)
	{
		return true;
	}
	else if (m_drawArrow == 0 && mouseX > m_posX - ((80 * m_fontsize / 24)/2)&& mouseX < m_posX + ((80 * m_fontsize / 24)/2) && mouseY > m_posY  - ((80 * m_fontsize / 24)/2) - 5 && mouseY < m_posY)
	{
		return true;
	}
	else if (m_drawArrow == 2 && mouseX > m_posX - ((80 * m_fontsize / 24)/2)&& mouseX < m_posX + ((80 * m_fontsize / 24)/2) && mouseY < m_posY + m_sizeY + 5 + ((80 * m_fontsize / 24)/2) && mouseY > m_posY + m_sizeY + 5)
	{
		return true;
	}
	else return false;
}

bool button :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture)
{	
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesTillUnclick == 0 && isMouseTouching(mouseX, mouseY)) m_framesTillUnclick = 10;

	doDraw(ren, mouseX, mouseY, lastmouse, optionalTexture);
	//strobe true when in a 60fps loop (it's true for 1 frame)
	if (m_framesTillUnclick == 9) return true;
	else return false;

}

void button:: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, bool &boolToToggle, SDL_Texture *optionalTexture)
{
	
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && m_framesTillUnclick == 0 && isMouseTouching(mouseX, mouseY)) m_framesTillUnclick = 10;

	doDraw(ren, mouseX, mouseY, lastmouse, optionalTexture);
	//strobe true when in a 60fps loop (it's true for 1 frame)
	if (m_framesTillUnclick == 9) 
	{
		boolToToggle = !boolToToggle;
	}
}

void button :: doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, SDL_Texture *optionalTexture)
{
	if (m_backgroundColor.getAlpha() != 0) drawRectFilled(ren, m_backgroundColor, m_posX, m_posY, m_sizeX, m_sizeY);
	if (m_framesTillUnclick > 0)
	{
		if (m_showBorder) drawRect(ren, m_clickColor, m_posX, m_posY, m_sizeX, m_sizeY);
		//drawText(ren, m_fontsize, m_clickColor, m_label, m_posX, m_posY);
		drawTextOrTexture(ren, m_clickColor, optionalTexture);
		if (m_drawArrow > -1) drawArrow(ren, m_clickColor);
		m_framesTillUnclick--;
	}
	//if mouse is hovering over button, draw it in the highlight color instead of the text color
	else if (isMouseTouching(mouseX, mouseY))
	{
		if (!m_buttonIsCircle)
		{
			//drawText(ren, m_fontsize, m_highlightColor, m_label, m_posX, m_posY);
			drawTextOrTexture(ren, m_highlightColor, optionalTexture);
			if (m_showBorder) drawRect(ren, m_highlightColor, m_posX, m_posY, m_sizeX, m_sizeY);
			if (m_drawArrow > -1) drawArrow(ren, m_highlightColor);
		}
		else
		{
			drawCircle(ren, m_highlightColor, m_hightlightRadius, m_posX + (m_sizeX/2), m_posY + (m_sizeY/2), true);
			drawText(ren, m_fontsize, m_textColor, m_tooltip, m_posX, m_posY + (m_sizeY/2));
		}
	}
	else 
	{
		if (m_showBorder) drawRect(ren, m_textColor, m_posX, m_posY, m_sizeX, m_sizeY);
		//drawText(ren, m_fontsize, m_textColor, m_label, m_posX, m_posY);
		drawTextOrTexture(ren, m_textColor, optionalTexture);
		if (m_drawArrow > -1) drawArrow(ren ,m_textColor);
	}
}

void button :: drawTextOrTexture(SDL_Renderer *ren, color textColor, SDL_Texture *optionalTexture)	//to make the doDraw function easier to read and less complicated
{
	if (optionalTexture == nullptr)
	{
		drawText(ren, m_fontsize, textColor, m_label, m_posX, m_posY);
	}
	else
	{
		renderTextureEx(optionalTexture, ren, m_posX, m_posY, m_sizeX, m_sizeY, 0);
	}
}

void button :: drawArrow(SDL_Renderer *ren, color arrowColor)
{
	//left arrow
	if (m_drawArrow == 3)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX - 5, m_posY + ((80 * m_fontsize / 24)/2), m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//right arrow
	else if (m_drawArrow == 1)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX + m_sizeX + 5, m_posY + ((80 * m_fontsize / 24)/2), m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//up arrow
	else if (m_drawArrow == 0)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX, m_posY - 5, m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}
	//down arrow
	else if (m_drawArrow == 2)
	{
		drawIsoscelesTriangle(ren, arrowColor, m_posX, m_posY + m_sizeY + 5, m_drawArrow, (80 * m_fontsize / 24), (80 * m_fontsize / 24)/2, true);
	}

}

//=============================================================
//textbox
//=============================
textbox :: textbox()
{
	m_text = "this is a textbox";
	color white(255,255,255,255);
	color clearBlack(0,0,0,100);
	m_textColor = white;
	m_backgroundColor = clearBlack;
	m_posX = 0;
	m_posY = 0;
	m_fontsize = 12;
	m_maxChars = 30;
	m_sizeX = (30 * m_maxChars * m_fontsize / 24);
	m_sizeY = 80 * m_fontsize / 24;
	m_isSelected = false;
	m_framesTillCursorBlink = 30;
	m_cursorVisible = false;
	m_timeTillNextKey = 0;
	m_frameWait = 0;
}

textbox :: textbox(string label, color textColor, int posX, int posY, int fontSize, int maxChars)
{
	m_text = label;
	m_textColor = textColor;
	color clearBlack(0,0,0,100);
	m_backgroundColor = clearBlack;
	m_posX = posX;
	m_posY = posY;
	m_fontsize = fontSize;
	m_maxChars = maxChars;
	m_sizeX = (30 * m_maxChars * m_fontsize / 24);
	m_sizeY = 80 * m_fontsize / 24;
	m_isSelected = false;
	m_framesTillCursorBlink = 30;
	m_cursorVisible = false;
	m_timeTillNextKey = 0;
	m_frameWait = 0;
}

textbox :: textbox(const textbox& other)
{
	m_text = other.text();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_maxChars = other.maxChars();
}

bool textbox :: isMouseTouching(int mouseX, int mouseY)
{
	if (mouseX > m_posX && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY) return true;
	else return false;
}

textbox& textbox :: operator=(const textbox& other)
{
	m_text = other.text();
	m_textColor = other.textColor();
	m_backgroundColor = other.backgroundColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_maxChars = other.maxChars();

	return *this;
}

//important for on the fly ui scaling
void textbox :: setFontSize(int newsize)
{
	m_fontsize = newsize;
	m_sizeX = (30 * m_maxChars * m_fontsize / 24);
	m_sizeY = 80 * m_fontsize / 24;
	return void();
}

string textbox :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{	
	//clicking anywhere in the textbox selects it
	if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && isMouseTouching(mouseX, mouseY)) select();
	//clicking anywhere outside the textbox deselects it
	else if (lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT) && !isMouseTouching(mouseX, mouseY)) deselect();

	doDraw(ren, mouseX, mouseY, lastmouse);
	return m_text;
}

void textbox :: doDraw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	//draw background first
	drawRectFilled(ren, m_backgroundColor, m_posX, m_posY, m_sizeX, m_sizeY);
	drawText(ren, m_fontsize, m_textColor, m_text, m_posX, m_posY);
	if (m_isSelected) 
	{

		//SDL_PollEvent( &keyboardEvent );
		/*while (SDL_PollEvent(&keyboardEvent) == 1)
		{
	

       	 	if (keyboardEvent.type == SDL_TEXTINPUT)
       	 	{
       	 		m_text += keyboardEvent.text.text;
       	 	}

        	if (keyboardEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				exitGame = true;
			}

    	}*/

    	//backspace isnt handled by the SDL_TEXTINPUT event
    	/*const Uint8 *lastKey = SDL_GetKeyboardState(NULL);
    	if (m_timeTillNextKey <= 0)
    	{
    		if (lastKey[SDL_SCANCODE_BACKSPACE]) 
    		{
    			m_text = m_text.substr(0, m_text.size() - 1);
    			m_timeTillNextKey = 10;
    		}
    	}*/
    	if (backspaceAsserted && m_timeTillNextKey <= 0)
    	{
    		m_text = m_text.substr(0, m_text.size() - 1);
    		m_timeTillNextKey = 10;
    	}
    	else if (m_timeTillNextKey > 0) m_timeTillNextKey--;
    	else if (backspaceAsserted) m_timeTillNextKey = 0;

        //since i'm overriding the event by polling it, I have to do a close game check
        //to be honest, this system kinda sucks balls. You can't even argue that "yeah well its better this way cuz there's interrupts" because you have to poll it anyway.

        //cout << to_string(keyboardEvent.key.type) << endl;
        if (m_text.size() < m_maxChars) m_text += lastCharTyped;
		drawCursor(ren);
	}
}

void textbox :: drawCursor(SDL_Renderer *ren)
{
	int cursorTop = m_posY + (m_sizeY*0.15);
	int cursorBottom = m_posY + m_sizeY - (m_sizeY*0.15);
	if (m_cursorVisible) drawLine(ren, m_textColor, m_posX + ((30 * m_text.length()) * m_fontsize / 24), cursorTop, m_posX + ((30 * m_text.length()) * m_fontsize / 24), cursorBottom);
	m_framesTillCursorBlink--;

	if (m_framesTillCursorBlink <= 0)
	{
		m_framesTillCursorBlink = 30;
		m_cursorVisible = !m_cursorVisible;
	}
}

void textbox :: appendText(string keyboardInput)
{
	if (keyboardInput == "Backspace" && m_text.size() > 0) m_text = m_text.substr(0, m_text.size() - 1);
	else if (keyboardInput == "CapsLock") capsLock = !capsLock;
	else if (keyboardInput == "Space") m_text += " ";
	//cout << "keyboardInput = " << keyboardInput << endl;
	else if (keyboardInput.size() == 1)
	{
		if (capsLock) m_text += keyboardInput;
		else m_text += makeLowercase(keyboardInput);
	}
	//m_text.substr(0, m_text.size() - 1);
}

//=========================================
//progress bar
//========================================

progressBar :: progressBar()
{

}

progressBar :: progressBar(int x, int y, int sizeX, int sizeY, color barColor, int max, bool gradient)
{
	color black(0,0,0,255);
	m_mainColor = barColor;
	m_leftColor = barColor;
	/*if (m_leftColor.getRed() > 100) m_leftColor.setRed(m_leftColor.getRed() - 100);
	if (m_leftColor.getGreen() > 100) m_leftColor.setGreen(m_leftColor.getGreen() - 100);
	if (m_leftColor.getBlue() > 100) m_leftColor.setBlue(m_leftColor.getBlue() - 100);*/

	m_leftColor.setRed(m_leftColor.getRed() * 0.2);
	m_leftColor.setGreen(m_leftColor.getGreen() * 0.2);
	m_leftColor.setBlue(m_leftColor.getBlue() * 0.2);
	m_boarderColor = black;
	m_posX = x;
	m_posY = y;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_gradient = gradient;
	m_max = max;
	m_value = 0;
}

void progressBar :: draw(SDL_Renderer *ren)
{
	if (m_gradient)
	{
		//cout << "number equals " << (static_cast<double>(m_value) / static_cast<double>(m_max)) << endl;
		int cutoffSize = (static_cast<double>(m_value) / static_cast<double>(m_max)) * m_sizeX;
		//cout << "cutoff size = " << cutoffSize << endl;
		drawCuttableSidewaysGradient(ren, m_posX, m_posY, m_sizeX, m_sizeY, m_leftColor, m_mainColor, cutoffSize, 20);
	}
	else
	{
		drawRectFilled(ren, m_mainColor, m_posX, m_posY, m_sizeX, m_sizeY);
	}
	drawRect(ren, m_boarderColor, m_posX, m_posY, m_sizeX, m_sizeY);
}

progressBar& progressBar :: operator=(const progressBar& other)
{
	m_mainColor = other.mainColor();
	m_leftColor = other.secondaryColor();
	m_boarderColor = other.boarderColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_gradient = other.hasGradient();
	m_max = other.getMax();
	m_value = other.getValue();
}

//==============================================
//vertical scroll view
//=============================================
verticalScrollView :: verticalScrollView()
{
	//make a blank empty one just whatever but setup some colors
	m_backgroundColor = color(0,0,0,100);
	m_barColor = color(0,0,255,255);
	m_hightlightColor = color(255,150,0,255);
	m_selectedIndex = -1;
}


verticalScrollView :: verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth, color backgroundColor, color barColor, color highlightColor, color textColor)
{
	m_backgroundColor = backgroundColor;
	m_barColor = barColor;
	m_hightlightColor = highlightColor;
	m_textColor = textColor;
	m_posX = x;
	m_posY = y;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_barWidth = barWidth;
	m_barPos = 0;
	m_selectedIndex = -1;

	calculateTextSize();
}

verticalScrollView :: verticalScrollView(int x, int y, int sizeX, int sizeY, int barWidth)
{
	//make a blank empty one just whatever but setup some colors
	m_backgroundColor = color(0,0,0,100);
	m_barColor = color(0,0,255,255);
	m_hightlightColor = color(255,150,0,255);
	m_textColor = color(255,0,0,255);

	//the rest of the values
	m_posX = x;
	m_posY = y;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_barWidth = barWidth;
	m_barPos = 0;
	m_selectedIndex = -1;

	calculateTextSize();
}

verticalScrollView :: verticalScrollView(const verticalScrollView& other)
{
	m_backgroundColor = other.backgroundColor();
	m_barColor = other.barColor();
	m_hightlightColor = other.highlightColor();
	m_textColor = other.textColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_barWidth = other.barWidth();
	m_barPos = other.barPos();
	m_selectedIndex = -1;

	calculateTextSize();
}

verticalScrollView& verticalScrollView :: operator=(const verticalScrollView& other)
{
	m_backgroundColor = other.backgroundColor();
	m_barColor = other.barColor();
	m_hightlightColor = other.highlightColor();
	m_textColor = other.textColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_barWidth = other.barWidth();
	m_barPos = other.barPos();
	m_selectedIndex = -1;

	calculateTextSize();

	return *this;
}

void verticalScrollView :: setPos(int px, int py) 
{ 
	m_posX = px; 
	m_posY = py;

	for (int i = 0; i < m_elements.size(); i++)
	{
		int newButtonPosX = m_posX;
		int newButtonPosY = m_posY + (80 * m_textSize / 24 * i);
		m_elements.at(i).setPos(newButtonPosX, newButtonPosY);
	} 
}

//calculates text size to be used when new elements are added
void verticalScrollView :: calculateTextSize()
{
	int n = 4;
	//make it so that you can fit n characters per 100 pixels

	//what font size can fit in m_sizeX if n characters are used?
	m_textSize = static_cast<double>(100) / static_cast<double>(30) * static_cast<double>(n);
	cout << "m_textSize = " << m_textSize << endl;

	return void();
}

string verticalScrollView :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{	
	//m_selectedIndex = -1;
	//if number of positions is either zero or less than zero, no scrolling is required. Set barheight to m_sizeY to avoid dumb bugs
	if (getNumPositions() > 0)
	{
		m_barHeight = m_sizeY / getNumPositions();
	}
	else m_barHeight = m_sizeY;
	//draw background
	drawRectFilled(ren, m_backgroundColor, m_posX, m_posY, m_sizeX, m_sizeY);

	//draw the slider bar
	//m_sliderBar.draw(ren, mouseX, mouseY, lastmouse);
	//cout << m_sliderBar.posX() << "," << m_sliderBar.posY() << m_sliderBar.sizeX() << "," << m_sliderBar.sizeY() << endl;
	drawScrollBar(ren, mouseX, mouseY, lastmouse);

	//drawText(ren, 12, color(255,0,0), "haha poop", m_posX, m_posY);
	for (int i=m_barPos; i < m_elements.size(); i++)
	{
		//don't draw stuff beyond the box
		if (m_elements.at(i).posY() >= m_posY + m_sizeY + (m_elements.at(i).sizeY()*m_barPos))
		{
			i = m_elements.size();
		}
		//if elements aren't beyond the scroll view box bottom bounds, go ahead and draw them
		else
		{

			//figure out character space for length of x size
			int numBlanksToAppend = (m_sizeX - getTextXSize(m_textSize, m_elements.at(i).getLabel().length()))/getTextXSize(m_textSize, 1);

			//the button labels are meant to be used to resolve the save location so be sure to save the original labels, modify them to viewing standards then change them back
			string originalText = m_elements.at(i).getLabel();

			//append blanks to element so that the end of the button will be clickable
			for (int p = 0; p < numBlanksToAppend; p++)
			{
				m_elements.at(i).setLabel(m_elements.at(i).getLabel() + " ");
			}
			m_elements.at(i).setPos(m_elements.at(i).posX(), m_elements.at(i).posY() - (m_elements.at(i).sizeY()*m_barPos));
			if (m_elements.at(i).draw(ren, mouseX, mouseY, lastmouse))
			{
				m_selectedIndex = i;
			}
			m_elements.at(i).setPos(m_elements.at(i).posX(), m_elements.at(i).posY() + (m_elements.at(i).sizeY()*m_barPos));

			//put back original label
			m_elements.at(i).setLabel(originalText);
		}
	}

	//cout << "there are " << getNumPositions() << " positions and " << m_elements.size() << " total elements" << endl;
	
	if (m_selectedIndex > -1)
	{
		return m_elements.at(m_selectedIndex).getLabel();
	}
	else
	{
		return to_string(m_selectedIndex);
		return "error";
	}
}

//separate the scroll bar and the non scroll bar drawing code to make everything easier for the programmer to figure out wtf is going on
void verticalScrollView :: drawScrollBar(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	int scrollPosX = m_posX + m_sizeX + 5;
	int scrollPosY = m_posY;

	if ((isColliding2D(scrollPosX, scrollPosY, m_barWidth, m_sizeY, mouseX, mouseY) || (m_holdingClick && mouseY > m_posY && mouseY < m_posY + m_sizeY) )&& lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (!m_holdingClick)
		{
			m_holdingClick = true;
			m_mouseVerticalOffset = mouseY - scrollPosY - (m_barPos*m_barHeight);
		}
		scrollPosY = mouseY - m_mouseVerticalOffset;
		drawRectFilled(ren, m_hightlightColor, scrollPosX, scrollPosY, m_barWidth, m_barHeight);

		m_barPos = (scrollPosY - m_posY) / m_barHeight;
		//cout << "bar position = " << (scrollPosY - m_posY) / m_barHeight << endl;
	}
	else
	{
		m_holdingClick = false;
		m_mouseVerticalOffset = 0;
		drawRectFilled(ren, m_barColor, scrollPosX, scrollPosY + (m_barPos*m_barHeight), m_barWidth, m_barHeight);
	}
	
	//draw triangles above and below the scroll bar
	drawEquilateralTriangle(ren, color(255,255,255,255), m_posX + m_sizeX + 5 + (m_barWidth)/2, m_posY - 2, 0, m_barWidth, true);
	drawEquilateralTriangle(ren, color(255,255,255,255), m_posX + m_sizeX + 5 + (m_barWidth)/2, m_posY + m_sizeY + 2, 2, m_barWidth, true);
}

void verticalScrollView :: addElement(string elementText)
{
	//m_sizeY = 80 * m_fontsize / 24;
	//m_sizeX = (30 * m_label.length()) * m_fontsize / 24;
	int newButtonPosY = m_posY + (80 * m_textSize / 24 * m_elements.size());

	//figure out character space for length of x size
	//int numBlanksToAppend = (m_sizeX - getTextXSize(m_textSize, elementText.length()))/getTextXSize(m_textSize, 1);

	//append blanks to element so that the end of the button will be clickable
	//for (int i = 0; i < numBlanksToAppend; i++)
	//{
	//	elementText += " ";
	//}


	button newButton(elementText, m_textColor, m_posX, newButtonPosY, m_textSize);

	m_elements.push_back(newButton);

	m_selectedIndex = -1;
}

//removes all elements from the scroll view
void verticalScrollView :: removeAllElements()
{
	m_elements.clear();

	//not resetting this to zero, removing all the elements then drawing again may have buggy results unless barPos gets reset to zero
	m_barPos = 0;
	m_selectedIndex = -1;
}

//deselects whatever is currently selected
void verticalScrollView :: deselect()
{
	m_selectedIndex = -1;
	return void();
}


//figure out how many different scroll positions there are
int verticalScrollView :: getNumPositions() 
{
	int number = m_elements.size() - (m_sizeY / getTextYSize(m_textSize)); 
	if (number > 0) return number;
	else return 0;
}

//==============================================
//slider
//===============================================
slider :: slider()
{
	m_barColor = color(255, 255, 255);
	m_sliderColor = color(255, 255, 255);
	m_posX = 0;
	m_posY = 0;
	m_sizeX = 200;
	m_sizeY = 50;
	m_sliderValue = 0.5f;
	m_holdingClick = false;
	m_knobWidth = 20;
}

slider :: slider(color textColor, int posX, int posY, int sizeX, int sizeY)
{
	m_barColor = color(255, 255, 255);
	m_sliderColor = textColor;
	m_posX = posX;
	m_posY = posY;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_sliderValue = 0.5f;
	m_holdingClick = false;
	m_knobWidth = 20;
}

slider :: slider(const slider &other)
{
	m_barColor = other.getBarColor();
	m_sliderColor = other.getSliderColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_sliderValue = other.getValue();
	m_holdingClick = false;
	m_knobWidth = other.getKnobWidth();
}

slider& slider :: operator=(const slider& other)
{
	m_barColor = other.getBarColor();
	m_sliderColor = other.getSliderColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_sliderValue = other.getValue();
	m_holdingClick = false;
	m_knobWidth = other.getKnobWidth();

	return *this;
}

void slider :: setPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

int slider :: draw(SDL_Renderer *ren, int mouseX, int mouseY, int lastmouse)
{
	doDraw(ren, mouseX, mouseY, lastmouse);
	//strobe true when in a 60fps loop (it's true for 1 frame)
	//if (m_framesTillUnclick == 9) return true;
	//else return false;
	return m_sliderValue;
}

bool slider :: isMouseTouching(int mouseX, int mouseY)
{
	if (mouseX > m_posX && mouseX < m_posX + m_sizeX && mouseY > m_posY && mouseY < m_posY + m_sizeY)
	{
		return true;
	}
	else return false;
}

void slider :: doDraw(SDL_Renderer *ren, int mouseX, int mouseY, int lastmouse)
{
	//if (m_framesTillUnclick > 0)
	//if mouse touching and left click
	if ((isMouseTouching(mouseX, mouseY) && lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT)) || m_holdingClick)
	{
		//if (m_showBorder) drawRect(ren, m_clickColor, m_posX, m_posY, m_sizeX, m_sizeY);
		//drawText(ren, m_fontsize, m_clickColor, m_label, m_posX, m_posY);
		//drawTextOrTexture(ren, m_clickColor, optionalTexture);
		//if (m_drawArrow > -1) drawArrow(ren, m_clickColor);
		drawRectFilled(ren, m_barColor, m_posX + (m_sizeX * m_sliderValue) - (m_knobWidth/2), m_posY, m_knobWidth, m_sizeY);
		m_sliderValue = (mouseX - m_posX)/static_cast<double>(m_sizeX);
		//indicate that the mouse click is being held
		m_holdingClick = true;

		//never allow the mouse to slide the slider into invalid values
		if (m_sliderValue < 0)
		{
			m_sliderValue = 0;
		}
		else if (m_sliderValue > 1)
		{
			m_sliderValue = 1;
		}
	}
	//if mouse is hovering over button, draw it in the highlight color instead of the text color
	else if (isMouseTouching(mouseX, mouseY))
	{
		drawRectFilled(ren, color(255,255,0), m_posX + (m_sizeX * m_sliderValue) - (m_knobWidth/2), m_posY, m_knobWidth, m_sizeY);
		//drawText(ren, m_fontsize, m_highlightColor, m_label, m_posX, m_posY);
		//drawTextOrTexture(ren, m_highlightColor, optionalTexture);
		//if (m_showBorder) drawRect(ren, m_highlightColor, m_posX, m_posY, m_sizeX, m_sizeY);
		//if (m_drawArrow > -1) drawArrow(ren, m_highlightColor);
	}
	else 
	{
		//if (m_showBorder) drawRect(ren, m_textColor, m_posX, m_posY, m_sizeX, m_sizeY);
		//drawText(ren, m_fontsize, m_textColor, m_label, m_posX, m_posY);
		//drawTextOrTexture(ren, m_textColor, optionalTexture);
		//if (m_drawArrow > -1) drawArrow(ren ,m_textColor);
		drawRectFilled(ren, color(0,255,255), m_posX + (m_sizeX * m_sliderValue) - (m_knobWidth/2), m_posY, m_knobWidth, m_sizeY);
	}

	if (m_holdingClick && lastmouse != SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		m_holdingClick = false;
	}

	//draw back bar at all times
	drawRect(ren, m_barColor, m_posX, m_posY, m_sizeX, m_sizeY);
}

//==============================================
//dial
//==============================================
dial :: dial()
{

}

dial :: dial(int size, int posX, int posY, int maxVal, SDL_Texture *texture, double minAngle, double maxAngle)
{
	m_radius = size;
	m_sizeX = size*2;
	m_sizeY = size*2;
	m_posX = posX;
	m_posY = posY;
	m_elementTexture = texture;
	m_dialColor = color(255,255,255,255);
	m_maxVal = maxVal;
	m_degreesOfLastClick = 0;
	m_minDegrees = minAngle;
	m_maxDegrees = maxAngle;
	m_dialTexture = generic_dial_needle;
}

dial :: dial(const dial& other)
{
	m_radius = other.getRadius();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_posX = other.posX();
	m_posY = other.posY();
	m_dialColor = getDialColor();
	m_elementTexture = other.getTexture();
	m_currentValue = other.value();
	m_maxVal = other.maxVal();
	m_degreesOfLastClick = 0;
	m_minDegrees = other.minDegrees();
	m_maxDegrees = other.maxDegrees();
	m_dialTexture = other.getDialTexture();
}

dial& dial :: operator=(const dial& other)
{
	m_radius = other.getRadius();
	m_sizeX = other.sizeX();
	m_sizeY = other.sizeY();
	m_posX = other.posX();
	m_posY = other.posY();
	m_dialColor = getDialColor();
	m_elementTexture = other.getTexture();
	m_currentValue = other.value();
	m_maxVal = other.maxVal();
	m_degreesOfLastClick = 0;
	m_minDegrees = other.minDegrees();
	m_maxDegrees = other.maxDegrees();
	m_dialTexture = other.getDialTexture();

	return *this;
}

//allows you to set a value manually
void dial :: setValue(double newValue)
{
	m_currentValue = newValue;
	m_degreesOfLastClick = newValue;
}

double dial :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	renderTextureEx(m_elementTexture, ren, m_posX, m_posY, m_sizeX, m_sizeY, 0);

	if (isColliding2D(m_posX, m_posY, m_sizeX, m_sizeY, mouseX, mouseY) && lastmouse == SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		//get center of dial in preparation for triginometric calculation
		int cx;
		int cy;
		getCenter(cx, cy);
		double xVal = mouseX - cx;
		double yVal = mouseY - cy;

		//never let it equal to zero or there will be a divide by zero crash
		if (xVal == 0) xVal = 0.00001;
		if (yVal == 0) yVal = 0.00001;

		double intermediateValue = atan((yVal)/(xVal)) * (180/3.141592);

		//when cursor is in lower left quadrant of dial
		if (xVal < 0 && yVal > 0) intermediateValue = 90 + intermediateValue;

		//when cursor is in upper left quadrant of dial
		else if (xVal < 0 && yVal < 0) intermediateValue = 90 + intermediateValue;

		//when cursor is in upper right quadrant of dial
		else if (xVal > 0 && yVal < 0) intermediateValue = 270 + intermediateValue;

		//when cursor is in lower right quadrant of dial
		else if (xVal > 0 && yVal > 0) intermediateValue = 270 + intermediateValue;

		m_degreesOfLastClick = intermediateValue;

		if (intermediateValue > m_maxDegrees) intermediateValue = m_maxDegrees;
		if (intermediateValue < m_minDegrees) intermediateValue = m_minDegrees;
		m_currentValue = (intermediateValue - m_minDegrees) / (m_maxDegrees - m_minDegrees) * m_maxVal;
	}

	int needlesizeX;
	int needlesizeY;
	int cx;
	int cy;
	getCenter(cx, cy);
	SDL_QueryTexture(m_dialTexture, NULL, NULL, &needlesizeX, &needlesizeY);

	//scale the needle's size so that it's the correct size for whatever size the dial background is
	needlesizeX = needlesizeX * (static_cast<double>(m_sizeY)/needlesizeY/static_cast<double>(1));
	needlesizeY = needlesizeY * (static_cast<double>(m_sizeY)/needlesizeY/static_cast<double>(1));

	renderTextureEx(m_dialTexture, ren, cx - (needlesizeX / 2), cy - (needlesizeY/2), needlesizeX, needlesizeY, m_degreesOfLastClick);


	return m_currentValue;
}

markerPoint :: markerPoint()
{

}

markerPoint :: markerPoint(double posX, double posY, int markerNum)
{
	m_worldPosX = posX;
	m_worldPosY = posY;
	m_caption = "mark #" + markerNum;
}

void markerPoint :: setPos(double x, double y)
{
	m_worldPosX = x;
	m_worldPosY = y;
}

int markerPoint :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, int correctX, int correctY, bool cursorHighlight)
{

	if (isColliding2D(correctX - 5, correctY - 5, 10, 10, mouseX, mouseY) && cursorHighlight)
	{
		drawLine(ren, color(100,100,100), correctX + 5, correctY - 5, correctX - 5, correctY + 5);
		drawLine(ren, color(100,100,100), correctX + 5,correctY + 5, correctX - 5, correctY - 5);
		return 1;
	}
	else
	{
		drawLine(ren, color(200,200,200), correctX + 5, correctY - 5, correctX - 5, correctY + 5);
		drawLine(ren, color(200,200,200), correctX + 5,correctY + 5, correctX - 5, correctY - 5);
		return 0;
	}
}

markerPoint& markerPoint :: operator=(const markerPoint& other)
{
	m_worldPosX = other.posX();
	m_worldPosY = other.posY();
	m_caption = other.getCaption();

	return *this;
}

rulerLine :: rulerLine()
{
	m_secondPointPlaced = false;
}

rulerLine :: rulerLine(double posX, double posY)
{
	m_worldPosX1 = posX;
	m_worldPosY1 = posY;
	m_secondPointPlaced = false;
}

rulerLine :: rulerLine(double posX1, double posY1, double posX2, double posY2)
{
	m_worldPosX1 = posX1;
	m_worldPosY1 = posY2;
	m_worldPosX2 = posX2;
	m_worldPosY2 = posY2;
	m_secondPointPlaced = true;

	//how that all the important stuff has been set, calculate the length between 2 points and update the object
	calculateDistance();
}

void rulerLine :: swapPoints()
{
	double tempX = m_worldPosX2;
	double tempY = m_worldPosY2;
	m_worldPosX2 = m_worldPosX1;
	m_worldPosY2 = m_worldPosY1;
	m_worldPosX1 = tempX;
	m_worldPosY1 = tempY;

	return void();
}


int rulerLine :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool lengthOnOtherEnd, bool cursorSelect)
{
	int stringSize;
	if (zoom >= 1.0f) stringSize = 7;
	else if (zoom < 1.0f && zoom >= 0.6f) stringSize = 6;
	else if (zoom < 0.6f && zoom >= 0.3f) stringSize = 5;
	else stringSize = 0;
	if (!m_secondPointPlaced)
	{
		m_worldPosX2 = mapToWorldX(zoom, mapCenterX, mouseX);
		m_worldPosY2 = mapToWorldY(zoom, mapCenterY, mouseY);
		calculateDistance();

		int x1 = worldToMapX(zoom, mapCenterX, m_worldPosX1*mapScale, mapSizeX, mapScale);
		int x2 = worldToMapX(zoom, mapCenterX, m_worldPosX2*mapScale, mapSizeX, mapScale);
		int y1 = worldToMapY(zoom, mapCenterY, m_worldPosY1*mapScale, mapSizeY, mapScale);
		int y2 = worldToMapY(zoom, mapCenterY, m_worldPosY2*mapScale, mapSizeY, mapScale);

		drawLine(ren, color(200,200,200), x1, y1, x2, y2);

		if (lengthOnOtherEnd)
		{
			//make the length draw on the other side
			x1 = x2;
			y1 = y2;
		}
		drawText(ren, stringSize, color(200,200,200), doubleToMeters(m_length*mapScale), x1, y1);
		if (isColliding2D(x1 - 5, y1 - 5, 10, 10, mouseX, mouseY) && cursorSelect)
		{
			return 1;
		}
	}
	else
	{
		int x1 = worldToMapX(zoom, mapCenterX, m_worldPosX1*mapScale, mapSizeX, mapScale);
		int x2 = worldToMapX(zoom, mapCenterX, m_worldPosX2*mapScale, mapSizeX, mapScale);
		int y1 = worldToMapY(zoom, mapCenterY, m_worldPosY1*mapScale, mapSizeY, mapScale);
		int y2 = worldToMapY(zoom, mapCenterY, m_worldPosY2*mapScale, mapSizeY, mapScale);

		drawLine(ren, color(200,200,200), x1, y1, x2, y2);
		if (lengthOnOtherEnd)
		{
			//make the length draw on the other side
			//int tempx = x1;
			//int tempy = y1;
			x1 = x2;
			y1 = y2;
			//x2 = x1;
			//y2 = y1;
		}
		drawText(ren, stringSize, color(200,200,200), doubleToMeters(m_length*mapScale), x1, y1);

		if ((isColliding2D(x1 - 5, y1 - 5, 10, 10, mouseX, mouseY) || isColliding2D(x2 - 5, y2 - 5, 10, 10, mouseX, mouseY)) && cursorSelect)
		{
			return 1;
		}
	}


	return 0;
}

void rulerLine :: calculateDistance()
{
	double a_squared = pow(m_worldPosX1 - m_worldPosX2, 2);
	double b_squared = pow(m_worldPosY1 - m_worldPosY2, 2);

	m_length = sqrt(a_squared + b_squared);

	return void();
}

rulerLine& rulerLine :: operator=(const rulerLine& other)
{
	m_worldPosX1 = other.posX1();
	m_worldPosX2 = other.posX2();
	m_worldPosY1 = other.posY1();
	m_worldPosY2 = other.posY2();
	m_secondPointPlaced = other.secondPointPlaced();
	m_length = other.distance();

	return *this;
}

protractorAngle :: protractorAngle()
{
	m_secondLinePlaced = false;
}

protractorAngle :: protractorAngle(double posX1, double posY1)
{
	m_firstLine = rulerLine(posX1, posY1);
	m_secondLinePlaced = false;
}

int protractorAngle :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool cursorSelect)
{
	bool l1col = false;
	bool l2col = false;
	int stringSize;
	if (zoom >= 1.0f) stringSize = 7;
	else if (zoom < 1.0f && zoom >= 0.6f) stringSize = 6;
	else if (zoom < 0.6f && zoom >= 0.3f) stringSize = 5;
	else stringSize = 0;

	l1col = m_firstLine.draw(ren, mouseX, mouseY, lastMouse, zoom, mapCenterX, mapCenterY, mapScale, mapSizeX, mapSizeY, false, cursorSelect);
	if (!firstLinePlaced()) 
	{
		calculateAngle();
		double anglePosX = worldToMapX(zoom,mapCenterX, m_firstLine.posX1()*mapScale, mapSizeX, mapScale);
		double anglePosY = worldToMapY(zoom,mapCenterY, (m_firstLine.posY1())*mapScale, mapSizeY, mapScale)-20;
		drawText(ren, stringSize, color(200,200,200), to_string(m_angle), anglePosX, anglePosY);
	}
	if (m_firstLine.secondPointPlaced())
	{
		if (!m_secondLine.secondPointPlaced()) calculateAngle();
		//m_secondLine.swapPoints();
		double anglePosX = worldToMapX(zoom,mapCenterX, m_firstLine.posX2()*mapScale, mapSizeX, mapScale);
		double anglePosY = worldToMapY(zoom,mapCenterY, m_firstLine.posY2()*mapScale, mapSizeY, mapScale);
		l2col = m_secondLine.draw(ren, mouseX, mouseY, lastMouse, zoom, mapCenterX, mapCenterY, mapScale, mapSizeX, mapSizeY, true, cursorSelect);
		drawText(ren, stringSize, color(200,200,200), to_string(m_angle), anglePosX, anglePosY);
		//m_secondLine.swapPoints();
	}

	if (l1col || l2col) return 1;
	else return 0;
}

void protractorAngle :: protractorAngle :: calculateAngle()
{
	//doesn't work (not even close)
	//double length1 = m_firstLine.distance();
	//double length2 = m_secondLine.distance();
	//m_angle = tan(length1/length2);
	//cout << "angle = " << m_angle << endl;

	//doesn't work
	/*float dx21 = m_firstLine.posX2()-m_firstLine.posX1();
	float dx31 = m_secondLine.posX2()-m_firstLine.posX1();
	float dy21 = m_firstLine.posY2()-m_firstLine.posY1();
	float dy31 = m_secondLine.posY2()-m_firstLine.posY1();
	float m12 = sqrt( dx21*dx21 + dy21*dy21 );
	float m13 = sqrt( dx31*dx31 + dy31*dy31 );
	float theta = acos( (dx21*dx31 + dy21*dy31) / (m12 * m13) );
	m_angle = theta * 180.0 / 3.1415926535897932384626; //make sure to use enough digits of pi*/

	//this works but there's no way to display more than 90 degree angles without doing a LOT of if statements and first finding what conditions point 1, 2 and 3 would have to do in order to make it calculatable.
	//if I had weed, I would do this but I don't, so I don't have the patience for that so I'm finding a different solution
	//calculate the slopes of each line
	/*double m1 = (m_firstLine.posX2() - m_firstLine.posX1())/(m_firstLine.posY2() - m_firstLine.posY1());
	double m2 = (m_secondLine.posX2() - m_secondLine.posX1())/(m_secondLine.posY2() - m_secondLine.posY1());
	double m3 = (m_firstLine.posX1() - m_firstLine.posX2())/(m_firstLine.posY1() - m_firstLine.posY2());
	double m4 = (m_secondLine.posX1() - m_secondLine.posX2())/(m_secondLine.posY1() - m_secondLine.posY2());
	double val1 = (1+m1*m2);
	double val2 =  m2-m1;
	double val3 = (1-m3*m4);
	double val4 =  m4-m3;
	double theta = atan((val2/val1)) * 180 / 3.1415926535897932384626;
	double theta2 = atan((val4/val3)) * 180 / 3.1415926535897932384626;
	m_angle = theta;
	cout << "theta = " << 180-(theta) << " theta 2 = " << theta2 << endl;*/
	if (firstLinePlaced())
	{
		double angle = angleBetweenLinesInRadians(m_firstLine, m_secondLine);
		if (angle >= 180) m_angle = angle - 180;
		else if (angle < 180) m_angle = 180 - angle;
	}
	else
	{
		/*double m1 = (m_firstLine.posX2() - m_firstLine.posX1())/(m_firstLine.posY2() - m_firstLine.posY1());
		double m2 = ((m_firstLine.posX1()) - m_firstLine.posX1())/((m_firstLine.posY1()+5) - m_firstLine.posY1());

		double val1 = (1+m1*m2);
		double val2 =  m2-m1;
		double angle = atan((val2/val1)) * 180 / 3.1415926535897932384626;*/
		rulerLine tempLine(m_firstLine.posX1(), m_firstLine.posY1(), m_firstLine.posX1(), m_firstLine.posY1() + 10);
		double angle = angleBetweenLinesInRadians(m_firstLine, tempLine);
		angle += 270;
		if (angle >= 360) angle = angle - 360;
		//else if (angle < 180) m_angle = 180 - angle;
		m_angle = angle;

	}

	//attempt 4.. maybe a double dot product then get the difference of the 2 of them?
	//nope. Doesn't function as the internet claimed it does. Does not seem to calculate angles
	//double dot = (m_firstLine.posX2() * m_secondLine.posX2())
	/*double x1 = m_firstLine.posX1();
	double x2 = m_firstLine.posX2();
	double x3 = m_secondLine.posX2();
	double y1 = m_firstLine.posY1();
	double y2 = m_firstLine.posY2();
	double y3 = m_secondLine.posY2();

	double dot1 = x1*x2 + y1*y2;
	double det1 = x1*y2 - y1*x2;
	double angle1 = atan2(det1, dot1) * 180 / 3.1415926535897932384626;

	double dot2 = x3*x2 + y3*y2;
	double det2 = x3*y2 - y3*x2;
	double angle2 = atan2(det2, dot2) * 180 / 3.1415926535897932384626;
	cout << "angle1 = " << angle1 << " angle 2 = " << angle2 << endl;*/


}

protractorAngle& protractorAngle :: operator=(const protractorAngle& other)
{
	m_firstLine = other.getFirstLine();
	m_secondLine = other.getSecondLine();
	m_angle = other.getAngle();
	m_secondLinePlaced = m_secondLine.secondPointPlaced();

	return *this;
}

compassCircle :: compassCircle()
{

}

compassCircle :: compassCircle(double posX, double posY)
{
	//use the line's built-in constructor to create a new line in a hopefully non-buggy way
	m_theLine = rulerLine(posX, posY);
}

int compassCircle :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastMouse, double zoom, double mapCenterX, double mapCenterY, double mapScale, int mapSizeX, int mapSizeY, bool cursorSelect)
{
	bool collision = false;
	if (m_theLine.draw(ren, mouseX, mouseY, lastMouse, zoom, mapCenterX, mapCenterY, mapScale, mapSizeX, mapSizeY, false, cursorSelect))
	{
		collision = true;
	}
	
	double x = worldToMapX(zoom, mapCenterX, m_theLine.posX1()*mapScale, mapSizeX, mapScale);
	double y = worldToMapY(zoom, mapCenterY, m_theLine.posY1()*mapScale, mapSizeY, mapScale);
	drawEmptyCircle(ren, color(200,200,200), m_theLine.distance()*zoom, x, y);

	return collision;
}

compassCircle& compassCircle :: operator=(const compassCircle& other)
{
	m_theLine = other.getLine();

	return *this;
}

//it actually outputs in degrees not radians
double angleBetweenLinesInRadians(rulerLine line1, rulerLine line2)
{
	double angle1 = atan2(line1.posY1()-line1.posY2(), line1.posX2()-line1.posX1());
	double angle2 = atan2(line2.posY1()-line2.posY2(), line2.posX2()-line2.posX1());

	double result = (angle2-angle1) * 180 / 3.14;
	if (result<0) 
	{
    	result+=360;
	}
	
	return result;

}

//====================================================
//sideScroll class ui element stuff
//====================================================
sideScroll :: sideScroll()
{
	m_background = true;	//have a background by default
	m_backgroundColor = color(0, 0, 0, 150);
	m_posX = 0;
	m_posY = 0;
	//m_sizeX = 50;
	m_sizeY = 50;
	m_fontsize = 8;
	m_showBorder = false;	//no border by default
	m_tooltip = "N/A";
	m_selectedIndex = 0;
	m_elements.clear();
}

sideScroll :: sideScroll(int posX, int posY, int fontSize, int width)
{
	m_fontsize = fontSize;
	m_maxChars = width;

	m_background = true;	//have a background by default
	m_backgroundColor = color(0, 0, 0, 150);
	m_posX = posX;
	m_posY = posY;
	m_sizeY = getTextYSize(fontSize);
	m_showBorder = false;	//no border by default
	m_tooltip = "N/A";
	m_selectedIndex = 0;
	m_elements.clear();

	//now that all the basic data required for operation is set up, create button objects
	m_leftButton = button(" ", color(255, 255, 255, 255), posX, posY, fontSize);
	m_rightButton = button(" ", color(255, 255, 255, 255), posX, posY, fontSize);
	
	//set default button properties
	m_leftButton.setArrow(3);	//make arrow point left
	m_rightButton.setArrow(1);	//make right arrow point right

	//setting the font size also sets the position of the right button
	setFontSize(fontSize);
}

sideScroll :: sideScroll(const sideScroll& other)
{
	m_background = other.hasBackground();
	m_backgroundColor = other.backgroundColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_showBorder = other.hasBorder();
	m_tooltip = other.getTooltip();
	m_selectedIndex = other.getIndex();
	m_maxChars = other.maxChars();

	m_leftButton = other.leftButtonConst();
	m_rightButton = other.rightButtonConst();

	//now that we have all the information, set the font size to a thing
	setFontSize(m_fontsize);

	//do list stuff
	m_selectedIndex = 0;
	//m_elements = vector<coloredString>();
	//m_elements.clear();

	//now that we have all the information, set the font size to a thing
	setFontSize(m_fontsize);
}

sideScroll& sideScroll :: operator=(const sideScroll& other)
{
	m_background = other.hasBackground();
	m_backgroundColor = other.backgroundColor();
	m_posX = other.posX();
	m_posY = other.posY();
	m_sizeY = other.sizeY();
	m_fontsize = other.fontsize();
	m_showBorder = other.hasBorder();
	m_tooltip = other.getTooltip();
	m_selectedIndex = other.getIndex();
	m_maxChars = other.maxChars();

	m_leftButton = other.leftButtonConst();
	m_rightButton = other.rightButtonConst();

	//now that we have all the information, set the font size to a thing
	setFontSize(m_fontsize);

	//do list stuff
	m_selectedIndex = 0;
	//m_elements = vector<coloredString>();
	//m_elements.clear();

	//return the reference to the object
	return *this;
}

int sideScroll :: sizeX() const
{
	int textSizeX = getTextXSize(m_fontsize, m_maxChars);
	return m_leftButton.sizeX() + 10 + textSizeX + 10 + m_rightButton.sizeX();
}

void sideScroll :: setFontSize(int size)
{
	//first set the font size to whats its supposed to be set to
	m_fontsize = size;
	m_sizeY = 80 * m_fontsize / 24;		//size y gets derived the same size as buttons pretty much. size x is what's different

	//set font size of each button using their built-in member functions. yay, i dont have to think very hard about this one. Thanks, past me
	m_leftButton.setFontSize(size);
	m_rightButton.setFontSize(size);
	int textSizeX = getTextXSize(m_fontsize, m_maxChars);

	//derive horizontal spacing now that we have most of the hard math stuff finished
	//m_sizeX = m_leftButton.sizeX() + 20 + textSizeX + 
	//set new position of buttons to match new size. left buttons stays where it is
	m_rightButton.setPos(m_posX + 20 + textSizeX + m_leftButton.sizeX(), m_posY);

	return void();
}

void sideScroll :: addItem(coloredString item)
{
	m_elements.push_back(item);
}

void sideScroll :: setPos(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
	m_leftButton.setPos(posX, posY);
	setFontSize(m_fontsize);
}

//draw the object. returns selected index
int sideScroll :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse)
{
	//if left arrow button is pressed, decrement the counter but only do so if it wont cause a crash
	if (m_leftButton.draw(ren, mouseX, mouseY, lastmouse, nullptr) && m_selectedIndex > 0)
	{
		m_selectedIndex--;
	}
	
	//if right arrow button is pressed, increment the counter but only if it wont cause a crash
	if (m_rightButton.draw(ren, mouseX, mouseY, lastmouse, nullptr) && m_selectedIndex < m_elements.size() - 1)
	{
		m_selectedIndex++;
	}

	//draw the background if enabled
	if (m_background)
	{
		int backgroundX = m_posX + m_leftButton.sizeX() + 10;
		drawRectFilled(ren, m_backgroundColor, backgroundX, m_posY, sizeX() - (m_rightButton.sizeX()*2) - 20, m_sizeY);
	}

	//draw the list if applicable
	//cout << "m_elements.size() = " << m_elements.size() << endl;
	//cout << "m_selectedIndex = " << m_selectedIndex << endl;
	if (m_elements.size() > 0 && m_selectedIndex < m_elements.size())
	{
		int textStartX = m_posX + m_leftButton.sizeX() + 12;
		//cout << "textStartX = " << textStartX << endl;
		//drawText(ren, textStartX, m_elements.at(0), textStartX, m_posY);
		//cout << m_elements.at(0).atPos(0).getText() << endl;
		
		/*it mysteriously fails for no reason when i use the tried and true draw text function that never has never fucking failed before
		but when I copy in the body of the draw text function WHICH IS THE SAME FUCKING CODE (just with variable names swapped out) it
		mysteriously works. Fucking. Bullshit.
		*/
		int offsetX = 0;
		for (int i = 0; i < m_elements.at(m_selectedIndex).size(); i++)
		{
			//manually draw the color string because fuck it
			string temp = m_elements.at(m_selectedIndex).atPos(i).getText();
			color tempColor = m_elements.at(m_selectedIndex).atPos(i).getColor();
			drawText(ren, m_fontsize, tempColor, temp, textStartX + offsetX, m_posY);
			offsetX += getTextXSize(m_fontsize, temp.size());
		}
	}

	//cout << "m_fontsize = " << m_fontsize << endl;
	//cout << "m_selectedIndex = " << m_selectedIndex << endl;

	//return 0 for testing purposes. will need to return index of selected item eventually
	return m_selectedIndex;
}