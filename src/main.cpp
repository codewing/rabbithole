#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "game/WormholeGame.hpp"

int main() {

    WormholeGame game ({800, 600});
    game.runGame();
};