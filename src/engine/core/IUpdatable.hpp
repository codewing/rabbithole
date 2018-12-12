//
// Created by codewing on 28.11.18.
//

#pragma once

class IUpdatable {

public:
    virtual ~IUpdatable() = default;

    virtual void onUpdate(float deltaTime) = 0;

};
