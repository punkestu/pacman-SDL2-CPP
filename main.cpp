#include <SDL.h>
#include <iostream>

#include <vector>

struct vect2d{
    int x,y;
};

std::vector<bool> _maps = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

class player{
private:
    SDL_Rect body;
    SDL_Rect eye;
    bool moveD[4];
public:
    player(std::vector<bool>* maps){
        body = {100,100,30,30};
        eye = {body.x+20, body.y+5, 5, 5};
        moveD[0] = moveD[1] = moveD[2] = moveD[3] = 0;
        for(int i = 0; i < 24; i++){
            for(int j = 0; j < 24; j++){
                std::cout<<_maps[24*i+j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,0,255);
        SDL_RenderFillRect(renderer, &body);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderFillRect(renderer, &eye);
    }

    void control(SDL_Event* event){
        if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_a){
                moveD[0] = 1;
                moveD[1] = 0;
                moveD[2] = 0;
                moveD[3] = 0;
            }
            if(event->key.keysym.sym == SDLK_d){
                moveD[0] = 0;
                moveD[1] = 1;
                moveD[2] = 0;
                moveD[3] = 0;
            }
            if(event->key.keysym.sym == SDLK_w){
                moveD[0] = 0;
                moveD[1] = 0;
                moveD[2] = 1;
                moveD[3] = 0;
            }
            if(event->key.keysym.sym == SDLK_s){
                moveD[0] = 0;
                moveD[1] = 0;
                moveD[2] = 0;
                moveD[3] = 1;
            }
        }
    }

    void update(){
        if(moveD[0]){
            body.x--;
            eye = {body.x+5, body.y+5, 5, 5};
        }
        if(moveD[1]){
            body.x++;
            eye = {body.x+20, body.y+5, 5, 5};
        }
        if(moveD[2]){
            body.y--;
            eye = {body.x+5, body.y+5, 5, 5};
        }
        if(moveD[3]){
            body.y++;
            eye = {body.x+5, body.y+20, 5, 5};
        }
    }

    SDL_Rect* getBody(){return &body;}
};

void mapRender(SDL_Renderer* renderer){
    SDL_Rect rect;
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 24; j++){
            if(_maps[i*24+j]){
                rect = {j*20, i*20, 20, 20};
                SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,480,480,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    player mplayer = player(&_maps);

    SDL_Event event;
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        mplayer.render(renderer);
        mapRender(renderer);

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }
        mplayer.control(&event);

        mplayer.update();


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
