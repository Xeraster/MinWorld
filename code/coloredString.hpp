colorStringKey :: colorStringKey()
{
	color white(255,255,255,255);
	m_text = "";
	m_stringColor = white;
} 

colorStringKey& colorStringKey :: operator=(const colorStringKey& other)
{
	m_text = other.getText();
	m_stringColor = other.getColor();
}

coloredString :: coloredString()
{
	coloredStrings = new vector<colorStringKey>();
}

coloredString :: coloredString(string text, color stringColor)
{
	coloredStrings = new vector<colorStringKey>();
	colorStringKey newColorString;
	newColorString.setColor(stringColor);
	newColorString.setText(text);

	coloredStrings->push_back(newColorString);
}

coloredString :: coloredString(char *text)
{
	coloredStrings = new vector<colorStringKey>();
	colorStringKey newColorString;
	newColorString.setText(text);

	coloredStrings->push_back(newColorString);
}

coloredString :: coloredString(string text)
{
	coloredStrings = new vector<colorStringKey>();
	colorStringKey newColorString;
	newColorString.setText(text);

	coloredStrings->push_back(newColorString);
}

coloredString :: ~coloredString()
{
	//valgrind claims no additional memory leaks added by not having this
	//i'm stil skeptical though
	//delete coloredStrings;
}

colorStringKey coloredString :: atPos(int index) const
{
	return coloredStrings->at(index);
}

void coloredString :: setColor(int index, color newColor)
{
	coloredStrings->at(index).setColor(newColor);
}

void coloredString :: appendColorString(string newString, color newColor)
{
	colorStringKey newcs;
	newcs.setText(newString);
	newcs.setColor(newColor);

	coloredStrings->push_back(newcs);
}

coloredString& coloredString :: operator=(const coloredString& other)
{
	delete coloredStrings;
	coloredStrings = new vector<colorStringKey>();
	for (int i = 0; i < other.size(); i++)
	{
		coloredStrings->push_back(other.atPos(i));
	}

	return *this;
}

coloredString& coloredString :: operator=(const string& other)
{
	delete coloredStrings;
	coloredStrings = new vector<colorStringKey>();

	colorStringKey newColorString;
	newColorString.setText(other);

	coloredStrings->push_back(newColorString);

	return *this;
}

coloredString& coloredString :: operator=(const char* other)
{
	delete coloredStrings;
	coloredStrings = new vector<colorStringKey>();

	colorStringKey newColorString;
	string theString = other;
	newColorString.setText(theString);

	coloredStrings->push_back(newColorString);

	return *this;
}

coloredString& coloredString :: operator +=(const coloredString& other)
{
	for (int i = 0; i < other.size(); i++)
	{
		coloredStrings->push_back(other.atPos(i));
	}

	return *this;
}

coloredString& coloredString :: operator +=(const string& other)
{
	colorStringKey newstring;
	newstring.setText(other);

	coloredStrings->push_back(newstring);

	return *this;
}

coloredString& coloredString :: operator +=(char *other)
{
	colorStringKey newstring;
	newstring.setText(other);

	coloredStrings->push_back(newstring);

	return *this;
}

coloredString coloredString :: operator+(const coloredString &other) const
{
	coloredString temp = *this;
	temp += other;

	return temp;
}

coloredString coloredString :: operator+(const string &other) const
{
	coloredString temp = *this;
	temp += other;

	return temp;
}