#pragma once

#include "common.h"

class textureManager{
public:

    struct imgDir{
    private:
        SDL_Rect pos;

    public:
        int x;
        int y;
        int page;

        imgDir():x(0), y(0){};

        void operator()(imgDir copia){
            this->x=copia.x;
            this->y=copia.y;
            this->page=copia.page;
        }

        void operator=(imgDir copia){
            this->x=copia.x;
            this->y=copia.y;
            this->page=copia.page;
        }

        SDL_Rect& getRect(){
            pos.x=x*BLOCK_WIDTH;
            pos.y=y*BLOCK_HEIGHT;
            pos.w=BLOCK_WIDTH;
            pos.h=BLOCK_HEIGHT;
            return pos;
        }
    };

    textureManager(SDL_Renderer* r);

    ~textureManager();

    void draw(textureManager::imgDir* in, SDL_Rect* dest);

    imgDir add(SDL_Texture* in);

    imgDir add();

    SDL_Renderer* edit(textureManager::imgDir* in);

private:

    SDL_Renderer* r;
    std::vector<SDL_Texture*> images;
    imgDir siguiente;

};