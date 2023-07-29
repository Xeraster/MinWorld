#ifndef PAWNDRIVER_H
#define PAWNDRIVER_h

struct pawnDriverStats
{
    int test = 42;
};


class pawnDriver
{
public:
    pawnDriver();

    //copy constructor
    pawnDriver(const pawnDriver& rhs);

    //equals operator
    pawnDriver operator=(const pawnDriver& rhs);
protected:
    pawnControls OnTick(pawnDriverStats &stats, pawnState parentState, unsigned int seed = 69420);

private:
};

#include "pawnDriver.hpp"

#endif