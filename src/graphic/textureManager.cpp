#include "graphic/textureManager.h"

textureManager::textureManager(SDL_Renderer* r):r(r), images(NUMBER_TEXTURE_BLOCKS){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    images[0]=SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BLOCK_WIDTH*TEXTURE_BLOCK_SIDE, BLOCK_HEIGHT*TEXTURE_BLOCK_SIDE);
    //SDL_SetTextureBlendMode(images, SDL_BLENDMODE_NONE);
    //SDL_SetRenderTarget(r, images);
    siguiente.x=-1;
    siguiente.y=0;
    siguiente.page=0;
}

textureManager::~textureManager(){
    for(auto image : images)
        SDL_DestroyTexture( image );
}

void textureManager::draw(textureManager::imgDir* in, SDL_Rect* dest){
    SDL_SetRenderTarget(r, NULL);
    SDL_RenderCopy(r, images[in->page], &in->getRect(), dest);
}

textureManager::imgDir textureManager::add(SDL_Texture* in){
    add();
    SDL_RenderCopy(r,in,NULL, &siguiente.getRect());
    return siguiente;
}

textureManager::imgDir textureManager::add(){
    siguiente.x++;
    if(siguiente.x!=TEXTURE_BLOCK_SIDE){
        return siguiente;
    }
    else if(siguiente.y!=TEXTURE_BLOCK_SIDE-1){
        siguiente.x=0;
        siguiente.y++;
        return siguiente;
    }
    else if(siguiente.page!=NUMBER_TEXTURE_BLOCKS-1){
        siguiente.x=0;
        siguiente.y=0;
        siguiente.page++;
        images[siguiente.page]=SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BLOCK_WIDTH*TEXTURE_BLOCK_SIDE, BLOCK_HEIGHT*TEXTURE_BLOCK_SIDE);
        return siguiente;
    }
    else{
        std::cout << "The engine has run out of texture spaces" << std::endl;
        exit(1);
    }
    
}

SDL_Renderer* textureManager::edit(textureManager::imgDir* in){
    if(in!=nullptr) SDL_SetRenderTarget(r, images[in->page]);
    return r;
}