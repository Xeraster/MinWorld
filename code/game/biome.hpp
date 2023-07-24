biome :: biome()
{

}

biome :: biome(XMLElement *biomeElement)
{
    m_defName = biomeElement->FirstChildElement("defName")->GetText();
    m_label = biomeElement->FirstChildElement("label")->GetText();
    m_description = biomeElement->FirstChildElement("description")->GetText();
    //m_mapColor = biomeElement->FirstChildElement("description")->GetText();
    m_survivabilty = atof(biomeElement->FirstChildElement("survivability")->GetText());
    m_commonality = atof(biomeElement->FirstChildElement("commonality")->GetText());

    m_tempMin = atof(biomeElement->FirstChildElement("tempMin")->GetText());
    m_tempMax = atof(biomeElement->FirstChildElement("tempMax")->GetText());

    m_moveDifficulty = atof(biomeElement->FirstChildElement("movementDiff")->GetText());
    m_forageability = atof(biomeElement->FirstChildElement("forageability")->GetText());
    m_diseaseFrequency = atof(biomeElement->FirstChildElement("diseaseFrequency")->GetText());

    m_wind = atof(biomeElement->FirstChildElement("wind")->GetText());
    m_water = atof(biomeElement->FirstChildElement("water")->GetText());
    m_clouds = atof(biomeElement->FirstChildElement("clouds")->GetText());

    m_elevation = atof(biomeElement->FirstChildElement("elevationVariance")->GetText());
    
    //get all the biome's valid terrain blocks
    XMLElement *terrainTags = biomeElement->FirstChildElement("terrainTypes");
    XMLElement *li = terrainTags->FirstChildElement("li");
    while (li != nullptr)
    {
        terrainEntry newEntry;
        newEntry.commonality = atof(li->FirstChildElement("commonality")->GetText());
        //cout << li->FirstChildElement("terrainDef")->GetText() << endl;
        newEntry.terrainType = getTerrainByDefName(li->FirstChildElement("terrainDef")->GetText());
        terrainTypes.push_back(newEntry);
        li = li->NextSiblingElement("li");
    }

    //get all the underground terrain blocks too
    XMLElement *undergroundTags = biomeElement->FirstChildElement("undergroundTerrainTypes");
    li = undergroundTags->FirstChildElement("li");
    while (li != nullptr)
    {
        terrainEntry newEntry;
        newEntry.commonality = atof(li->FirstChildElement("commonality")->GetText());
        cout << li->FirstChildElement("terrainDef")->GetText() << endl;
        newEntry.terrainType = getTerrainByDefName(li->FirstChildElement("terrainDef")->GetText());
        undergroundTerrainTypes.push_back(newEntry);
        li = li->NextSiblingElement("li");
    }

    //get all the biome's plant data
    XMLElement *plantTags = biomeElement->FirstChildElement("spawnablePlants");
    /*XMLElement **/li = plantTags->FirstChildElement("li");//reuse the same li variable
    while (li != nullptr)
    {
        plantEntry newPlant;
        newPlant.commonality = atof(li->FirstChildElement("commonality")->GetText());
        //newPlant.plantType = getPlantByDefName(li->FirstChildElement("plant")->GetText());
        newPlant.plant = getPlantTypeByDefName(li->FirstChildElement("plant")->GetText());
        plantTypes.push_back(newPlant);
        li = li->NextSiblingElement("li");
    }

    //looks like color didn't get added to the code. Whateversz
    m_mapColor = color(biomeElement->FirstChildElement("mapColor")->GetText());
}

//outputs whether or not a biome is suitable for a chunk with the specified parameters
bool biome :: isTempAcceptable(float temperature, float variance)
{
    //if average temp is between the biome's min and max temps, then its acceptable
    //if (temperature >= m_tempMin && temperature <= m_tempMax)
    //factor temperature variance into whether a chunk is suitable for the biome or not
    if ((temperature-variance) >= m_tempMin && (temperature+variance) <= m_tempMax)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns a score of how well the biome matches the specified parameters. Unreliable at low return values. Do not use for determining the boolean value of if a biome is suitable for a chunk or not. There is actually already a function for that that works well.
double biome :: biomeMatchScore(float temperature, float variance)
{
    //figure out difference in temperature
    double diff1 = abs(m_tempMin - (temperature-variance));
    double diff2 = abs(m_tempMax - (temperature+variance));
    double result = diff1+diff2;

    //it seems ~40 = a goodish match and ~325 = a shitty match
    if (result < 300)
    {
        //the score needs to drop off exponentially not linearly
        //return 3.0f * (300.0f-result)/300.0f;

        //2 to the power of some number between 0.1 and 1.6
        //make it be able to return negative values too
        return pow(2.0f, (((result/300.0f*1.5)+0.1)*2.0f)-3.0f);
    }
    else
    {
        return 0.0f;
    }
}

/*load everything in Data/Biomes/
note that in this iteration of the engine, there can be more than 1 biome per xml file*/
void loadAllBiomes(SDL_Renderer *ren)
{
    string dataPath = "Data/Biomes";
    vector<string> filePaths;

    //my install of visual studio code doesnt like this but its valid. VSCode is just bullshitting again as usual
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
		    cout << "warning: a biome xml file with no root element got loaded for some stupid reason" << endl;
	    }

        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *biomeToLoad = rootElement->FirstChildElement("Biome");
        while (biomeToLoad != nullptr)
        {
            biome newBiome(biomeToLoad);
            biomeDatabase.push_back(newBiome);
            biomeToLoad = biomeToLoad->NextSiblingElement("Biome");
            //cout << "loading" << endl;
        }
    }
}

biome* getBiomeByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (biomeDatabase.at(i).defName() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &biomeDatabase.at(i);
}