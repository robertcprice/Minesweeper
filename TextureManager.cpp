#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string textureName) {

    std::string path = "../images/";
    path += textureName + ".png";

    textures[textureName].loadFromFile(path);
    //fileName == space
    //path == images/space.png
}
sf::Texture& TextureManager::GetTexture(std::string textureName) {

    if(textures.find(textureName) == textures.end()){

        LoadTexture(textureName);

    }
    return textures[textureName];

}

void TextureManager::Clear(){

    textures.clear();

}