#ifndef PAWN_H
#define PAWN_H

//fuck it, pawns extend the thing class because why not
class pawn : public thing
{
public:
    pawn();
    //overload for spawning a thing from thing type pointer
    pawn(pawnType *thePawn, int x, int y, int z, int seed);

    //copy constructor
    pawn(const pawn& rhs);

    //equals operator
    pawn operator=(const pawn& rhs);

    //call this to draw the pawn to the screen. Since I'll almost certainly have to do some arcane c++ sorcery to make this work as modularly as in similar c# based games, it's very important that the function names and overloads match that of the thing class
    void drawThing(SDL_Renderer *ren, SDL_Window *win, int playerCameraX, int playerCameraY, int playerCameraZ, double zoomLevel);

    //this gets run once per tick.
    void tickThing(unsigned int seed = 69420);

    bool isAlive() const { return m_state.m_isAlive; }

    //get the pawn type objet pointer
    pawnType *getPawnType() const { return m_type; }

    //get the pawn state
    pawnState getPawnState() const { return m_state; }

    //get the pawn controls object
    pawnControls getPawnControls() const { return m_controls; }

    int numPawnNeeds() const { return m_needs.size(); }

    //non-const need getter for modding and advanced functionality purposes. Don't use this if you don't have to
    need getNeedAt_noconst(int index) { return m_needs.at(index); }

    //constant need getter for copy constructor and compatibility purposes
    need getNeedAt(int index) const { return m_needs.at(index); }

    //get pawn's life stage from 0.0f to 1.0f
    double getGrowthProgress() const { return m_growthProgress; }

    //remember that pawn inherits several useful functions and variables from thing but im not going to paste them all here

    //functionality stuff

    //eat food
    //bool eat(food item);
protected:
    pawnType *m_type;//pointer to the type of pawn it is

    pawnState m_state;

    //controls used by the pawnDriver
    pawnControls m_controls;

    //the object that autonomously controls the pawn
    pawnDriver m_pawnDriver;

    //inherited variables from base thing class (for readability):
    /*double m_posX;
    double m_posY;

    int m_posZ;         //zlevels are only ever ints
    //planet *m_planetItsOn;

    double m_rotation;//a number between 0-360

    //how many "things" are in this "stack" right now
    int m_stack;
    int m_health;   //how many hitpoints this thing has right now. 0 or -1 to disable hitpoint system and instead use medical system
    int m_onFire;   //0 = not on fire. 1 = on fire (small). 2 = on fire (med). 3 = on fire (very)

    bool m_interacted;  //any item that gets touched/moved/interacted with by a player becomes a world thing and not just a chunk thing
    */

   //the pawn's needs all stored in a vector
   vector<need> m_needs;

   double m_growthProgress; //0 = newly born. 1 = mature adult

   vector<thing> m_inventory;//all the things in this pawn's standard inventory

   /*
   apparelSlot m_underwear_groin;
   apparelSlot m_underwear_chest;
   
   apparelSlot m_head;
   apparelSlot m_torso_under;
   apparelSlot m_torso_outer;
   apparelSlot m_torso_bottom;
   apparelSlot m_feet;
   apparelSlot m_backpack;  //i don't care about the loss in realism this causes, make it possible to use backpacks because caravanning in Rimworld is grindy and slow and stupid

   apparelSlot m_fullBody;
   //unlike in Rimworld, non of the clothing slots are exclusive. You can have all the slots fully used at all times and there will be no xml def settings to override this. 
   //Wanna go commando while wearing a space suit? Sure, why not. Wanna wear a flight suit but also a bulletproof kevlar vest? Absolutely.
   */


private:
    //clears whatever is in m_needs and reapplys them from pawnTYpe
    void populateNeeds();

    //run this on tick to decrement needs at the correct rate
    void tickNeeds();
};

#include "pawn.hpp"
#endif