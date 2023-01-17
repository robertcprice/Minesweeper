#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Board.h"
#include "Random.h"
#include "TextureManager.h"
/*
 * for the tiles that are clicked on going away up to a point if there are numerous holes is through recursion, like the linked list. Follow through
 * each pointer through each neighbor until you get to a point where it has to stop, for each and every neighor of every neighor
 */

void ReadConfig(std::string* x, std::string* y, std::string* mines){

    std::vector<std::string> vals;
    std::ifstream in;
    in.open("../boards/config.cfg", std::ios_base::binary);

    std::string line;
    std::string thing;

    std::getline(in, line);
    line = line.substr(0, line.length() - 1);
    *x = line;

    std::getline(in, line);
    line = line.substr(0, line.length() - 1);
    *y = line;

    std::getline(in, line);
    *mines = line;

}
int main() {

    std::string firstVal, secondVal, thirdVal;
    ReadConfig(&firstVal, &secondVal, &thirdVal);

    int cfgX = stoi(firstVal);
    int cfgY = stoi(secondVal);
    int cfgMines = stoi(thirdVal);

    int TILESIZE = 32;

    Board board(cfgX, cfgY, cfgMines);

    sf::RenderWindow window(sf::VideoMode(cfgX * 32, cfgY * 32 + 88), "Minesweeper: Bobby Edition");

    while (window.isOpen()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mouseX = mousePosition.x / TILESIZE; // snaps to tiles when clicking
        int mouseY = mousePosition.y / TILESIZE;
        int mouseTileSnap = mouseX + ((mouseY) * cfgX);
        sf::FloatRect smile = board.happy.getGlobalBounds();
        sf::FloatRect debugbox = board.debug.getGlobalBounds();
        sf::FloatRect test1box = board.test1.getGlobalBounds();
        sf::FloatRect test2box = board.test2.getGlobalBounds();
        sf::FloatRect test3box = board.test3.getGlobalBounds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                sf::FloatRect box = board.tiles[mouseTileSnap].tile.getGlobalBounds();

                if(!board.clickedBomb && !board.win) {

                    if (box.contains(mousePosition.x, mousePosition.y) && !board.tiles[mouseTileSnap].isFlagged) {

                        board.tiles[mouseTileSnap].isClicked = true;
                        if(board.tiles[mouseTileSnap].isMine){

                            board.clickedBomb = true;
                            board.Loser();

                        }

                        /*
                        std::string out;
                        if (board.tiles[mouseTileSnap].isMine)
                            out = "1";
                        else
                            out = "0";
                            */

                        board.RecursiveReveal(mouseTileSnap);
                        board.CalcNumClicked();
                        //std::cout << board.numClicked <<std::endl;
                        if(board.numClicked >= ((board.x*board.y) - board.mines)){

                            board.happy.setTexture(TextureManager::GetTexture("face_win"));
                            board.win = true;

                        }

                    }

                }

                if(smile.contains(mousePosition.x, mousePosition.y)){

                    board.Reset(cfgMines);

                }

                if(debugbox.contains(mousePosition.x, mousePosition.y)){

                    if(!board.debuggingmode) {

                        board.debuggingmode = true;

                    } else{

                        board.debuggingmode = false;

                    }


                }

                if(test1box.contains(mousePosition.x, mousePosition.y)){

                    //board.Reset();
                    board.ReadBoard("testboard1");

                }
                if(test2box.contains(mousePosition.x, mousePosition.y)){

                    //board.Reset();
                    board.ReadBoard("testboard2");

                }
                if(test3box.contains(mousePosition.x, mousePosition.y)){

                    //board.Reset();
                    board.ReadBoard("testboard3");

                }

            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {

                sf::FloatRect box = board.tiles[mouseTileSnap].tile.getGlobalBounds();

                if ((box.contains(mousePosition.x, mousePosition.y)) && ((board.tiles[mouseTileSnap].isClicked) == false)) {


                    if (board.tiles[mouseTileSnap].isFlagged) {

                        board.tiles[mouseTileSnap].isFlagged = false;
                        board.tiles[mouseTileSnap].recussed = false;
                        board.numFlagged -= 1;
                        continue;

                    } else {

                        board.tiles[mouseTileSnap].isFlagged = true;
                        board.tiles[mouseTileSnap].recussed = true;
                        board.numFlagged += 1;
                        continue;

                    }
                }

            }

        }

        window.clear();
        board.DrawBoard(&window);
        board.DrawCounter(&window);
        board.DrawButtons(&window);
        window.display();

    }

    TextureManager::Clear();
    return 0;

}