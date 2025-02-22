#include "GridSquare.h"

GridSquare::GridSquare(){
    display = '.';
    type = 'X';
    id = 0;
}

void GridSquare::setDisplay(char display){
    this->display = display;
}

void GridSquare::setType(char type){
    this->type = type;
}

void GridSquare::setID(int id){
    this->id = id;
}

char GridSquare::getDisplay(){
    return display;
}

char GridSquare::getType(){
    return type;
}

int GridSquare::getID(){
    return id;
}

void GridSquare::print(){
    cout << display;
}