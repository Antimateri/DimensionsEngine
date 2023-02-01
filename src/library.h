//includes the global variable library, in the future this may be eliminated for a more object oriented approach
#pragma once

#include "definitions.h"

struct libra{

    mainWindow* _mainWindow;            //the window class
    textureManager* _textureManager;    //manage and stores textures
    EntityID _player;                   //the player entity (ugly, to change)
    toRenderInnerAnimation* _innerAnimationManager; //manage the animations which change the texture of the entities
    toRenderOuterAnimation* _outerAnimationManager; //manage the animations which paint over the entities
    //quitar
    command* aux; 


};

struct representation_coordinates{

    int topX=0;
    int topY=0;

    int selectedX=0;
    int selectedY=0;

};

extern representation_coordinates Representation_coordinates;

extern libra library;