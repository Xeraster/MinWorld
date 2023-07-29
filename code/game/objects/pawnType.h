#ifndef PAWNTYPE_H
#define PAWNTYPE_H

/*
the pawn type class. any living thing (except for plants, I guess). living things you see moving around on the screen are of the pawn class. 
each pawn class has a pointer a pawnType object and that pawnType sets the rules and features and stuff
*/
class pawnType
{
public:
    pawnType();
    pawnType(XMLElement *thingElement, SDL_Renderer *ren);

    //yay I love doing this part by hand /s
    //generally none of this is supposed to be changed at runtime but mod support is important so there will also be setters eventually
    string defname() const { return m_defname; }//returns the defname of this pawnType
    string label() const { return m_label; }    //returns the ingame display label/string of this pawnType
    string description() const { return m_description; }    //returns the description of the thing

    double minTemp() const { return m_minTemp; }//minimum suvivable temperature
    double maxTemp() const { return m_maxTemp; }//maximum survivable temperature
    double minComfortableTemp() const { return m_minComfortableTemp; }
    double maxComfortableTemp() const { return m_maxComfortableTemp; }

    double fertility() const { return m_fertility; }//how much babymaking does this pawn type do/how effective is this pawn type at babymaking

    double nutritionPerDay() const { return m_nutritionPerDay; }    //how much does this pawn type eat per day.
    double moveSpeed() const { return m_moveSpeed; }    //base movement speed in meters per second (1 tile is 1 cubic meter)
    double dirtiness() const { return m_dirtiness; }    //how much filth the pawn type generates when they move around
    double growthRate() const { return m_growthRate; }  //how quickly does an immature one of these grow to become mature
    double carryCapacity() const { return m_carryCapacity; }    //how many kg of things can this base pawn type carry
    double lifespan() const { return m_lifespan; }              //in Earth years (365*86400 Earth seconds)

    bool nocturnal() const { return m_nocturnal; }              //does this thing natrually prefer to sleep at night or during the day
    double marketValue() const { return m_marketValue; }        //how much is this lifeform worth?
    double hitPoints() const { return m_hitPoints; }            //0 or less means it uses the health system. any number greater than zero uses a simple hitpoint system (for making a horsefly or something that is small/numerous)
    double flammability() const { return m_flammability; }      //how easily does this thing burn? 0.5 or higher is a self sustaining flame

    double armorSharp() const { return m_armorSharp; }
    double armorHeat() const { return m_armorHeat; }
    double armorBlunt() const { return m_armorBlunt; }
    double armorStrink() const { return m_armorStink; }         //smells can be weaponized
    double stinkTolerance() const { return m_stinkTolerance; }  //0 means they hate bad smells (eg: humans). 0.5 means indifferent (eg: dogs, chickens). 1 means they love bad smells (eg: horseflies, sharks, some dogs)

    int harvestLeather() const { return m_harvestLeather; }
    int harvestFur() const { return m_harvestFur; }
    int harvestMeat() const { return m_harvestMeat; }
    int harvestBone() const { return m_harvestBone; }

    color furColor() const { return m_furColor; }
    color skinColor() const { return m_skinColor; }
    color meatColor() const { return m_meatColor; }
    color boneColor() const { return m_boneColor; }

    int techLevel() const { return m_techLevel; }

    //texture getters
    bool maskInFront() const { return m_maskInFront; }
    //fuck there's 8 different textures
    SDL_Texture *getTextureByRotation(double rot);
    SDL_Texture *getMaskByRotation(double rot);

    //true if the pawn has a valid list of needs. false if otherwise
    bool hasNeeds() const;

    //number of loaded needs into this pawnType
    int numNeeds() const { return m_pawnNeeds.size(); }

    needType *getNeedAt(unsigned int index) const { return m_pawnNeeds.at(index); }

    //if there are any nullptr textures, print them to the console. that's all this does and probably isn't whatever it is you're looking for
    void printNullTextures();
protected:
    string m_defname;
    string m_label;
    string m_description;

    double m_minTemp;
    double m_maxTemp;
    double m_minComfortableTemp;
    double m_maxComfortableTemp;
    double m_fertility;//reproductive

    //store a list of needs for this pawn. Generally supposed to be read-only from outside classes
    vector<needType*> m_pawnNeeds;
    //bool m_hasNeeds;

    double m_nutritionPerDay;//how much does this pawn type eat per day.
    double m_moveSpeed;//base movement speed in meters per second (1 tile is 1 cubic meter)
    double m_dirtiness;//how much filth the pawn type generates when they move around
    double m_growthRate;//how quickly does an immature one of these grow to become mature
    double m_carryCapacity;//how many kg of things can this base pawn type carry
    double m_lifespan;//in Earth years (365*86400 Earth seconds)
    //dietDef *m_dietDef;//diet restriction.
    bool m_nocturnal;//does this thing natrually prefer to sleep at night or during the day
    double m_marketValue;//how much is this lifeform worth?
    double m_hitPoints;//0 or less means it uses the health system. any number greater than zero uses a simple hitpoint system (for making a horsefly or something that is small/numerous)
    double m_flammability;//how easily does this thing burn? 0.5 or higher is a self sustaining flame

    //the armor system is similar to rimworld.
    double m_armorSharp;
    double m_armorBlunt;
    double m_armorHeat;
    double m_armorStink;//smells can be weaponized
    double m_stinkTolerance;//0 means they hate bad smells (eg: humans). 0.5 means indifferent (eg: dogs, chickens). 1 means they love bad smells (eg: horseflies, sharks, some dogs)

    /*harvest products
    if the harvest product variable has a nonzero value, autogenerate it
    */
    int m_harvestLeather;
    int m_harvestFur;
    int m_harvestMeat;
    int m_harvestBone;

    //the mask colors for the autogenerated harvest products
    color m_furColor;
    color m_skinColor;
    color m_meatColor;
    color m_boneColor;

    //vector<thingType> m_harvestProducts;//the non auto generated harvest products

    int m_techLevel;//<!-- 0 = feral/animal. 1 = neolithic. 2 = med. 3 = industrial. 4 = nuclear. 5 = space. 6 = ultratech. 7 = god tier. 8 = dev only -->. probably unneccesary but im leaving it in because stonks

    SDL_Texture *m_frontTex;
    SDL_Texture *m_backTex;
    SDL_Texture *m_sideATex;    //sideA = face left. if there is no sideB texture, a flipped sideA texture is used
    SDL_Texture *m_sideBTex;

    SDL_Texture *m_frontMaskTex;    //mask probably isn't the right word, but typically you make the "mask" be the color white. It will then get colored to whatever the skin color is
    SDL_Texture *m_backMaskTex;
    SDL_Texture *m_sideAMaskTex;
    SDL_Texture *m_sideBMaskTex;
    bool m_maskInFront;

    /*there are 3 supported texture configurations:
        1. using just the front. In this configuration, you only supply the front (and mask, if desired). The game engine will rotate that 1 sprite for you
        2. supplying a front, back and sideA texture. The game engine will use sideA for both left and right facing and flip it automatically. Make sure sideA faces left. mask textures are supported and optional
        3. supplying a front, back, sideA and sideB texture. sideA is the left facing one. sideB is the back facing one. mask textures are supported and optional
    */
    int m_textureConfiguration;
private:
};

vector<pawnType> pawnTypeDatabase;

//load everything in Data/PawnTypes/*
void loadAllPawnTypes(SDL_Renderer *ren);

pawnType *getPawnTypeByDefName(string name);

#include "pawnType.hpp"
#endif  