//
// Created by codewing on 08.11.18.
//

#pragma once


#include <SDL_events.h>

class InputManager {

public:
    bool handleInput();

private:


    void keyEvent(SDL_Event& e);
    void mouseEvent(SDL_Event& e);
    void controllerEvent(SDL_Event& e);
    void joystickEvent(SDL_Event& e);
    void touchEvent(SDL_Event& e);
    void otherEvent(SDL_Event& e);
};

