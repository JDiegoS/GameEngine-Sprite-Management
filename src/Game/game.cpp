#include <iostream>
#include "game.h"
#include "stexture.cpp"

SDL_Rect ball;
SDL_Rect paddle1;
SDL_Rect paddle2;
int speed = 2;
int player_speed = 50;

Game::Game ()
{
    std::cout << "SPRITE MANAGEMENT" << std::endl;
    std::cout << " " << std::endl;

    FPS = 60;
    frameDuration = (1.0f / FPS) * 1000.0f;
    counter = 0;

}

Game::~Game ()
{
    std::cout << "~Game" << std::endl;
}
void Game::setup(){

}

void Game::frameStart(){
    frameStartTimeStamp = SDL_GetTicks();
    if (frameEndTimeStamp)
    {
        dT = (frameStartTimeStamp - frameEndTimeStamp) / 1000.0f;
    }
    else
    {
        dT = 0;
    }
}

void Game::frameEnd(){
    frameEndTimeStamp = SDL_GetTicks();

    float actualFrameDuration = frameEndTimeStamp - frameStartTimeStamp;

    if (actualFrameDuration < frameDuration){
        SDL_Delay(frameDuration - actualFrameDuration);
    }
    counter++;


}

Uint32 fragment(Uint32 currentColor, float dT)
{
    if (currentColor == 0) {
        return currentColor;
    }
    return currentColor - 18;
}

void Game::init(const char* title, int widthi, int heighti){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(title, 0, 0, widthi, heighti, 0);
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    window_height = heighti;
    window_width = widthi;
    isRunning = true;

}
void Game::handleEvents(){

    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            isRunning = false;
        }

    }

}


void Game::update(){


}
void Game::render(){

    SDL_SetRenderDrawColor(renderer, 50, 50, 100, 1);
    SDL_RenderClear(renderer);

    STexture tex = STexture(renderer,window);
    tex.load("./assets/bullet.png");
    tex.executeShader(fragment, dT);
    tex.render(100, 100, 300, 300);

    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 1);

    /*
    SDL_Surface* surface = IMG_Load("./assets/1.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, nullptr, &ball);

    SDL_DestroyTexture(texture);
    */

    SDL_RenderFillRect(renderer, &paddle1);

    SDL_RenderPresent(renderer);

}
void Game::clean(){

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();


}
bool Game::running(){
    return isRunning;
}