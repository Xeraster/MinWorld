needType :: needType()
{

}

needType :: needType(XMLElement *xmlElement, SDL_Renderer *ren)
{
    m_defName = xmlElement->FirstChildElement("defname")->GetText();
    cout << "loading " << m_defName << endl;
    m_label = xmlElement->FirstChildElement("label")->GetText();
    m_description = xmlElement->FirstChildElement("description")->GetText();

    m_requiresIntelligence = stoi(xmlElement->FirstChildElement("requiresIntelligence")->GetText());
    m_important = stringToBool(xmlElement->FirstChildElement("important")->GetText());
    m_showOnList = stringToBool(xmlElement->FirstChildElement("showOnList")->GetText());
    m_relevantIfOutOfPlay = stringToBool(xmlElement->FirstChildElement("showOnList")->GetText());
    m_listPriority = stoi(xmlElement->FirstChildElement("listPriority")->GetText());
    m_freezeWhileSleeping = stringToBool(xmlElement->FirstChildElement("freezeWhileSleeping")->GetText());
    m_freezeWhileInMentalState = stringToBool(xmlElement->FirstChildElement("freezeInMentalState")->GetText());

    m_minAge = stof(xmlElement->FirstChildElement("minAge")->GetText());
    m_maxAge = stof(xmlElement->FirstChildElement("maxAge")->GetText());

    m_barColor = color(xmlElement->FirstChildElement("barColor")->GetText());

    ///the only unimplemented vars as of 07/27/23 are moodElement, and whatever that class + tickMethod bs is
}

//the July 27 anomoly
//load everything in Data/NeedTypes/*
void loadAllNeedTypes(SDL_Renderer *ren)
{
    string dataPath = "Data/NeedTypes";
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
        XMLError error = doc.LoadFile(filePaths.at(i).c_str());
        cout << "loaded file " << filePaths.at(i) << " into ram" << endl;

        if (doc.RootElement() == nullptr)
	    {
		    cout << "warning: a need type xml file with no root element got loaded for some reason" << endl;
            cout << "error = " << error << endl;
	    }



        //contents of all def xml files are supposed to be surrounded by def tags
        XMLElement *rootElement = doc.RootElement();
        XMLElement *thingToLoad = rootElement->FirstChildElement("NeedType");
        //XMLElement *thingToLoad = doc.FirstChildElement("NeedType");
        while (thingToLoad != nullptr)
        {
            needType newNeed(thingToLoad, ren);
            needTypeDatabase.push_back(newNeed);

            //push the thing into the pointer database
            //thingTypeDatabase.push_back(dynamic_cast<thingType *>(&newThing));
            // plantTypeDatabase.push_back(new plantType);
            // static_cast<plantType*>(thingTypeDatabase->back()) = newPlant;

            thingToLoad = thingToLoad->NextSiblingElement("NeedType");
            //cout << "loading" << endl;
        }
    }
}

needType *GetNeedTypeByDefName(string name)
{
    bool foundMatch = false;
    int i = 0;
	while (!foundMatch)
	{
        if (needTypeDatabase.at(i).defname() == name)
        {
			foundMatch = true;
		}
		else
		{
			i++;
		}
	}

	return &needTypeDatabase.at(i);
}