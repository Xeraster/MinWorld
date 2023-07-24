devConsole :: devConsole()
{
	//color consoleColor(0,255,0);
	//coloredString welcome("Welcome to the console", consoleColor);
	coloredString welcome("Welcome", color(255,127,0));
	welcome += coloredString(" to the ", color(120,150,255));
	welcome += coloredString("console", color(0,255,0));
	m_consoleOutput.push_front(welcome);
	//m_consoleOutput.push_front("Welcome to the console");

	color bkg(25,25,25,200);
	color txt(24,240,24,255);
	m_backgroundColor = bkg;
	m_textColor = txt;
	m_enterDeAssertedYet = true;
	m_showConsole = false;

	textbox temp("", m_textColor, 0, 0, 8, 255);
	m_inputLine = temp;
}

void devConsole :: draw(SDL_Renderer *ren, int mouseX, int mouseY, Uint32 lastmouse, int screenSizeX, int screenSizeY)
{
	//I added this to prevent the console from inserting the tilde key every time the user closes it with tildo
	if (lastCharTyped == "`" && m_showConsole)
	{
		m_inputLine.deselect();
	}

	if (m_showConsole)
	{
		drawRectFilled(ren, m_backgroundColor, 0, 0, m_screenX, m_screenY / 2);

		//draw each of the lines of text in the list
		list<coloredString> copied(m_consoleOutput);
		for (int i = 0; i < m_consoleOutput.size(); i++)
		{
			//drawText(ren, m_textSize, m_textColor, copied.front(), 10, (m_screenY / 2) - ((i+2)*(80 * m_textSize / 24)));
			drawText(ren, m_textSize, copied.front(), 10, (m_screenY / 2) - ((i+2)*(80 * m_textSize / 24)));
			copied.pop_front();
		}

		string currentText = m_inputLine.draw(ren, mouseX, mouseY, lastmouse);
		if (enterAsserted && m_enterDeAssertedYet)
		{
			if (parseInput(currentText)) m_inputLine.replaceText("");
			m_enterDeAssertedYet = false;
		}

		if (!enterAsserted && ! m_enterDeAssertedYet)
		{
			m_enterDeAssertedYet = true;
		}
	}

	if (lastCharTyped == "`")
	{
		m_showConsole = !m_showConsole;
		if (m_showConsole) m_inputLine.select();
		else if (!m_showConsole) m_inputLine.deselect();
	}
}

void devConsole :: setScreenSize(int x, int y) 
{ 
	m_screenX = x;
	m_screenY = y;

	//use 800x600 to establish the base ratio
	m_textSize = 8 * (m_screenY / 600);

	int textHeight = (80 * m_textSize / 24);
	int consoleY = m_screenY / 2;
	m_numLines = consoleY / textHeight;

	textbox temp("", m_textColor, 0, 0, m_textSize, 255);
	m_inputLine = temp;
	m_inputLine.setPos(0, consoleY - textHeight);

	cout << "number of console lines based on screen size and provided text size is " << m_numLines << endl;
}

void devConsole :: printString(string stringToPrint)
{
	appendTextToConsole(stringToPrint);
}

void devConsole :: saveGame(string input)
{

	if (!isIngame())
	{
		throwError("not in game");
		return void();
	}
	else
	{
		//TODO: make it do more filtering out of invalid filenames
		if (input.size() < 3) input = "you_are_an_idiot";
		//int result = saveToXml(input, playerCampaignInfo);
		int result = 1;

		if (result == 0)
		{
			coloredString msg = "Game has been ";
			msg += coloredString("saved", color(255,255,100));
			appendTextToConsole(msg);
		}
		else
		{
			coloredString msg = "Game save function ";
			msg += coloredString("reported an error", color(255,100,100));
			appendTextToConsole(msg);
		}
	}
}

bool devConsole :: parseInput(string input)
{
	if (input.substr(0, 6) == "print ")
	{
		printString(input.substr(6, input.size()));
		return true;
	}
	else if (input.substr(0, 3) == "420")
	{
		appendTextToConsole("420? lol nice");
		return true;
	}
	else if (input.substr(0, 2) == "69")
	{
		appendTextToConsole("69? lol nice");
		return true;
	}
	else if (input.substr(0,8) == "savegame")
	{
		saveGame(input.substr(8, input.size()));
		return true;
	}
	//appendTextToConsole(input);
	return false;
}

/*void devConsole :: appendTextToConsole(string text)
{
	coloredString convertedString = text;
	m_consoleOutput.push_front(convertedString);
	if (m_consoleOutput.size() > m_numLines)
	{
		m_consoleOutput.pop_back();
	}
}*/

void devConsole :: appendTextToConsole(coloredString text)
{
	//coloredString convertedString = text;
	m_consoleOutput.push_front(text);
	if (m_consoleOutput.size() > m_numLines)
	{
		m_consoleOutput.pop_back();
	}
}

void devConsole :: throwError(string reason)
{
	coloredString errormsg("Error: ", color(255,20,20));
	errormsg += coloredString(reason, color(255,255,100));
	appendTextToConsole(errormsg);
}