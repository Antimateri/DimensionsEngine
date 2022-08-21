#pragma once

#define MAX_COMPONENTS 10
#define MAX_ENTITIES 10

#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 50

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
class toRenderInnerAnimation;
class commandComponent;

typedef unsigned long long EntityID;
