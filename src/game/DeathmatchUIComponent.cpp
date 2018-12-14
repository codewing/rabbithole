//
// Created by codewing on 14/12/2018.
//

#include <sre/Renderer.hpp>
#include "DeathmatchUIComponent.hpp"

DeathmatchUIComponent::DeathmatchUIComponent(GameObject *gameObject) : Component(gameObject, ComponentFlag::RENDERABLE) {}

void DeathmatchUIComponent::onRender(sre::RenderPass &renderPass) {

    bool open = true;
    ImGui::Begin("#TestLabel", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowFontScale(2.0f);
    auto textRed = "Red: " + std::to_string(scoreRed);
    auto textBlue = "Blue: " + std::to_string(scoreBlue);
    ImGui::TextColored(colorRed, textRed.c_str());
    ImGui::TextColored(colorBlue, textBlue.c_str());

    ImGui::End();
}

void DeathmatchUIComponent::updateScore(int red, int blue) {
    scoreRed = red;
    scoreBlue = blue;
}
