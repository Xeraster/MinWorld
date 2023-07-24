#ifndef COLOREDSTRING_H
#define COLOREDSTRING_H

class colorStringKey
{
public:
	colorStringKey();

	color getColor() const { return m_stringColor; }
	void setColor(color newColor) { m_stringColor = newColor; }

	string getText() const { return m_text; }
	void setText(string newText) { m_text = newText; }

	colorStringKey& operator=(const colorStringKey& other);

private:
	color m_stringColor;
	string m_text;

};

class coloredString
{
public:
	coloredString();

	coloredString(string text, color stringColor);

	coloredString(char *text);

	coloredString(string text);

	~coloredString();

	colorStringKey atPos(int index) const;

	void setColor(int index, color newColor);

	int size() const { return coloredStrings->size(); }

	void appendColorString(string newString, color newColor);

	coloredString& operator=(const coloredString& other);

	coloredString& operator=(const string& other);

	coloredString& operator=(const char* other);

	coloredString& operator +=(const coloredString& other);

	coloredString& operator +=(const string& other);

	coloredString& operator +=(char *other);

	coloredString operator+(const coloredString &other) const;

	coloredString operator+(const string &other) const;

private:
	vector<colorStringKey> *coloredStrings;

};

#include "coloredString.hpp"
#endif