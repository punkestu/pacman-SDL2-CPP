#include <SDL.h>
#include <iostream>

#include <vector>

struct vect2d{
    int x,y;
};

struct point{
    vect2d pos; bool big;
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
    1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,
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
    short cmd, lcmd;
    bool moveD[4];
public:
    player(std::vector<bool>* maps){
        body = {200,300,20,20};
        mouth = {body.x+7, body.y, 6, 10};
        cmd = 0; lcmd = 0;
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
                moveD[0] = 1;
            }
            if(event->key.keysym.sym == SDLK_d){
                moveD[1] = 1;
            }
            if(event->key.keysym.sym == SDLK_w){
                moveD[2] = 1;
            }
            if(event->key.keysym.sym == SDLK_s){
                moveD[3] = 1;
            }
        }
        if(event->type == SDL_KEYUP){
            if(event->key.keysym.sym == SDLK_a){
                moveD[0] = 0;
            }
            if(event->key.keysym.sym == SDLK_d){
                moveD[1] = 0;
            }
            if(event->key.keysym.sym == SDLK_w){
                moveD[2] = 0;
            }
            if(event->key.keysym.sym == SDLK_s){
                moveD[3] = 0;
            }
        }
//        cmd = 0;
        for(int i = 0; i < 4; i++){
            if(moveD[i]){
                cmd = i+1;
            }
        }
    }

    void update(){
        if(cmd == 1){
            if(!_maps[((body.y/20)*21)+(body.x/20)-1]){
                lcmd = cmd;
            }
        }
        if(cmd == 2){
            //std::cout<<"right"<<std::endl;
            if(!_maps[((body.y/20)*21)+(body.x/20)+1]){
                lcmd = cmd;
            }
        }
        if(cmd == 3){
            if(!_maps[((body.y/20)*21)+(body.x/20)-21]){
                lcmd = cmd;
            }
        }
        if(cmd == 4){
            if(!_maps[((body.y/20)*21)+(body.x/20)+21]){
                lcmd = cmd;
            }
        }
        //std::cout<<lcmd<<std::endl;
        if(lcmd == 1){
            bool istouch = false;
            if(body.x!=0){
                if(_maps[((body.y/20)*21)+(body.x/20)-1]){
                    istouch = true;
                }
            }
            if(!istouch){
                if(body.x == 0){
                    body.x=400;
                }else{
                    body.x-=20;
                }
                mouth = {body.x, body.y+7, 10, 6};
            }
        }
        if(lcmd == 2){
            bool istouch = false;
            if(body.x!=400){
                if(_maps[((body.y/20)*21)+(body.x/20)+1]){
                    istouch = true;
                }
            }
            if(!istouch){
                if(body.x == 400){
                    body.x = 0;
                }else{
                    body.x+=20;
                }
                mouth = {body.x+10, body.y+7, 10, 6};
            }
        }
        if(lcmd == 3){
            bool istouch = false;
            if(_maps[((body.y/20)*21)+(body.x/20)-21]){
                istouch = true;
            }
            if(!istouch){
                body.y-=20;
                mouth = {body.x+7, body.y, 6, 10};
            }
        }
        if(lcmd == 4){
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

void pointRender(SDL_Renderer* renderer, std::vector<point> points){
    SDL_Rect rect;
    for(unsigned int i = 0; i < points.size(); i++){
        if(points[i].big){
            rect = {points[i].pos.x,points[i].pos.y,16,16};
        }else{
            rect = {points[i].pos.x,points[i].pos.y,10,10};
        }
        SDL_SetRenderDrawColor(renderer, 150,150,0,255);
        SDL_RenderFillRect(renderer, &rect);
    }
}


int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,420,420,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    player mplayer = player(&_maps);

    std::vector<point> points;
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            if(j!=0 && j!=20){
                if(i==7 || i==11 || i == 9){
                    if(j>4 && j<16){
                        if(i == 9 ){
                            if(j<8 || j>12){
                                if(!_maps[i*21+j]){
                                    points.push_back({{j*20+5,i*20+5},0});
                                }
                            }
                        }else{
                            if(!_maps[i*21+j]){
                                points.push_back({{j*20+5,i*20+5},0});
                            }
                        }
                    }
                }else{
                    if(!_maps[i*21+j]){
                        if((i == 2 && j == 2)||(i == 2 && j == 18)||(i == 18 && j == 2)||(i == 18 && j == 18)){
                            points.push_back({{j*20+2,i*20+2},1});
                        }else{
                            if(i!=15 || j!=10){
                                points.push_back({{j*20+5,i*20+5},0});
                            }
                        }
                    }
                }
            }
        }
    }

    SDL_Event event;
    int frame = SDL_GetTicks();
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        mplayer.render(renderer);
        mapRender(renderer);
        pointRender(renderer, points);

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }
        mplayer.control(&event);

        if(SDL_GetTicks()-frame>=125){
            if(points.empty()){
                if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2)){
                    break;
                }
            }else{
                mplayer.update();
            }
            //std::cout<<mplayer.getBody()->x<<":"<<mplayer.getBody()->y<<std::endl;
            frame = SDL_GetTicks();
        }

        for(std::vector<point>::iterator it = points.begin(); it != points.end(); it++){
            if(mplayer.getBody()->x < it->pos.x+10 && mplayer.getBody()->x+20 > it->pos.x &&
               mplayer.getBody()->y < it->pos.y+10 && mplayer.getBody()->y+20 > it->pos.y){
                points.erase(it);
                it--;
            }
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
