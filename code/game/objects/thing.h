#ifndef THINGZ_H
#define THINGZ_H//i guess thing is a reserved name or something

//do this because planet class gets loaded after the thing class
//extern planet;

class thing
{
    public:
        thing();
        //overload for spawning a thing from thing type pointer
        thing(thingType *theThing, int x, int y, int z, int seed);

        double getPosX() const { return m_posX; }
        double getPosY() const { return m_posY; }
        int getPosZ() const { return m_posZ; }
        double getRotation() const { return m_rotation; }
        void setRotation(double newRot) 
        { 
            //cout << "setting rotation of " << m_type->defName() << " from " << m_rotation << " to " << newRot << endl;
            m_rotation = newRot;
        }

        int stack() const { return m_stack; }
        int health() const { return m_health; }
        int fire() const { return m_onFire; }
        bool interacted() const { return m_interacted; }

        //modifies the number of things in this stack. returns 0 if success. returns 1 if failed for some reason
        int setStackSize(int newAmt);

        void drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);


    protected:
        thingType *m_type;

        //some things have to conform to whole numbers. Some dont
        double m_posX;
        double m_posY;

        int m_posZ;         //zlevels are only ever ints
        //planet *m_planetItsOn;

        double m_rotation;//a number between 0-360

        //how many "things" are in this "stack" right now
        int m_stack;
        int m_health;   //how many hitpoints this thing has right now
        int m_onFire;   //0 = not on fire. 1 = on fire (small). 2 = on fire (med). 3 = on fire (very)

        bool m_interacted;  //any item that gets touched/moved/interacted with by a player becomes a world thing and not just a chunk thing

        //draws the stack quantity label below any thing. Recommended for use on any child thing that uses stack sizes
        void drawQtyLabel(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);
};

class plant : public thing
{
    public:
        plant();

        //overload for spawning a plant thing based on def name
        plant(string typeDef, int x, int y, int z, int seed);

        //overload for spawning a plant thing from plant type pointer. faster than doing it by def name
        plant(plantType *thePlant, int x, int y, int z, int seed);

        plantType *getThingType() { return m_type; }

        void drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);

    protected:
        double m_growthProgress; //0 = newly planted. 1 = fully grown
        plantType *m_type;
};

class building : public thing
{
    public:
        building();

        //overload for creating a thing of type building from a given buildingType def name
        building(string typeDef, int x, int y, int z, int seed);

        /*maybe this will solve the bullshit "variables not holding value" problem
        i think maybe this is what vector push back looks for*/
        building(const building &rhs);

        //overload for creating a thing of type building from a given buildingType pointer
        building(buildingType *theBuilding, int x, int y, int z, int seed);

        bool madeFromStuff() const { return m_madeFromStuff; }
        buildingType *getType() const { return m_type; }

        //buildings can only be rotated for values of 0, 90, 180, 270
        void setRotation(double newRot) 
        { 
            if (newRot <= 45)
            {
                m_rotation = 0;
            }
            else if (newRot <= 135)
            {
                m_rotation = 90;
            }
            else if (newRot <= 225)
            {
                m_rotation = 180;
            }
            else if (newRot <= 315)
            {
                m_rotation = 270;
            }
            else
            {
                m_rotation = 0;
            }
        }

        void drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);

        //get a list of occupied tiles for this building
        void getOccupiedTiles(vector<positionEntry> *tiles);

        building& operator=(const building& other);

    protected:
        bool m_madeFromStuff;//if made from stuff, it utilizes the mask texture layer. whether the mask layer gets drawn first or last depends on the maskInFront value of the thing type
        buildingType *m_type;

};

//remember how we have to make storage vectors for each child with the item types? we have to do this with every type of thing too
/*i guess each thing gets stored in a different spot
//0 = generic. 1 = plant. 2 = building. 3 = weapon. 4 = clothing or armor. 5 = other equippable. 6 = food. 7 = drug. 8 = reserved. 9 = corpse. 10 = pawn

*/

//this is where all the created things go
vector<thing*> worldThings;

//however the data each child thing needs to be stored in its own vector which means there has to be a vector for each category.. yeah
vector<plant> worldPlants;

#include "thing.hpp"
#endif