#include "Window.h"
#include "../Manager/LogStatus.h"

Window::Window() {
    window = nullptr;
    renderer = nullptr;
    playState = nullptr;
    startMenu = nullptr;
    runningMenu = false;
}

Window::~Window() {
    delete playState;
    playState = nullptr;

    delete startMenu;
    startMenu = nullptr;

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Console->Status( SDL_GetError() );
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        Console->Status("Window opened successfully!");
        Running = true;

        if (window == nullptr) {
            Console->Status( SDL_GetError() );
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully!");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (TTF_Init() < 0) Console->Status( TTF_GetError() );
            else Console->Status("TTF Ready!");

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) Console->Status( Mix_GetError() );
            else Console->Status("Audio Ready!");
            Mix_Volume(-1, MIX_MAX_VOLUME);

            std::ifstream file("score.txt");
           
            if( file.is_open() )
            {
                std::string t = "";
                for( int i=0; i<10 ; i++ )
                {
                    std::getline(file,t);
                    highScore.push_back(t);
                }
                file.close();
            }
            else std::cout<<"Failed to open file!\n";
            // freopen("score.txt", "r", stdin);
            // std::string t = "";
            // for (int i = 0; i < 10; ++i) {
            //     std::getline(std::cin, t);
            //     highScore.push_back(t);
            // }
        }
    }
}

void Window::quitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    Mix_Quit();
    TTF_Quit();
    atexit(SDL_Quit);
    Console->Status("Successfully exited!");
    
    std::ofstream file("score.txt");
    if( file.is_open() )
    {
        for( int i=0; i<10; i++ ) 
        {   
            file<<highScore[i]<<std::endl;
        }
        file.close();
    }
    else std::cout<<"Failed to open file!"<<std::endl;
    
    
    // freopen("score.txt", "w", stdout);
    // for (int i = 0; i < 10; ++i) std::cout << highScore[i] << std::endl;
    return;
}

void Window::runGame() {
    startMenu = new Menu(420, 320, startMenuButtonText.size(), 280, 30);
    //init menu 262, 170
    startMenu->init(renderer, "Source/Assets/Menu Image/menu.png", startMenuButtonText);
    startMenu->changeRunStatus();

    SDL_Event e;
    runningMenu = true;
    bool startGame = false;
    playState = new PlayStateManager();

    while (Running) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) Running = false;
            else {
                if (runningMenu) {
                    startMenu->handleEvent(e, renderer);
                    switch (startMenu->getStatus()) {
                        case Menu::PLAY_BUTTON_PRESSED:
                            runningMenu = false; break;
                        case Menu::EXIT_BUTTON_PRESSED:
                            Running = false; break;
                    }
                }
                else {
                    playState->handleEvent(e, renderer, runningMenu, highScore);
                    if (runningMenu){
                        //if press exit to Menu -> "startGame" will be reset game
                        startGame = false;
                        startMenu->reOpen();
                    }   
                }
            }
        }
        if (!runningMenu) {
            
            if (!startGame) {
                playState->newGame(renderer);
                startGame = true;
            }
            playState->runGame(runningMenu);
            //if (runningMenu) startMenu->reOpen(), startGame = false;
        }

        //render background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (runningMenu)
            startMenu->render(renderer, highScore);
        else playState->render(renderer, highScore);

        SDL_RenderPresent(renderer);
    }
}
