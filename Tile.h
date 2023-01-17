#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile {

public:

    unsigned char isMine;
    int indy;
    bool recussed;
    bool isFlagged;
    bool isClicked;
    Tile(unsigned char mine = 0);

    sf::Sprite bomb;
    sf::Sprite flag;
    sf::Sprite tile;
    sf::Sprite tileChecked;
    sf::Sprite neighborNumber;

    std::vector<Tile*> bombs;
    std::vector<Tile*> neighbors;

};
