#include <SDL.h>
#include <iostream>

#include <vector>

struct vect2d{
    int x,y;
};

std::vector<bool> _maps = {
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
    0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,0,
    0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,
    0,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,
    0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
    1,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1,1,
    0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,
    1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
    0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,
    0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,
    0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,
    0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0,
    0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
    0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,0,
    0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,
    0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,
    0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
};

class player{
private:
    SDL_Rect body, mouth;
    bool moveD[4];
public:
    player(std::vector<bool>* maps){
        body = {200,300,20,20};
        mouth = {body.x+10, body.y+7, 10, 6};
        moveD[0] = moveD[1] = moveD[2] = moveD[3] = 0;
    }

    void render(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255,255,0,255);
        SDL_RenderFillRect(renderer, &body);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderFillRect(renderer, &mouth);
    }

    void control(SDL_Event* event){
        if(event->type == SDL_KEYDOWN){
            if(event->key.keysym.sym == SDLK_a){
                if(!_maps[((body.y/20)*21)+(body.x/20)-1]){
                    moveD[0] = 1;
                    moveD[1] = moveD[2] = moveD[3] = 0;
                }
            }
            if(event->key.keysym.sym == SDLK_d){
                if(!_maps[((body.y/20)*21)+(body.x/20)+1]){
                    moveD[1] = 1;
                    moveD[0] = moveD[2] = moveD[3] = 0;
                }
            }
            if(event->key.keysym.sym == SDLK_w){
                if(!_maps[((body.y/20)*21)+(body.x/20)-21]){
                    moveD[2] = 1;
                    moveD[0] = moveD[1] = moveD[3] = 0;
                }
            }
            if(event->key.keysym.sym == SDLK_s){
                if(!_maps[((body.y/20)*21)+(body.x/20)+21]){
                    moveD[3] = 1;
                    moveD[0] = moveD[1] = moveD[2] = 0;
                }
            }
        }
    }

    void update(){
        if(moveD[0]){
            bool istouch = false;
            if(_maps[((body.y/20)*21)+(body.x/20)-1]){
                istouch = true;
            }
            if(!istouch){
                body.x-=20;
                mouth = {body.x, body.y+7, 10, 6};
            }
        }
        if(moveD[1]){
            bool istouch = false;
            if(_maps[((body.y/20)*21)+(body.x/20)+1]){
                istouch = true;
            }
            if(!istouch){
                body.x+=20;
                mouth = {body.x+10, body.y+7, 10, 6};
            }
        }
        if(moveD[2]){
            bool istouch = false;
            if(_maps[((body.y/20)*21)+(body.x/20)-21]){
                istouch = true;
            }
            if(!istouch){
                body.y-=20;
                mouth = {body.x+7, body.y, 6, 10};
            }
        }
        if(moveD[3]){
            bool istouch = false;
            if(_maps[((body.y/20)*21)+(body.x/20)+21]){
                istouch = true;
            }
            if(!istouch){
                body.y+=20;
                mouth = {body.x+7, body.y+10, 6, 10};
            }
        }
    }

    SDL_Rect* getBody(){return &body;}
};

void mapRender(SDL_Renderer* renderer){
    SDL_Rect rect;
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            if(_maps[i*21+j]){
                rect = {j*20, i*20, 20, 20};
                SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,420,420,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    player mplayer = player(&_maps);

    SDL_Event event;
    int frame = SDL_GetTicks();
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

        if(SDL_GetTicks()-frame>=150){
            mplayer.update();
            std::cout<<mplayer.getBody()->x<<":"<<mplayer.getBody()->y<<std::endl;
            frame = SDL_GetTicks();
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
