#pragma once

#define MAX_COMPONENTS 10
#define MAX_ENTITIES 10

#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 50

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define TEXTURE_BLOCK_SIDE 100

#define NUMBER_COMMANDS_REMEMBERED 10

#define FPS 31

#define INF 1000000000

struct game;
class World;
class mainWindow;
class textureManager;
struct command;
class innerAnimation;
class outerAnimation;
class toRenderInnerAnimation;
class commandComponent;
class toRenderOuterAnimation;

typedef unsigned long long EntityID;
