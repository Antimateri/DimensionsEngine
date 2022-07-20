#include "graphic/textureManager.h"

textureManager::textureManager(SDL_Renderer* r):r(r){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    images=SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BLOCK_WIDTH*TEXTURE_BLOCK_SIDE, BLOCK_HEIGHT*TEXTURE_BLOCK_SIDE);
    //SDL_SetTextureBlendMode(images, SDL_BLENDMODE_NONE);
    //SDL_SetRenderTarget(r, images);
    siguiente.x=-1;
    siguiente.y=0;
}

textureManager::~textureManager(){
    SDL_DestroyTexture( images );
}

void textureManager::draw(textureManager::imgDir* in, SDL_Rect* dest){
    SDL_SetRenderTarget(r, NULL);
    SDL_RenderCopy(r, images, &in->getRect(), dest);
}

textureManager::imgDir textureManager::add(SDL_Texture* in){
    add();
    SDL_RenderCopy(r,in,NULL, &siguiente.getRect());
    return siguiente;
}

textureManager::imgDir textureManager::add(){
    siguiente.x++;
    if(siguiente.x==TEXTURE_BLOCK_SIDE){
        siguiente.x=0;
        siguiente.y++;
    }
    return siguiente;
}

SDL_Renderer* textureManager::edit(){
    SDL_SetRenderTarget(r, images);
    return r;
}