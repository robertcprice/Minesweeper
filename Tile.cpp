#include "Tile.h"

Tile::Tile(unsigned char mine) {

    isMine = mine;
    isFlagged = false;
    recussed = false;
    isClicked = false;
    tile.setTexture(TextureManager::GetTexture("tile_hidden"));
    tileChecked.setTexture(TextureManager::GetTexture("tile_revealed"));
    bomb.setTexture(TextureManager::GetTexture("mine"));
    flag.setTexture(TextureManager::GetTexture("flag"));

}
