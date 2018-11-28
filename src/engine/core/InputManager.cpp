//
// Created by codewing on 08.11.18.
//

#include "InputManager.hpp"
#include "ObjectManager.hpp"

#include <SDL.h>
#include <sre/imgui_sre.hpp>

bool InputManager::handleInput() {
    bool keepRunning = true;

    SDL_Event e;
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        sre::ImGui_SRE_ProcessEvent(&e);
        switch (e.type) {
            case SDL_QUIT:
                keepRunning = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keyEvent(e);
                break;
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
                mouseEvent(e);
                break;
            case SDL_CONTROLLERAXISMOTION:
            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
            case SDL_CONTROLLERDEVICEADDED:
            case SDL_CONTROLLERDEVICEREMOVED:
            case SDL_CONTROLLERDEVICEREMAPPED:
                controllerEvent(e);
                break;
            case SDL_JOYAXISMOTION:
            case SDL_JOYBALLMOTION:
            case SDL_JOYHATMOTION:
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            case SDL_JOYDEVICEADDED:
            case SDL_JOYDEVICEREMOVED:
                joystickEvent(e);
                break;
            case SDL_FINGERDOWN:
            case SDL_FINGERUP:
            case SDL_FINGERMOTION:
                touchEvent(e);
                break;
            default:
                otherEvent(e);
                break;
        }
    }

    return keepRunning;
}

void InputManager::keyEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onKeyEvent(e);
    }
}

void InputManager::mouseEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onMouseEvent(e);
    }
}

void InputManager::controllerEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onControllerEvent(e);
    }
}

void InputManager::joystickEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onJoystickEvent(e);
    }
}

void InputManager::touchEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onTouchEvent(e);
    }
}

void InputManager::otherEvent(SDL_Event &e) {
    for(auto& inputComponent : ObjectManager::GetInstance()->getInputComponents()) {
        inputComponent->onOtherEvent(e);
    }
}
