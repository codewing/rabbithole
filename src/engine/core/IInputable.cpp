//
// Created by codewing on 28.11.18.
//

#include "IInputable.hpp"

bool IInputable::onKeyEvent(SDL_Event &event) {
    return false;
}

bool IInputable::onMouseEvent(SDL_Event &event) {
    return false;
}

bool IInputable::onControllerEvent(SDL_Event &event) {
    return false;
}

bool IInputable::onJoystickEvent(SDL_Event &event) {
    return false;
}

bool IInputable::onTouchEvent(SDL_Event &event) {
    return false;
}

bool IInputable::onOtherEvent(SDL_Event &event) {
    return false;
}
