#ifndef LOCATION 
#define LOCATION
#include <vector>
#include "story.hpp"

struct location
{
    unsigned short id;
    unsigned short type;
    unsigned short date_b;
    short date_e;
    std::vector <unsigned short> name;
    std::vector <unsigned short> neighbors;
    std::vector <story> history;
    location(unsigned short, unsigned short, unsigned short, unsigned short);
};

#endif