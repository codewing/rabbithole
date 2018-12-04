//
// Created by codewing on 07.11.18.
//

#include "WormholeGame.hpp"
#include <glm/glm.hpp>
#include "MovementComponent.hpp"
#include "LevelGenerator.hpp"
#include "Rabbit.hpp"
#include <string>


WormholeGame::WormholeGame(EngineCore &engine) : GameModule(engine) {}

void WormholeGame::update(float deltaTime) {

}

void WormholeGame::initialize() {

    //Rabbit redRabbit {engine, "red", {200, 600}};
    //Rabbit blueRabbit {engine, "blue", {300, 700}};

    LevelGenerator level({800,600}, 0.6);
    level.generateLevel();

    sre::Camera cam;
    cam.setOrthographicProjection(500,-1,1);
    auto x = 300;
    auto y = 500;
    glm::vec3 eye (x, y, 0);
    glm::vec3 at (x, y, -1);
    glm::vec3 up (0, 1, 0);
    cam.lookAt(eye, at, up);
    ObjectManager::GetInstance()->GetCameraManager().RegisterCamera("main", cam);
    ObjectManager::GetInstance()->GetCameraManager().SetActiveCamera("main");
}
