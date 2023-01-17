#include <fstream>
#include <sstream>
#include <iostream>
#include "Board.h"


Board::Board(int x, int y, int mines) {

    this->x = x;
    this->y = y;
    this->mines = mines;
    clickedBomb = false;
    win = false;
    debuggingmode = false;
    numFlagged = 0;
    numClicked = 0;
    counter.setTexture(TextureManager::GetTexture("digits"));
    happy.setTexture(TextureManager::GetTexture("face_happy"));
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test3.setTexture(TextureManager::GetTexture("test_3"));
    debug.setTexture(TextureManager::GetTexture("debug"));

    Reset(mines);

}
void Board::ReadBoard(std::string filename){

    happy.setTexture(TextureManager::GetTexture("face_happy"));
    tiles.clear();
    mineSpots.clear();
    numClicked = 0;
    numFlagged = 0;
    clickedBomb = false;
    win = false;
    mines = 0;

    std::vector<char> vals;
    std::ifstream in;
    in.open("../boards/" + filename + ".brd");

    char hold;
    std::string line;
    int count = 0;

    for(int c = 0; c < x*y; c++){

        Tile t(0);
        t.indy = c;
        tiles.push_back(t);

    }

    while(getline(in, line)) {

        std::istringstream stream(line, std::ios_base::binary);

        while(stream.read(&hold, 1)){

            if(hold == 49){

                vals.push_back(1);

            }
            if(hold == 48){

                vals.push_back(0);

            }
            /*
            Tile t(hold);
            t.indy = count;
            if(hold == 1){

                this->mineSpots.push_back(count);
                this->mines++;

            }

            count++;
            tiles.push_back(t);
            std::cout << t.isMine;
             */

        }

    }

    for(int c = 0; c < tiles.size(); c++){

        if(vals[c] == 1) {

            tiles[c].isMine = 1;
            mines++;
            mineSpots.push_back(c);

        }

    }

    int ok = mines;
    char okk = vals.at(0);
    bool okay = tiles[0].isMine;
    int okkk = mineSpots.size();
    FindMines();

}
void Board::DrawBoard(sf::RenderWindow* window) {

    for (int c = 0; c < tiles.size(); c++) {

        int dimx = c % x;
        int dimy = c / x;

        if(!tiles[c].isClicked) {

            tiles[c].tile.setPosition(dimx * 32, dimy * 32);
            (*window).draw(tiles[c].tile);

        } else{

            tiles[c].tileChecked.setPosition(dimx * 32, dimy * 32);
            (*window).draw(tiles[c].tileChecked);

        }


        if(tiles[c].isClicked && tiles[c].bombs.size() > 0) {

            tiles[c].neighborNumber.setPosition(dimx * 32, dimy * 32);
            (*window).draw(tiles[c].neighborNumber);

        }
        if(tiles[c].isFlagged){

            tiles[c].isClicked = 0;
            tiles[c].tile.setPosition(dimx * 32, dimy * 32);
            (*window).draw(tiles[c].tile);
            tiles[c].flag.setPosition(dimx*32, dimy*32);
            (*window).draw(tiles[c].flag);

        }
        if(debuggingmode){

            if(tiles[c].isMine){

                tiles[c].bomb.setPosition(dimx*32, dimy*32);
                (*window).draw(tiles[c].bomb);

            }

        }
        if(clickedBomb){

            if(tiles[c].isMine){

                tiles[c].bomb.setPosition(dimx*32, dimy*32);
                (*window).draw(tiles[c].bomb);

            }

        }

    }

}
void Board::Reset(int cfgMines) {

    tiles.clear();
    mines = cfgMines;
    mineSpots.clear();
    numClicked = 0;
    numFlagged = 0;
    clickedBomb = false;
    win = false;
    happy.setTexture(TextureManager::GetTexture("face_happy"));


    for(int c = 0; c < x*y; c++){

        Tile t(0);
        t.indy = c;
        tiles.push_back(t);

    }

    int okkaaaaay = Random::Int(0, x*y-1);
    mineSpots.push_back(okkaaaaay);
    tiles[okkaaaaay].isMine = 1;
    for(int c = 1; c < mines; c++){

        int val;
        bool check = true;

        while(check){

            check = false;
            val = Random::Int(0, x*y-1);

            for(int mineSpot : mineSpots){

                if(mineSpot == val){

                    check = true;
                    break;

                }

            }

        }
        mineSpots.push_back(val);
        tiles[val].isMine = 1;

    }

    /*
    for(int minespot : mineSpots){

        tiles[minespot].isMine = 1;

    }
     */

    FindMines();

}

void Board::RecursiveReveal(int index){

    if(tiles[index].recussed || !tiles[index].bombs.empty() || tiles[index].isMine || tiles[index].isFlagged){

        return;

    }
    for(int c = 0; c < tiles[index].neighbors.size(); c++){

        if(!tiles[index].isFlagged) {

            (*(tiles[index].neighbors[c])).isClicked = true;
            tiles[index].recussed = true;

        }
        RecursiveReveal(tiles[index].neighbors[c]->indy);

    }


}

void Board::FindMines(){

    int grid = x*y;
    int checkkekk = mineSpots.size();
    for(int c = 0; c < tiles.size(); c++){

        int linePos = c % x;
        if(linePos + 1 < x && c + 1 < grid){

            (tiles[c].neighbors).push_back(&(tiles[c + 1]));

        }
        if(linePos - 1 >= 0 && (c - 1 >= 0)){

            (tiles[c].neighbors).push_back(&(tiles[c - 1]));

        }
        if(linePos < x && (c + x) < grid ){

            (tiles[c].neighbors).push_back(&(tiles[c + x]));

        }
        if(linePos >= 0 && (c - x) >= 0){

            (tiles[c].neighbors).push_back(&(tiles[c - x]));

        }
        if((linePos + 1) < x && (c + x + 1) < grid){

            (tiles[c].neighbors).push_back(&(tiles[c + x + 1]));

        }
        if((linePos - 1) >= 0 && ((c + x - 1) < grid)){

            (tiles[c].neighbors).push_back(&(tiles[c + x - 1]));

        }
        if((linePos + 1) < x && (c - x + 1) >= 0){

            (tiles[c].neighbors).push_back(&(tiles[c - x + 1]));

        }
        if((linePos - 1) >= 0 && (c - x - 1) >= 0){

            (tiles[c].neighbors).push_back((&tiles[c - x - 1]));

        }

    }

    for(int c = 0; c < mineSpots.size(); c++){

        int num = mineSpots[c] % x;
        if(num + 1 < x && (mineSpots[c] + 1) < grid && !tiles[(mineSpots[c] + 1)].isMine){

            (tiles[mineSpots[c] + 1].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if(num - 1 >= 0 && (mineSpots[c] - 1) >= 0 && !tiles[(mineSpots[c] - 1)].isMine){

            (tiles[mineSpots[c] - 1].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if((mineSpots[c] + x < grid) && !tiles[(mineSpots[c] + x)].isMine){

            (tiles[mineSpots[c] + x].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if(((mineSpots[c] - x) >= 0) && !tiles[(mineSpots[c] - x)].isMine){

            (tiles[mineSpots[c] - x].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if (num + 1 < x && ((mineSpots[c] + x + 1) < grid && !tiles[(mineSpots[c] + x + 1)].isMine)) {

            (tiles[mineSpots[c] + x + 1].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if(num - 1 >= 0 && ((mineSpots[c] + x - 1) < grid) && !tiles[(mineSpots[c] + x -1)].isMine){

            (tiles[mineSpots[c] + x - 1].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if(num + 1 < x && ((mineSpots[c] - x + 1) >= 0) && !tiles[(mineSpots[c] - x + 1)].isMine){

            (tiles[mineSpots[c] - x + 1].bombs).push_back(&tiles[mineSpots[c]]);

        }
        if(num - 1 >= 0 && ((mineSpots[c] - x - 1) >= 0) && !tiles[(mineSpots[c] - x - 1)].isMine){

            (tiles[mineSpots[c] - x - 1].bombs).push_back(&tiles[mineSpots[c]]);

        }

    }


    for(int c = 0; c < tiles.size(); c++){

        if(!tiles[c].bombs.empty()){

            std::string neybs = "number_" + std::to_string(tiles[c].bombs.size());
            tiles[c].neighborNumber.setTexture(TextureManager::GetTexture(neybs));

        }

    }

}

void Board::DrawCounter(sf::RenderWindow* window) {

    int remaining = mines - numFlagged;
    if(numFlagged > mines) {

        counter.setTextureRect(sf::IntRect(210,0,21,32));
        counter.setPosition(32, y*32);
        (*window).draw(counter);

    }

    counter.setTextureRect(sf::IntRect((abs(remaining) / 100)*21,0,21,32));
    counter.setPosition(53, y*32);
    (*window).draw(counter);

    counter.setTextureRect(sf::IntRect(((abs(remaining) % 100) / 10)*21,0,21,32));
    counter.setPosition(74, y*32);
    (*window).draw(counter);

    counter.setTextureRect(sf::IntRect(((abs(remaining) % 100) % 10)*21,0,21,32));
    counter.setPosition(95, y*32);
    (*window).draw(counter);

}
void Board::DrawButtons(sf::RenderWindow *window) {

    happy.setPosition((x/2)*32, y*32);
    (*window).draw(happy);

    if(clickedBomb){

        happy.setTexture(TextureManager::GetTexture("face_lose"));
        happy.setPosition((x/2)*32, y*32);
        (*window).draw(happy);

    }

    test3.setPosition(((x - 2)*32), y*32);
    test2.setPosition(((x - 4)*32), y*32);
    test1.setPosition(((x - 6)*32), y*32);
    debug.setPosition(((x - 8)*32), y*32);

    (*window).draw(test1);
    (*window).draw(test2);
    (*window).draw(test3);
    (*window).draw(debug);

}
void Board::CalcNumClicked(){

    int count = 0;
    for(int c = 0; c < tiles.size(); c++){

        if(tiles[c].isClicked && !tiles[c].isFlagged){

            count++;

        }

    }

    numClicked = count;

}
void Board::Loser(){

    for(int mineSpot : mineSpots){

        tiles[mineSpot].tile.setTexture(TextureManager::GetTexture("tile_revealed"));

    }

}