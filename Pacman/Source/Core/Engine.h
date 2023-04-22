
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "../Map/Map.h"
#include "../Object/Pacman.h"
#include "../Object/Ghost.h"
#include "../Object/Item.h"
#include "../Object/TextureSrc.h"
#include "../Manager/TickManager.h"
#include "../Manager/GameManager.h"
#include "../Manager/SoundManager.h"

class Engine {
private:
    Map* map;
    Pacman* pacman = nullptr;
    Ghost* blinky = nullptr;
    Ghost* pinky = nullptr;
    Ghost* inky = nullptr;
    Ghost* clyde = nullptr;
    Ghost* greendy = nullptr;
    Ghost* friendy = nullptr;
    Item* apple;
    TextureSrc* objectTexture;
    TickManager* tickManager;
    GameManager* gameManager;
    SoundManager* soundManager;
    SDL_Texture* nextLevel;
    SDL_Texture* ready;
    bool runningEGBoard = false;
    bool eatGreenApple = false;
    int waitTime = 0;
protected:
    void respawnObject();

    void ghostMove(Ghost*& ghost);

    void pacmanMeatGhost(Ghost*& ghost);

    void renderGhost(SDL_Renderer*& renderer, Ghost*& ghost, int ghostID);
public:
    Engine();

    ~Engine();

    void newGame();

    void init(SDL_Renderer*& renderer);

    void handleEvent(SDL_Event& e, std::vector<std::string>& scoreData);

    void loop(bool& exitToMenu);

    void render(SDL_Renderer*& renderer, const std::vector<std::string>& scoreData);

};

#endif // _ENGINE_H_
