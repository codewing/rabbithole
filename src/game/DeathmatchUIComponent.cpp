//
// Created by codewing on 14/12/2018.
//

#include <sre/Renderer.hpp>
#include "DeathmatchUIComponent.hpp"

DeathmatchUIComponent::DeathmatchUIComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::RENDERABLE) {}

void DeathmatchUIComponent::onRender(sre::RenderPass &renderPass) {

    if(scoreBlue >= maxScore) {
        displayWinner(true);
    } else if(scoreRed >= maxScore) {
        displayWinner(false);
    } else {
        displayStats();
    }
}

void DeathmatchUIComponent::displayWinner(bool isBlue) {
    bool open = true;
    ImGui::SetNextWindowSize(ImVec2(300,100));
    ImGui::Begin("#TestLabel", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowFontScale(3.0f);
    std::string team = isBlue ? "TEAM BLUE" : "TEAM RED";
    auto textWinner = team + " WON";
    ImGui::TextColored(isBlue ? colorBlue : colorRed, textWinner.c_str());

    auto textScore = "  Score " + std::to_string(isBlue ? scoreBlue : scoreRed) + "-" + std::to_string(isBlue ? scoreRed : scoreBlue);
    ImGui::Text(textScore.c_str());
    ImGui::End();
}

void DeathmatchUIComponent::updateScore(int red, int blue) {
    scoreRed = red;
    scoreBlue = blue;
}

void DeathmatchUIComponent::displayStats() {
    bool open = true;
    ImGui::SetNextWindowSize(ImVec2(125,75));
    ImGui::Begin("#TestLabel", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowFontScale(2.0f);
    auto textRed = "Red:  " + std::to_string(scoreRed);
    auto textBlue = "Blue: " + std::to_string(scoreBlue);
    ImGui::TextColored(colorRed, textRed.c_str());
    ImGui::TextColored(colorBlue, textBlue.c_str());
    ImGui::End();
}

void DeathmatchUIComponent::setMaxScore(int maxScore) {
    DeathmatchUIComponent::maxScore = maxScore;
}
