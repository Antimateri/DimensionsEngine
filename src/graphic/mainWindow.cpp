#include "graphic/mainWindow.h"
#include "graphic/textureManager.h"

mainWindow::mainWindow(){

	int SCREEN_WIDTH=1000;
    int SCREEN_HEIGHT=800;

    BLOCKS_WIDTH=SCREEN_WIDTH/BLOCK_WIDTH;
    BLOCKS_HEIGHT=SCREEN_HEIGHT/BLOCK_HEIGHT;

	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("Prueba", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, rendererFlags);

	library._textureManager = new textureManager(renderer);//SDL_CreateRenderer(window, -1, rendererFlags));

	if (!renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

mainWindow::~mainWindow(){
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
}

void mainWindow::presentScene()
{
	SDL_SetRenderTarget(renderer,NULL);
	SDL_SetRenderDrawColor(renderer,255,0,255,255);
	SDL_RenderClear(renderer);
	_render.draw(renderer);
	SDL_RenderPresent(renderer);
}

void mainWindow::processInput(SDL_Event& _event){
	_render.processInput(_event);
}

void mainWindow::addLayer(toRender* render){
	_render.addLayer(render);
}

void mainWindow::removeLastLayer(){
	_render.removeLastLayer();
}