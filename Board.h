#pragma once
#include <vector>
#include "Tile.h"
#include "Random.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Board {

public:

    Board(int x = 0, int y = 0, int mines = 0);

    void ReadBoard(std::string filename);
    void DrawBoard(sf::RenderWindow* window);
    void FindMines();
    void CalcNumClicked();
    void RecursiveReveal(int index);
    void Reset(int cfgMines);
    void Loser();

    bool clickedBomb;
    bool win;
    bool debuggingmode;

    sf::Sprite counter;
    sf::Sprite test1, test2, test3;
    sf::Sprite happy;
    sf::Sprite debug;

    void DrawCounter(sf::RenderWindow* window);
    void DrawButtons(sf::RenderWindow* window);

    std::vector<Tile> tiles;
    //std::vector<std::vector<Tile>> tiles;
    std::vector<int> mineSpots;
    int x, y, mines, numFlagged, numClicked;

private:

};

