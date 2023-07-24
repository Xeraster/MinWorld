thingType :: thingType()
{
    
}

thingType :: thingType(XMLElement *thingElement, SDL_Renderer *ren)
{
    m_defName = thingElement->FirstChildElement("defName")->GetText();
    m_label = thingElement->FirstChildElement("label")->GetText();
    m_description = thingElement->FirstChildElement("description")->GetText();
    //m_mapColor = biomeElement->FirstChildElement("description")->GetText();
    //m_survivabilty = atof(plantElement->FirstChildElement("survivability")->GetText());
    //m_commonality = atof(plantElement->FirstChildElement("commonality")->GetText());

    m_marketValue = atof(thingElement->FirstChildElement("marketValue")->GetText());
    m_hitPoints = atoi(thingElement->FirstChildElement("hitPoints")->GetText());
    m_flammability = atof(thingElement->FirstChildElement("flammability")->GetText());
    m_maxStackSize = atoi(thingElement->FirstChildElement("stackSize")->GetText());
    m_canRotate = stringToBool(thingElement->FirstChildElement("canRotate")->GetText());
    //m_canRotate = stringToBool(thingElement->FirstChildElement("canRotate")->GetText());
    m_techLevel = atoi(thingElement->FirstChildElement("techLevel")->GetText());

    m_maskInFront = stringToBool(thingElement->FirstChildElement("maskInFront")->GetText());

    //figure out the fuckery that is the texturing system
    m_textureStack = stringToBool(thingElement->FirstChildElement("textureStack")->GetText());

    m_stuffColor = color(thingElement->FirstChildElement("stuffColor")->GetText());

    /*if texture stack bool is true, load texture information from element called texture_folder but also 
    load texture prefix from texture_prefix. Look, I know it's complicated but I thought about this for like a week straight
    and this is the most overall robust solution I could come up with
    */
    if (m_textureStack)
    {
        //get the relevant texture path information
        string textureFolder = thingElement->FirstChildElement("texture_folder")->GetText();
        string texturePrefix = thingElement->FirstChildElement("texture_prefix")->GetText();

        /*
        now that we have the folder all the textures are in, load them like so for 1-2-3 mode:
            
            //1:
            tex = [texturePrefix]_A.png
            m_maskTexture = [texturePrefix]_A_mask.png

            //2
            texB = [texturePrefix]_B.ong
            m_maskTextureB = [texturePrefix]_B_mask.png

            //3
            texC = [texturePrefix]_C.png
            m_maskTextureC = [texturePrefix]_C_mask.png
        */

       tex = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_A.png", ren);
       m_maskTexture = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_A_mask.png", ren);

       texB = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_B.png", ren);
       m_maskTextureB = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_B_mask.png", ren);

       texC = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_C.png", ren);
       m_maskTextureC = loadTextureToRam("Textures/" + textureFolder + "/" + texturePrefix + "_C_mask.png", ren);
       cout << "loaded texture folder: " << "Textures/" + textureFolder + "/" + texturePrefix << endl;
    }
    //if texture stack is false, load textures just like any other item by looking for a texture tag and then a texture_mask tag
    else
    {
        //get the relevant texture path information
        string maskTex = thingElement->FirstChildElement("texture_mask")->GetText();
        string colorTex = thingElement->FirstChildElement("texture")->GetText();

        //load the 2 textures into the texture pointers and go about your day. If a texture is missing it won't even crash
        tex = loadTextureToRam("Textures/" + colorTex, ren);
        m_maskTexture = loadTextureToRam("Textures/" + maskTex, ren);
    }
}

thingType *GetThingTypeByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (genericThingTypeDatabase.at(i).defName() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &genericThingTypeDatabase.at(i);
}

//load everything in Data/ThingTypes/*
void loadAllGenericTypes(SDL_Renderer *ren)
{
    string dataPath = "Data/ThingTypes";
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
		    cout << "warning: a thing type xml file with no root element got loaded for some reason" << endl;
	    }


        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *thingToLoad = rootElement->FirstChildElement("ThingType");
        while (thingToLoad != nullptr)
        {
            thingType newThing(thingToLoad, ren);
            genericThingTypeDatabase.push_back(newThing);

            //push the thing into the pointer database
            thingTypeDatabase.push_back(dynamic_cast<thingType *>(&newThing));
            // plantTypeDatabase.push_back(new plantType);
            // static_cast<plantType*>(thingTypeDatabase->back()) = newPlant;

            thingToLoad = thingToLoad->NextSiblingElement("ThingType");
            //cout << "loading" << endl;
        }
    }
}


//===================================================================
//plant related stuff
//===================================================================
plantType :: plantType()
{

}

plantType :: plantType(XMLElement *plantElement, SDL_Renderer *ren)
{
    //the base class values and stuff
    m_defName = plantElement->FirstChildElement("defName")->GetText();
    m_label = plantElement->FirstChildElement("label")->GetText();
    m_description = plantElement->FirstChildElement("description")->GetText();
    //m_mapColor = biomeElement->FirstChildElement("description")->GetText();
    //m_survivabilty = atof(plantElement->FirstChildElement("survivability")->GetText());
    //m_commonality = atof(plantElement->FirstChildElement("commonality")->GetText());

    m_canRotate = false;//plants can't be rotated

    m_marketValue = atof(plantElement->FirstChildElement("marketValue")->GetText());
    m_hitPoints = atoi(plantElement->FirstChildElement("hitPoints")->GetText());
    m_flammability = atof(plantElement->FirstChildElement("flammability")->GetText());
    m_maxStackSize = atoi(plantElement->FirstChildElement("stackSize")->GetText());
    m_techLevel = atoi(plantElement->FirstChildElement("techLevel")->GetText());

    //the only color plants can be is green
    m_stuffColor = color(0, 255, 0);

    //the plant specific values
    string researchString = plantElement->FirstChildElement("resarchToPlant")->GetText();
    if (researchString == "None")
    {
        m_requiresResearch = false;
    }
    else
    {
        m_requiresResearch = true;
    }

    if (researchString == "Never")
    {
        m_plantable = false;
    }
    else
    {
        m_plantable = true;
    }
    m_minTemp = atoi(plantElement->FirstChildElement("minTemp")->GetText());
    m_maxTemp = atoi(plantElement->FirstChildElement("maxTemp")->GetText());
    m_nutrition = atof(plantElement->FirstChildElement("nutrition")->GetText());
    m_needsLight = atof(plantElement->FirstChildElement("needsLight")->GetText());
    m_daysToGrow = atof(plantElement->FirstChildElement("daysToGrow")->GetText());
    m_harvestSkill = atoi(plantElement->FirstChildElement("harvestSkill")->GetText());
    m_minFertility = atof(plantElement->FirstChildElement("minFertility")->GetText());
    //cout << m_defName << " m_minFertility=" << m_minFertility << endl;

    //harvest products
    string growingTex = plantElement->FirstChildElement("texture")->GetText();
    string matureTex = plantElement->FirstChildElement("texture_mature")->GetText();

    grow_tex = loadTextureToRam("Textures/"+growingTex, ren);

    //don't load 2 copies of same texture if not required
    if (growingTex == matureTex)
    {
        mature_tex = grow_tex;
    }
    //if mature texture is different from grow texture, load it
    else
    {
        cout << m_defName << "has a seperate matrue texture " << endl;
        mature_tex = loadTextureToRam("Textures/" + matureTex, ren);
    }
}

//load everything in Data/*
void loadAllThingTypes(SDL_Renderer *ren)
{
    //load each type of different thing
    loadAllGenericTypes(ren);
    loadAllPlantTypes(ren);
    loadAllBuildingTypes(ren);
}

//load everything in Data/Plants/*
void loadAllPlantTypes(SDL_Renderer *ren)
{
    string dataPath = "Data/PlantTypes";
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
        cout << "got here 2" << endl;

        if (doc.RootElement() == nullptr)
	    {
		    cout << "warning: a plant xml file with no root element got loaded for some stupid reason" << endl;
	    }


        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *plantToLoad = rootElement->FirstChildElement("PlantType");
        while (plantToLoad != nullptr)
        {
            plantType newPlant(plantToLoad, ren);
            plantTypeDatabase.push_back(newPlant);

            //push the thing into the pointer database
            thingTypeDatabase.push_back(dynamic_cast<thingType *>(&newPlant));
            // plantTypeDatabase.push_back(new plantType);
            // static_cast<plantType*>(thingTypeDatabase->back()) = newPlant;

            plantToLoad = plantToLoad->NextSiblingElement("PlantType");
            //cout << "loading" << endl;
        }
    }
}

plantType *getPlantTypeByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (plantTypeDatabase.at(i).defName() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &plantTypeDatabase.at(i);
}

//=======================================================================
//building related stuff
//=======================================================================
buildingType :: buildingType()
{

}
buildingType :: buildingType(XMLElement *plantElement, SDL_Renderer *ren)
{
    //the base class values and stuff
    m_defName = plantElement->FirstChildElement("defName")->GetText();
    m_label = plantElement->FirstChildElement("label")->GetText();
    m_description = plantElement->FirstChildElement("description")->GetText();
    //m_mapColor = biomeElement->FirstChildElement("description")->GetText();
    //m_survivabilty = atof(plantElement->FirstChildElement("survivability")->GetText());
    //m_commonality = atof(plantElement->FirstChildElement("commonality")->GetText());

    m_marketValue = atof(plantElement->FirstChildElement("marketValue")->GetText());
    m_hitPoints = atoi(plantElement->FirstChildElement("hitPoints")->GetText());
    m_flammability = atof(plantElement->FirstChildElement("flammability")->GetText());
    m_maxStackSize = atoi(plantElement->FirstChildElement("stackSize")->GetText());
    m_techLevel = atoi(plantElement->FirstChildElement("techLevel")->GetText());
    m_unitWeight = atof(plantElement->FirstChildElement("weight")->GetText());
    m_canRotate = stringToBool(plantElement->FirstChildElement("canRotate")->GetText());

    m_subclassString = plantElement->FirstChildElement("buildingSubclass")->GetText();
    m_constructSkill = atoi(plantElement->FirstChildElement("constructSkill")->GetText());
    m_workToBuild = atoi(plantElement->FirstChildElement("workToBuild")->GetText());
    m_minifiable = stringToBool(plantElement->FirstChildElement("minifiable")->GetText());
    m_funFactor = atof(plantElement->FirstChildElement("workToBuild")->GetText());
    m_passability = atoi(plantElement->FirstChildElement("passability")->GetText());

    //load the footprint size data
    m_footprintX = atoi(plantElement->FirstChildElement("footprintx")->GetText());
    m_footprintY = atoi(plantElement->FirstChildElement("footprinty")->GetText());
    m_maskInFront = stringToBool(plantElement->FirstChildElement("maskInFront")->GetText());

    string buildingTex = plantElement->FirstChildElement("texture")->GetText();
    string offTex = plantElement->FirstChildElement("texture_off")->GetText();
    string maskTex = plantElement->FirstChildElement("texture_mask")->GetText();
    cout << "loaded buildingType " << m_defName << endl;

    m_onTexture = loadTextureToRam("Textures/" + buildingTex, ren);
    m_offTexture = loadTextureToRam("Textures/" + offTex, ren);
    m_maskTexture = loadTextureToRam("Textures/" + maskTex, ren);

    //get build recipe stuff
    XMLElement *buildRecipe = plantElement->FirstChildElement("buildRecipe");
    XMLElement *li = buildRecipe->FirstChildElement("li");
    m_madeFromStuff = false;    //if a thing category is encountered in the build recipe, madeFromStuff gets set to true
    while (li != nullptr)
    {
        buildRecipeEntry newEntry;
        //newEntry.commonality = atof(li->FirstChildElement("commonality")->GetText());
        //cout << li->FirstChildElement("terrainDef")->GetText() << endl;
        //newEntry.terrainType = getTerrainByDefName(li->FirstChildElement("terrainDef")->GetText());

        //figure out if its a category or not
        if (li->FirstChildElement("thing") != nullptr)
        {
            //if a tag called thing exists, the recipe takes a thing and not a thing category
            newEntry.defName = li->FirstChildElement("thing")->GetText();
            newEntry.isCategory = false;
        }
        else
        {
            //if a tag called thingCategory exists, the recipe takes a thing category and not just a thing
            newEntry.defName = li->FirstChildElement("thingCategory")->GetText();
            newEntry.isCategory = true;
            m_madeFromStuff = true; // if a thingCategory tag exits, the building is made from stuff
        }

        //get the amount of either thing or category
        newEntry.amount = atoi(li->FirstChildElement("amount")->GetText());
        cout << "build recipe with def of " << newEntry.defName << " and qty of" << newEntry.amount << endl;
        m_buildRecipe.push_back(newEntry);
        li = li->NextSiblingElement("li");
    }


}

//load everything in Data/BuildingTypes/*
void loadAllBuildingTypes(SDL_Renderer *ren)
{
    string dataPath = "Data/BuildingTypes";
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
		    cout << "warning: a building type xml file with no root element got loaded for some reason" << endl;
	    }


        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *buildingToLoad = rootElement->FirstChildElement("BuildingType");
        while (buildingToLoad != nullptr)
        {
            buildingType newBuilding(buildingToLoad, ren);
            buildingTypeDatabase.push_back(newBuilding);

            //push the thing into the pointer database
            thingTypeDatabase.push_back(dynamic_cast<thingType *>(&newBuilding));
            // plantTypeDatabase.push_back(new plantType);
            // static_cast<plantType*>(thingTypeDatabase->back()) = newPlant;

            buildingToLoad = buildingToLoad->NextSiblingElement("BuildingType");
            //cout << "loading" << endl;
        }
    }
}


buildingType *getBuildingTypeByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (buildingTypeDatabase.at(i).defName() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &buildingTypeDatabase.at(i);
}