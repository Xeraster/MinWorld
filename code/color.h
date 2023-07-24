#ifndef COLOR_H
#define COLOR_H

//converts a char that is in base 16 to a base 10 int
int charToHex(char input);
int charToHex(char input)
{
	int al = input - 48;
	if (al > 9)
	{
		al -= 7;
	}
	if (al > 15)
	{
		al -= 32;
	}

	return al;
}

//converts a 2 character string that is in hex format to an int. The supposed c++ functions that "work" don't actually work so I have to do it the old fashioned way
int stringToHex(string input);
int stringToHex(string input)
{
	//wow, like, you *really* have to do it the old fashioned way
	//string lin = tolower(input.at(0));//convert to lowercase to make there be less if statements.. nope doesn't work
	int newNum = (charToHex(input.at(0))*16) + charToHex(input.at(1));
	return newNum;
}

class color
{
public:
	color();

	color(Uint8 r, Uint8 g, Uint8 b);

	color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	//create a color from a 6 character string of hex values
	color(string hex);

	Uint8 getRed() const;
	Uint8 getGreen() const;
	Uint8 getBlue() const;
	Uint8 getAlpha() const;

	void setRed(Uint8 value) { red = value; }
	void setGreen(Uint8 value) { green = value; }
	void setBlue(Uint8 value) { blue = value; }
	void setAlpha(Uint8 value) { alpha = value; }

	color operator=(const color& rhs);

	color operator*(const color& rhs); //multiplication operator for 3d shading purposes

	color operator*(const float& rhs); //multiplication operator for 3d shading purposes

	bool operator==(const color& rhs);

protected:
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;

};

//a faster, more stripped down color for best possible 3d performance
class color24
{
public:
	color24();

	color24(Uint8 r, Uint8 g, Uint8 b);

	Uint8 getRed() const;
	Uint8 getGreen() const;
	Uint8 getBlue() const;

	void setRed(Uint8 value) { red = value; }
	void setGreen(Uint8 value) { green = value; }
	void setBlue(Uint8 value) { blue = value; }

	color24 operator=(const color24& rhs);

	color24 operator*(const color24& rhs); //multiplication operator for 3d shading purposes

	bool operator==(const color24& rhs);

protected:
	int red;
	int green;
	int blue;
	int alpha;

};

//<< opertors not having them sucks so much fucking ass
ostream& operator<<(ostream& os, const color& rhs)
{
	os << to_string(rhs.getRed()) << "," << to_string(rhs.getGreen()) << "," << to_string(rhs.getBlue());

	return os;
}

ostream& operator<<(ostream& os, const color24& rhs)
{
	os << to_string(rhs.getRed()) << "," << to_string(rhs.getGreen()) << "," << to_string(rhs.getBlue());

	return os;
}

#include "color.hpp"

#endif