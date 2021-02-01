#include <SDL.h>
#include <iostream>

#include <vector>
#include <math.h>

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
        body = {200,320,20,20};
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


class enemy{
private:
    bool frightened;
    SDL_Rect body;
    SDL_Rect eye;
    int id;
public:
    int lmd;
    bool moved;
    enemy(int id){
        moved = false;
        frightened = false;
        this->id = id;
        if(id == 0){
            body = {7*20,10*20,20,20};
        }
        if(id == 1){
            body = {9*20,10*20,20,20};
        }
        if(id == 2){
            body = {10*20,10*20,20,20};
        }
        if(id == 3){
            body = {11*20,10*20,20,20};
        }
        std::cout<<"passed"<<std::endl;
        eye = {body.x+7,body.y+3,6,6};
        std::cout<<"passed"<<std::endl;
    }

    void moveX(int dir){
        body.x+=dir*20;
        if(body.x>400){
            body.x=0;
        }
        if(body.x<0){
            body.x=400;
        }
        eye = {body.x+7,body.y+3,6,6};
    }
    void moveY(int dir){
        body.y+=dir*20;
        eye = {body.x+7,body.y+3,6,6};
    }

    void render(SDL_Renderer* renderer){
        if(id == 0){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &body);
        }
        if(id == 1){
            SDL_SetRenderDrawColor(renderer, 255, 184, 255, 255);
            SDL_RenderFillRect(renderer, &body);
        }
        if(id == 2){
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
            SDL_RenderFillRect(renderer, &body);
        }
        if(id == 3){
            SDL_SetRenderDrawColor(renderer, 255, 184, 81, 255);
            SDL_RenderFillRect(renderer, &body);
        }
        if(frightened){
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 100);
            SDL_RenderFillRect(renderer, &body);
        }
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &eye);
    }

    SDL_Rect* getBody(){return &body;}

};
void blinkyPF(enemy* _enemy, player mplayer, bool chasing);
void pinkyPF(enemy* _enemy);
void inkyPF(enemy* _enemy);
void clydePF(enemy* _enemy);

void mapRender(SDL_Renderer* renderer){
    SDL_Rect rect;
    for(int i = 0; i < 22; i++){
        for(int j = 0; j < 21; j++){
            if(_maps[i*21+j]){
                rect = {j*20, i*20, 20, 20};
                if(i*21+j == 21*9+10){
                    SDL_SetRenderDrawColor(renderer, 0,100,255,255);
                    SDL_RenderFillRect(renderer, &rect);
                }else{
                    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
                    SDL_RenderFillRect(renderer, &rect);
                }
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

float mutlak(float val);

int main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow("apps", 100,100,420,440,false);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    player mplayer = player(&_maps);
    std::vector<enemy*> enemies;
    for(int i = 0; i < 4; i++){enemies.push_back(new enemy(i));}

    std::vector<point> points;
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            if(j!=0 && j!=20){
                if(i==8 || i==12 || i == 10){
                    if(j>4 && j<16){
                        if(i == 10 ){
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
                        if((i == 2 && j == 2)||(i == 2 && j == 18)||(i == 16 && j == 2)||(i == 16 && j == 18)){
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
    int chaseTime = SDL_GetTicks();
    bool chasing = true;
    while(true){
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        mplayer.render(renderer);
        mapRender(renderer);
        pointRender(renderer, points);
        for(int i = 0; i < 4; i++){
            enemies[i]->render(renderer);
        }

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
            break;
        }
        mplayer.control(&event);

        if(chasing){
            if(SDL_GetTicks()-chaseTime>=20*1000){
                chasing = false;
            }
        }else{
            if(SDL_GetTicks()-chaseTime>=10*1000){
                chasing = true;
            }
        }

        if(SDL_GetTicks()-frame>=175){
            if(points.empty()){
                if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2)){
                    break;
                }
            }else{
                mplayer.update();
                blinkyPF(enemies[0],mplayer,chasing);
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

    for(int i = 0; i < 4; i++){delete enemies[i];}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

float mutlak(float val){
    return val>=0 ? val:-val;
}

void blinkyPF(enemy* _enemy, player mplayer, bool chasing){
    vect2d cPos;
    if(chasing){
        cPos = {mplayer.getBody()->x,mplayer.getBody()->y};
    }else{
        cPos = {480,0};
    }
    float range[4];
        range[0] = range[1] = range[2] = range[3] = 650.f;
    int dir[4];
        dir[0] = 2; dir[1] = 3; dir[2] = 0; dir[3] = 1;
    if(!_maps[_enemy->getBody()->y/20*21+_enemy->getBody()->x/20-1]){
        if(_enemy->getBody()->x==0){
            range[2] = mutlak(sqrt(float(
                       pow(cPos.x-(420),2)+pow(cPos.y-_enemy->getBody()->y,2))));
        }else{
            range[2] = mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x-20),2)+pow(cPos.y-_enemy->getBody()->y,2))));
            if(range[2]>mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x-440),2)+pow(cPos.y-_enemy->getBody()->y,2))))){
                range[2] = mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x-440),2)+pow(cPos.y-_enemy->getBody()->y,2))));
            }
        }
    }
    if(!_maps[_enemy->getBody()->y/20*21+_enemy->getBody()->x/20+1]){
        if(_enemy->getBody()->x>=420){
            range[2] = mutlak(sqrt(float(
                       pow(cPos.x-(0),2)+pow(cPos.y-_enemy->getBody()->y,2))));
        }else{
            range[3] = mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x+20),2)+pow(cPos.y-_enemy->getBody()->y,2))));
            if(range[3]>mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x+440),2)+pow(cPos.y-_enemy->getBody()->y,2))))){
                range[3] = mutlak(sqrt(float(
                                  pow(cPos.x-(_enemy->getBody()->x+440),2)+pow(cPos.y-_enemy->getBody()->y,2))));
            }
        }
    }
    if(!_maps[_enemy->getBody()->y/20*21+_enemy->getBody()->x/20-21]){
        range[0] = mutlak(sqrt(float(
                                  pow(cPos.x-_enemy->getBody()->x,2)+pow(cPos.y-(_enemy->getBody()->y-20),2)
                                  )));
    }
    if(!_maps[_enemy->getBody()->y/20*21+_enemy->getBody()->x/20+21]){
        range[1] = mutlak(sqrt(float(
                                  pow(cPos.x-_enemy->getBody()->x,2)+pow(cPos.y-(_enemy->getBody()->y+20),2)
                                  )));
    }
    for(int i = 1; i < 4; i++){
        for(int j = 0; j < i; j++){
            if(range[j]>range[i]){
                float temp = range[j];
                range[j] = range[i];
                range[i] = temp;
                int tdir = dir[j];
                dir[j] = dir[i];
                dir[i] = tdir;
            }
        }
    }
    choose:
    std::cout<<dir[0]<<":"<<range[0]<<std::endl;
    if(!_enemy->moved){
        _enemy->lmd = dir[0];
        _enemy->moved = true;
    }
    if(_enemy->getBody()->x>=400 && _enemy->lmd != 0){
        dir[0] = 1;
    }
    if(_enemy->getBody()->x<=0 && _enemy->lmd != 1){
        dir[0] = 0;
    }
    if(dir[0] == 0){
        if(_enemy->lmd!=1){
            _enemy->moveX(-1);
            _enemy->lmd = 0;
        }else{
            dir[0] = dir[1];
            goto choose;
        }
    }
    if(dir[0] == 1){
        if(_enemy->lmd!=0){
            _enemy->moveX(1);
            _enemy->lmd = 1;
        }else{
            dir[0] = dir[1];
            goto choose;
        }
    }
    if(dir[0] == 2){
        if(_enemy->lmd!=3){
            _enemy->moveY(-1);
            _enemy->lmd = 2;
        }else{
            dir[0] = dir[1];
            goto choose;
        }
    }
    if(dir[0] == 3){
        if(_enemy->lmd!=2){
            _enemy->moveY(1);
            _enemy->lmd = 3;
        }else{
            dir[0] = dir[1];
            goto choose;
        }
    }
}
