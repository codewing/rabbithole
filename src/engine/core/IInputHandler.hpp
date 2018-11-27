//
// Created by codewing on 28.11.18.
//

#pragma once


#include <SDL_events.h>

class IInputHandler {

public:
    // The methods should return true, if the key event is consumed. This prevents other components to receive the event.
    virtual bool onKeyEvent(SDL_Event &event);
    virtual bool onMouseEvent(SDL_Event& event);
    virtual bool onControllerEvent(SDL_Event& event);
    virtual bool onJoystickEvent(SDL_Event& event);
    virtual bool onTouchEvent(SDL_Event& event);
    virtual bool onOtherEvent(SDL_Event& event);

};

