#ifndef NEEDTYPE_H
#define NEEDTYPE_H

class needType
{
    public:

    needType();
    needType(XMLElement *xmlElement, SDL_Renderer *ren);

    string defname() const { return m_defName; }
    string label() const { return m_label; }
    string description() const { return m_description; }
    string className() const { return m_className; }
    string methodName() const { return m_methodName; }

    //what's the minimum pawn techLevel that this need will show up for
    int requiredIntelligence() const { return m_requiresIntelligence; }

    //whether this need is required for survival or not
    bool isImportant() const { return m_important; }

    //should this need show up on ui menus or not
    bool showOnList() const { return m_showOnList; }

    //if the pawn is out of play, should this get processed during game tick or ignore it?
    bool relevantIfOutOfPlay() const { return m_relevantIfOutOfPlay; }

    //ui list order. lower numbers towards top
    int listPriority() const { return m_listPriority; }

    //whether ontick gets disabled when the pawn is sleeping or not
    bool freezeWhileSleeping() const { return m_freezeWhileSleeping; }

    //whether ontick gets disable when the pawn is in a mental state or not
    bool freezeWhileInMentalState() const { return m_freezeWhileInMentalState; }

    //minimum pawn growth value for this need to be active
    int minAge() const { return m_minAge; }

    //maximum pawn growth value for this need to be active
    int maxAge() const { return m_maxAge; }

    //color of ui bar
    color barColor() const { return m_barColor; }

    protected:
    string m_defName;
    string m_label;
    string m_description;

    string m_className;
    string m_methodName;

    //what's the minimum pawn techLevel that this need will show up for
    int m_requiresIntelligence;

    //moodElement m_relevantMood;
    
    bool m_important;   //whether this need is required for survival or not
    bool m_showOnList;  //should this need show up on ui menus or not
    bool m_relevantIfOutOfPlay; //if the pawn is out of play, should this get processed during game tick or ignore it?
    int m_listPriority; //ui list order. higher numbers towards top
    bool m_freezeWhileSleeping;//whether ontick gets disabled when the pawn is sleeping or not
    bool m_freezeWhileInMentalState;//whether ontick gets disable when the pawn is in a mental state or not

    int m_minAge;   //minimum pawn growth value for this need to be active
    int m_maxAge;   //maximum pawn growth value for this need to be active
    color m_barColor;   //color of ui bar
};

//the July 27 anomoly
//load everything in Data/NeedTypes/*
void loadAllNeedTypes(SDL_Renderer *ren);
//why the fuck is this not working...? its exactly the same as all the other ones that DO work

vector<needType> needTypeDatabase;

needType *GetNeedTypeByDefName(string name);

#include "needType.hpp"

#endif