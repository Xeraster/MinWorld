#ifndef THING_H
#define THING_H

class thingType
{
    public:
        thingType();
        thingType(XMLElement *thingElement, SDL_Renderer *ren);

        string defName() const { return m_defName; }
        string label() const { return m_label; }
        string description() const { return m_description; }
        float marketValue() const { return m_marketValue; }
        int hitPoints() const { return m_marketValue; }
        float flammability() const { return m_flammability; }
        float techLevel() const { return m_techLevel; }
        bool isMadeFromStuff() const { return m_madeFromStuff; }
        bool canRotate() const { return m_canRotate; }
        bool maskInFront() const { return m_maskInFront; }
        int maxStackSize() const { return m_maxStackSize; }
        
        //if the thing type has a color, return it.
        color getStuffColor() const { return m_stuffColor; }

        //does the sprite use the 1-2-3 texture stacking convention or the default convention?
        bool usesTexStack() const { return m_textureStack; }

        SDL_Texture *getThingTex() const { return tex; }
        SDL_Texture *getMaskTex() const { return m_maskTexture; }

        SDL_Texture *getThingTexB() const { return texB; }
        SDL_Texture *getMaskTexB() const { return m_maskTextureB; }

        SDL_Texture *getThingTexC() const { return texC; }
        SDL_Texture *getMaskTexC() const { return m_maskTextureC; }

    protected:
        //needed in c++ for housekeeping reasons. Rimworld doesn't have to deal with issues like this because it runs on c#
        //1 integer for each child
        int m_type; //0 = invalid. 1 = plant. 2 = building. 3 = weapon. 4 = clothing or armor. 5 = other equippable. 6 = food. 7 = drug. 8 = general purpose thing or intermediate product. (i.e. anything that doesn't do anything on its own). 9 = corpse.

        string m_defName;
        string m_label;
        string m_description;
        SDL_Texture *tex;
        SDL_Texture *m_maskTexture;     //if thing is made from stuff, you can mask parts of the texture to show up as the color of that stuff

        //only used if thing type needs the 1-2-3 stacking convention. 
        //generally only the base thingType as well as foodType and drugType can have 1-2-3 stacking
        SDL_Texture *texB;
        SDL_Texture *m_maskTextureB;
        SDL_Texture *texC;
        SDL_Texture *m_maskTextureC;

        color m_stuffColor;

        int m_maxStackSize;
        double m_unitWeight;//how much does 1 of these weigh?

        float m_marketValue;//how much is the item worth

        int m_hitPoints;

        float m_flammability;

        bool m_madeFromStuff;

        bool m_maskInFront;

        int m_techLevel;//0 = feral/animal. 1 = neolithic. 2 = med. 3 = industrial. 4 = nuclear. 5 = spacer. 6 = ultratech. 7 = god tier. 8 = dev only

        //whether or not the sprite can be rotated. Note that only buildings, weapons, apparel, pawns and corpses are intended to have rotation
        bool m_canRotate;
    private:
        bool m_textureStack;    //whether or not to use the 1-2-3 texture stacking convention or just do 1 texture
};

class plantType: public thingType
{
    public:
        plantType();
        plantType(XMLElement *plantElement, SDL_Renderer *ren);

        //get the mature fully grow plant texture
        SDL_Texture *getTex() { return mature_tex; }

        //get the non-mature non fruit bearing plant texture if present
        SDL_Texture *getGrowTex() { return grow_tex; }

        bool is_plantable() const { return m_plantable; }
        bool requires_research() const { return m_requiresResearch; }

        float minTemp() const { return m_minTemp; }
        float maxTemp() const { return m_maxTemp; }
        float nutrition() const { return m_nutrition; }
        float needsLight() const { return m_needsLight; }
        float daysToGrow() const { return m_daysToGrow; }
        int harvestSkill() const { return m_harvestSkill; }
        float minFertility() const { return m_minFertility; }

    private:
        SDL_Texture *mature_tex;
        SDL_Texture *grow_tex;
        bool m_plantable;
        bool m_requiresResearch;
        float m_minTemp;
        float m_maxTemp;
        float m_nutrition;
        float m_needsLight;
        float m_daysToGrow;
        int m_harvestSkill;
        float m_minFertility;
        // harvest products
        // vector<harvestProduct> m_product;
};

struct buildRecipeEntry
{
        bool isCategory;    //this means any range of things in category can be used to build it
        string defName; //can be the category def or the thing def
        int amount;     //number of things
};

class buildingType : public thingType
{
    public:
        buildingType();
        buildingType(XMLElement *plantElement, SDL_Renderer *ren);

        int footprintX() const { return m_footprintX; }
        int footprintY() const { return m_footprintY; }
        bool maskInFront() const { return m_maskInFront; }

        SDL_Texture *getTex() const { return m_onTexture; }
        SDL_Texture *getTex_off() const { return m_offTexture; }

    private:
        SDL_Texture *m_onTexture;
        SDL_Texture *m_offTexture;

        //I have no idea how this will work yet but I will make it as dynamic as possible come hell or high water. no hack is too ugly to try
        string m_subclassString;

        //m_researchToBuild//dont have research yet
        int m_constructSkill;
        int m_workToBuild;
        bool m_minifiable;
        double m_funFactor;
        int m_passability;      //0: impassible. 1: impassible but not airtight. 2: slows movement. 3: passable

        int m_footprintX;
        int m_footprintY;
        
        //build recipe. What ingredients/things does it take to build one of these and how much?
        vector<buildRecipeEntry> m_buildRecipe;
};

class weaponType : public thingType
{
    public:
    private:
};

class clothingType : public thingType
{
    public:
    private:
};

class equippableType : public thingType
{
    public:
    private:
};

class foodType : public thingType
{
    public:
    private:
};

class drugType : public thingType
{
    public:
    private:
};

class intermediateThingType : public thingType
{
    public:
    private:
};

//load everything in Data/*
void loadAllThingTypes(SDL_Renderer *ren);

//load everything in Data/ThingTypes/*
void loadAllGenericTypes(SDL_Renderer *ren);

//load everything in Data/PlantTypes/*
void loadAllPlantTypes(SDL_Renderer *ren);

//load everything in Data/BuildingTypes/*
void loadAllBuildingTypes(SDL_Renderer *ren);

vector<thingType*> thingTypeDatabase;

//each thing has to be stored in a storage vector but a pointer to each object can be put in thingTypeDatabase
vector<thingType> genericThingTypeDatabase;     //we have to store instances of the generic type somewhere since they are actual real valid things
vector<plantType> plantTypeDatabase;        // plant types
vector<buildingType> buildingTypeDatabase;  //building types

//this will only work for thingTypes that are actually of the thingType class and not a child of class
thingType *GetThingTypeByDefName(string name);
plantType *getPlantTypeByDefName(string name);
buildingType *getBuildingTypeByDefName(string name);

#include "thingType.hpp"
#endif