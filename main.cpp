#include <SDL.h>
#include <iostream>

#include <vector>

struct vect2d{
    int x,y;
};

class player{
private:
    SDL_Rect body;
    SDL_Rect eye;
public:
    player(){
        body = {0,0,30,30};
        eye = {body.x+20, 5, 5, 5};
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,0,255);
        SDL_RenderFillRect(renderer, &body);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderFillRect(renderer, &eye);
    }

    SDL_Rect* getBody(){return &body;}
};

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,480,480,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    player mplayer = player();

    SDL_Event event;
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        mplayer.render(renderer);

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
