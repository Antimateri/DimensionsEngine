//Define all the constants used in the logic and structs used in the game
#pragma once

#define MAX_COMPONENTS 13
#define MAX_ENTITIES 100000

#define BLOCK_WIDTH 50
#define BLOCK_HEIGHT 50

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define ChunkSize 32

#define TEXTURE_BLOCK_SIDE 100
#define NUMBER_TEXTURE_BLOCKS 100

#define NUMBER_COMMANDS_REMEMBERED 10

#define FPS 31

#define INF 1000000000

struct game;
class World;
class mainWindow;
class textureManager;
struct command;
class planningParameter;
struct imgDir;
class effect;
class control;
class innerAnimation;
class outerAnimation;
class toRenderInnerAnimation;
class commandComponent;
class toRenderOuterAnimation;
class IO;

#define planningState std::unordered_map<int, planningParameter *>

typedef unsigned long long EntityID;
