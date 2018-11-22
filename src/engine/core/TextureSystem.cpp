//
// Created by codewing on 21.11.18.
//

#include "TextureSystem.hpp"

sre::SpriteAtlas& TextureSystem::getSpriteAtlas(const std::string& atlas) {
    if(!hasSpriteAtlas(atlas)) {
        loadSpriteAtlas(atlas);
    }

    return *(spriteAtlasses.find(atlas)->second);
}

sre::Sprite TextureSystem::getSpriteFromAtlas(const std::string& spriteName, const std::string& atlas) {
    return getSpriteAtlas(atlas).get(spriteName);
}

bool TextureSystem::hasSpriteAtlas(const std::string &atlas) {
    return spriteAtlasses.find(atlas) != spriteAtlasses.end();
}

void TextureSystem::loadSpriteAtlas(const std::string& atlas){
    auto spriteAtlas = sre::SpriteAtlas::create(atlasPath + atlas + ".json", atlasPath +  atlas + ".png");
    spriteAtlasses.insert({atlas, spriteAtlas});
}