textureEntry :: textureEntry()
{

}

textureEntry :: textureEntry(string texturePath, string name, SDL_Renderer *ren)
{
	m_name = name;

	//SDL_Surface *bmp = SDL_LoadBMP(texturePath.c_str());

	//slower but neccesary
	SDL_Surface *bmp = IMG_Load(texturePath.c_str());

	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
}

textureEntry :: ~textureEntry()
{
	SDL_DestroyTexture(tex);
}

textureEntry& textureEntry :: operator=(textureEntry& other)
{
	m_name = other.getName();
//	SDL_RenderCopy(tex, other.getTexture());

	return *this;
}

int textureDirectoryIntoDatabase(string filePath, SDL_Renderer *ren)
{
	vector<string> filePaths;
	for (const auto & entry : std::filesystem::directory_iterator(filePath))
	{
        //only do the operations for bmp files
        //this way I can keep this directory cluttered with dev crap

        //modified to load bmp and png file formats instead of just bmp
        if (entry.path().generic_string().substr(entry.path().generic_string().size() - 3, entry.path().generic_string().size()) == "bmp" || entry.path().generic_string().substr(entry.path().generic_string().size() - 3, entry.path().generic_string().size()) == "png")
        {
        	cout << entry.path().filename() << endl;
        	textureDatabase->push_back(new textureEntry(entry.path().generic_string(), entry.path().filename().generic_string(),ren));

        	//textureDatabase->push_back(new textureEntry(entry.path().generic_string(), entry.path().filename().generic_string(), ren));
       		//cout << entry.path().generic_string().substr(entry.path().generic_string().size() - 3, entry.path().generic_string().size());
        }
        //filePaths.push_back(entry.path());
	}

	return 0;
}

int loadSpecificTexture(string texPath, string customName, SDL_Renderer *ren)
{
	textureDatabase->push_back(new textureEntry(texPath, customName, ren));
	return 0;
}

//should work. not tested yet as of 03/26/2021 at 10:08am
SDL_Texture* findTextureByName(string texName, vector<textureEntry*> *texPointer)
{
	int maxSize = texPointer->size();
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < maxSize)
	{
		if (texPointer->at(i)->getName() == texName)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	if (foundMatch) return texPointer->at(i)->tex;
	else return nullptr;	//return null pointer instead of crash
}

//figure out if texture with provided name exists.
bool textureExists(string texName, vector<textureEntry*> *texPointer)
{
	int maxSize = texPointer->size();
	bool foundMatch = false;
	int i = 0;
	while (!foundMatch && i < maxSize)
	{
		if (texPointer->at(i)->getName() == texName)
		{
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return foundMatch;
}

ostream& operator<<(ostream& os, textureEntry texture)
{
	os << "texture name: " << texture.getName();

	return os;
}