#ifndef TEXTUREENTRY_H
#define TEXTUREENTRY_H

class textureEntry
{
	public:
		textureEntry();
		textureEntry(string texturePath, string name, SDL_Renderer *ren);
		textureEntry(SDL_Texture *newTex, string name);
		~textureEntry();

		string getName() { return m_name; }
		void setName(string newName) { m_name = newName; }
		SDL_Texture* getTexture() { return tex; }

		textureEntry& operator=(textureEntry& other);
		SDL_Texture *tex;
	private:

		string m_name;
};

SDL_Texture *errorTexture;

vector<textureEntry*> *textureDatabase = new vector<textureEntry*>;

int textureDirectoryIntoDatabase(string filePath, SDL_Renderer *ren);

int loadSpecificTexture(string texPath, string customName, SDL_Renderer *ren);

//includes anti-crash code (returns nullptr if texture with name not found)
//should work. not tested yet as of 03/26/2021 at 10:08am
SDL_Texture* findTextureByName(string texName, vector<textureEntry*> *texPointer);

//figure out if texture exists. If so, return true. If no, return false;
bool textureExists(string texName, vector<textureEntry*> *texPointer);

ostream& operator<<(ostream& os, textureEntry texture);

#include "textureEntry.hpp"

#endif