//
// Created by codewing on 28.11.18.
//

#include "IInputHandler.hpp"

bool IInputHandler::onKeyEvent(SDL_Event &event) {
    return false;
}

bool IInputHandler::onMouseEvent(SDL_Event &event) {
    return false;
}

bool IInputHandler::onControllerEvent(SDL_Event &event) {
    return false;
}

bool IInputHandler::onJoystickEvent(SDL_Event &event) {
    return false;
}

bool IInputHandler::onTouchEvent(SDL_Event &event) {
    return false;
}

bool IInputHandler::onOtherEvent(SDL_Event &event) {
    return false;
}
