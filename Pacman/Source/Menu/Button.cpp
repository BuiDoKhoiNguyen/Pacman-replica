#include "Button.h"

Button::Button(int Width, int Height, int scrPosX, int scrPosY) {
    buttonRect = { scrPosX, scrPosY, Width, Height };
    normalText = new TextManager(24);
    selectText = new TextManager(24);
    selectTextDetail = new TextManager(18);
}

void Button::loadButton(SDL_Renderer*& renderer, std::string text,bool isMenu) {
    if (text == "") return;
    if( !isMenu ){
        normalColor={0, 0, 0, 255 };
        selectColor={255, 255, 255, 255};
    } 

    normalText->loadRenderText(renderer, text, normalColor);
    selectText->loadRenderText(renderer, text, selectColor);
    bText = text;
    if (text == "New Game") bDetail = "Press Enter to play a new game.";
    else if (text == "Resume") bDetail = "Press Enter to continue the game.";
    else if (text == "How to Play") bDetail = "Press Enter for instructions on how to play.";
    else if (text == "High Scores") bDetail = "Press Enter for High score.";
    else if (text == "Sound: ON") bDetail = "Press Enter to change sound status.";
    else if (text == "Exit") bDetail = "Press Enter to quit the game.";
    else if (text == "Exit to Start Menu") bDetail = "Press Enter to return to the Start Menu.";
    else bDetail = "";

    //detail of text menu ( the text in the bottom of screen )
    if (bDetail != "") selectTextDetail->loadRenderText(renderer, bDetail, normalColor);
    else {
        delete selectTextDetail;
        selectTextDetail = nullptr;
    }
}

void Button::renderButton(SDL_Renderer*& renderer) {
    if (buttonStatus == BUTTON_IN) {
        //draw pointer with shape rectangle
        SDL_SetRenderDrawColor(renderer, 255, 247, 0, 255);
        SDL_RenderFillRect(renderer, &buttonRect);
        //render text inside rectangle to other color
        SDL_SetRenderDrawColor(renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        selectText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2, TextManager::CENTER);
  
        if (selectTextDetail != nullptr) {
            SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
            selectTextDetail->renderText(renderer, 420, 470, TextManager::CENTER);
        }
    }
    else if (buttonStatus == BUTTON_OUT) {
        SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
        normalText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2, TextManager::CENTER);
    }
}

void Button::setStatus(const int status) {
    buttonStatus = status;
}

void Button::changeSoundButton(SDL_Renderer*& renderer) {
    if (bText == "Sound: ON") bText = "Sound: OFF";
    else bText = "Sound: ON";
    normalText->loadRenderText(renderer, bText, normalColor);
    selectText->loadRenderText(renderer, bText, selectColor);
    buttonStatus = BUTTON_IN;
}
//????????
bool Button::checkMousePos(const int& x, const int& y) const {
    if (x < buttonRect.x || x > buttonRect.x + buttonRect.w) return false;
    if (y < buttonRect.y || y > buttonRect.y + buttonRect.h) return false;
    return true;
}

std::string Button::getText() const {
    return bText;
}
