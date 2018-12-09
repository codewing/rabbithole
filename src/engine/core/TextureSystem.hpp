//
// Created by codewing on 21.11.18.
//


#pragma once

#include <map>

#include <sre/SpriteAtlas.hpp>

class TextureSystem {

public:
    TextureSystem() = default;
    sre::Sprite getSpriteFromAtlas(const std::string& spriteName, const std::string& atlas);

private:
    const std::string atlasPath = "assets/images/atlas/";
    std::map<std::string, std::shared_ptr<sre::SpriteAtlas>> spriteAtlasses;

    void loadSpriteAtlas(const std::string& atlas);
    bool hasSpriteAtlas(const std::string& atlas);
    sre::SpriteAtlas& getSpriteAtlas(const std::string& atlas);

    friend class EngineCore;
};


