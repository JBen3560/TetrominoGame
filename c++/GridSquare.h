#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>
using namespace std;

class GridSquare{
    private:
        char display;
        char type;
        int id;

    public:
        GridSquare();
        void setDisplay(char display);
        void setType(char type);
        void setID(int id);
        char getDisplay();
        char getType();
        int getID();
        void print();
};

#endif