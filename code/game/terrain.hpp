terrain :: terrain()
{

}

terrain :: terrain(XMLElement *terrainElement, SDL_Renderer *ren)
{
    m_defName = terrainElement->FirstChildElement("defName")->GetText();
    m_label = terrainElement->FirstChildElement("label")->GetText();
    m_description = terrainElement->FirstChildElement("description")->GetText();
    //m_mapColor = biomeElement->FirstChildElement("description")->GetText();

    m_movementSpeed = atof(terrainElement->FirstChildElement("movementSpeed")->GetText());
    m_commonality = atof(terrainElement->FirstChildElement("commonality")->GetText());

    m_beauty = atof(terrainElement->FirstChildElement("beauty")->GetText());
    m_fertility = atof(terrainElement->FirstChildElement("fertility")->GetText());
    //cout << m_defName << " fertility=" << m_fertility << endl;

    string textureName = terrainElement->FirstChildElement("texture")->GetText();
    //cout << "texture name=" << textureName << endl;
    tex = loadTextureToRam("Textures/"+textureName, ren);
    // loadSpecificTexture(textureName, m_defName + "_terrain_tex", ren);
    // tex = findTextureByName(textureName + "_terrain_tex", textureDatabase);
    // tex = *textureDatabase->back();

    //this shit doesn't work
    if (m_defName == "SkyBlock")
    {
        skyNullBlock = this;
        cout << "assigned SkyBlock to global pointer" << endl;
        cout << "skynullblock def = " << skyNullBlock->defName() << endl;
    }
}

void terrain :: testDraw(SDL_Renderer *ren, SDL_Window *win)
{
    renderTextureEx(tex, ren, 50, 50, 128, 128, 0);
    drawPixel(ren, 50, 50, color(255,255,255));
}

terrain& terrain :: operator=(terrain& other)
{
    cout << "fjakfafa" << endl;
}

void loadAllTerrain(SDL_Renderer *ren)
{
    string dataPath = "Data/Terrain";
    vector<string> filePaths;

    for (const auto & entry : std::filesystem::directory_iterator(dataPath))
	{
        //load everything xml or not because fuck the feds
        std::cout << entry.path() << std::endl;
        filePaths.push_back(entry.path());
	}

    for (int i = 0; i < filePaths.size(); i++)
    {
        XMLDocument doc;
        doc.LoadFile(filePaths.at(i).c_str());

        if (doc.RootElement() == nullptr)
	    {
		    cout << "warning: a terrain xml file with no root element got loaded for some reason" << endl;
	    }

        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *terrainToLoad = rootElement->FirstChildElement("TerrainDef");
        while (terrainToLoad != nullptr)
        {
            terrain newTerrain(terrainToLoad, ren);
            terrainDatabase.push_back(newTerrain);
            terrainToLoad = terrainToLoad->NextSiblingElement("TerrainDef");
            cout << "loading terrain" << endl;
        }
    }
}

terrain* getTerrainByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (terrainDatabase.at(i).defName() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &terrainDatabase.at(i);
}