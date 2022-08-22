#pragma once
#include "definitions.h"

struct libra{

    game* _game;
    World* _world;
    mainWindow* _mainWindow;
    textureManager* _textureManager;
    EntityID _player;
    toRenderInnerAnimation* _innerAnimationManager;
    toRenderOuterAnimation* _outerAnimationManager;

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