#include "Pacman.h"
#include <iostream>
#include <algorithm>

typedef std::pair<int, std::pair<int, int> > IP;

Pacman::Pacman() : Object(13, 23) {
    while (!Direction.empty()) Direction.pop();
    while (!Special.empty())   Special.pop();
}

void Pacman::pushtoStack(int newDir) {
    if (!Direction.empty()) Direction.pop();
    Direction.push(newDir);
}

void Pacman::pushSpecialStack(int newDir, std::pair<int, int> nextCross) {
    if (!Special.empty()) {
        if (Special.top().first != newDir) {
            Special.pop();
            Special.push(IP(newDir, nextCross));
        }
    }
    else Special.push(IP(newDir, nextCross));
}

void Pacman::moving() {
    if (!Direction.empty()) {
        int velX = 0, velY = 0, dir = -1;

        switch (Direction.top()) {
        case UP: velX = 0; velY = -pacmanVelocity; dir = 0; break;
        case DOWN: velX = 0; velY = pacmanVelocity; dir = 2; break;
        case LEFT: velX = -pacmanVelocity; velY = 0; dir = 3; break;
        case RIGHT: velX = pacmanVelocity; velY = 0; dir = 1; break;
        }

        changeVelocityDir(velX, velY, dir);

        move();
    }
    // SDL_Event e;
    // while( SDL_PollEvent(&e) != 0 
        //     int velX = 0, velY = 0, dir = -1;
        //     if( e.type == SDL_KEYDOWN ){
        //         if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s){
        //             velX = 0; velY = pacmanVelocity;
        //         }
        //         else if( e.key.keysym.sym == SDLK_UP ||  e.key.keysym.sym == SDLK_w ){
                    
        //             velX = 0; velY = -pacmanVelocity;
        //         } 
        //         else if( e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a ){
        //             velX = -pacmanVelocity; velY = 0;
        //         }
        //         else if( e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d){
        //             velX = pacmanVelocity; velY = 0;
        //         }
        //     }
            
        //     switch (Direction.top()) {
        //         case UP:  dir = 0; break;
        //         case DOWN:  dir = 2; break;
        //         case LEFT:  dir = 3; break;
        //         case RIGHT:  dir = 1; break;
        //     }

        //     changeVelocityDir(velX, velY, dir);

        //     move();
        // }
}

void handle(SDL_Event& e)
{
    
}
void Pacman::turn() {
    if (!Direction.empty()) stopmoving();
    Direction.push(Special.top().first);
    Special.pop();
    //moving();
}

void Pacman::stopmoving() {
    while (!Direction.empty()) Direction.pop();
}

void Pacman::eraseSpecial() {
    while (!Special.empty()) Special.pop();
}
