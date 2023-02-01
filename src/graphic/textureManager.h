//manages textures, more of a sketch now
#pragma once

#include "common.h"

class textureManager{
public:

    //struct to manage the position of the images
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

        //returns the position of the image in the SDL_Texture
        SDL_Rect& getRect(){
            pos.x=x*BLOCK_WIDTH;
            pos.y=y*BLOCK_HEIGHT;
            pos.w=BLOCK_WIDTH;
            pos.h=BLOCK_HEIGHT;
            return pos;
        }
    };

    textureManager(SDL_Renderer* r);    //constructor, takes the renderer to draw on

    ~textureManager();

    void draw(textureManager::imgDir* in, SDL_Rect* dest);  //draws the image in in the position dest in the window renderer

    imgDir add(SDL_Texture* in);   //returns the next available image space and draws the texture in it

    imgDir add();   //returns the next available image space

    SDL_Renderer* edit(textureManager::imgDir* in); //returns the renderer to draw on the texture where the image in is

private:

    SDL_Renderer* r;
    std::vector<SDL_Texture*> images;
    imgDir siguiente;

};