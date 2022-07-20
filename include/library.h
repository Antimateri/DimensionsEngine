#pragma once

struct game;
class World;
class mainWindow;
class textureManager;
struct command;

typedef unsigned long long EntityID;

struct libra{

    game* _game;
    World* _world;
    mainWindow* _mainWindow;
    textureManager* _textureManager;
    EntityID _player;

};

struct representation_coordinates{

    int topX=0;
    int topY=0;

    int selectedX=0;
    int selectedY=0;

};

extern representation_coordinates Representation_coordinates;

extern libra library;