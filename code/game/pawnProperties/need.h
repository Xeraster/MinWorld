#ifndef NEED_H
#define NEED_H

//circular dependencies still can't be overcome though despite my latest breakthroughs in class stuff
//typedef struct pawnState pawnState;

class need
{
    public:
        need();
        need(needType *nType, unsigned int seed);

        //copy constructor
        need(const need& rhs);

        //equals operator
        need operator=(const need& rhs);

        //arbitrarily add a number to the need
        void add(double amt);

        //arbitrarily subtract a number from the need
        void subtract(double amt);

        //anything that inherits this class can do this
        virtual void OnTick();

        //you can set the rate of dropping in case you want to use the base OnTick instead of defining your own
        virtual void setDropRate(double rate);

        double getValue() const { return m_value; }

        double getCurrentDropRate() const { return m_currentDropRate; }

        needType *getNeedType() const { return m_needClass; }

    protected:

    double m_value;     //all the needs get a 0-1 general purpose value

    //how much will this drop per tick if using base need.OnTick(). If using this in a modded child extended class, use it for whatever you want
    double m_currentDropRate;

    needType *m_needClass;//pointer to a virtual class = as c#-like as it gets

    private:
    //void* m_needClass;  //void pointer to specific need class
};

//hmm i wonder if you can load different classes all into the same vector if using virtual functions correctly (you can't unless they're pointers but it actually does work if they're pointers)


#include "need.hpp"
#endif