//
// Created by codewing on 14/12/2018.
//


#pragma once


#include "../engine/core/IRenderable.hpp"
#include "../engine/core/Component.hpp"
#include <imgui.h>

class DeathmatchUIComponent : public Component, public IRenderable {
public:
    DeathmatchUIComponent(GameObject *gameObject);

    void onRender(sre::RenderPass &renderPass) override;

    void updateScore(int red, int blue);

    void setMaxScore(int maxScore);

private:
    int scoreRed = 0;
    int scoreBlue = 0;

    int maxScore = 0;

    const ImVec4 colorRed = {1, 0, 0, 1};
    const ImVec4 colorBlue = {0, 0, 1, 1};

    void displayWinner(bool isBlue);
    void displayStats();
};



