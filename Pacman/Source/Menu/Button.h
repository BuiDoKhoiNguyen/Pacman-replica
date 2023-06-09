
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL.h>
#include <string>
#include "../Manager/TextManager.h"

class Button {
private:
    SDL_Rect buttonRect;    
    TextManager* normalText;
    TextManager* selectText;
    TextManager* selectTextDetail;
    int buttonStatus;
    std::string bText;
    std::string bDetail;
public:
    static const int BUTTON_OUT = 0;
    static const int BUTTON_IN = 1;
    static const int BUTTON_PRESSED = 2;
    static const int MENU_FONT_SIZE = 28;
    SDL_Color normalColor = { 255, 255, 255, 255 };
    SDL_Color selectColor = { 0, 0, 0, 255 };

    Button(int Width, int Height, int scrPosX, int scrPosY);

    void loadButton(SDL_Renderer*& renderer, std::string text = "", bool isMenu=true);

    void renderButton(SDL_Renderer*& renderer);

    void setStatus(const int status);

    void changeSoundButton(SDL_Renderer*& renderer);

    bool checkMousePos(const int& x, const int& y) const;

    std::string getText() const;
};

#endif // _BUTTON_H
