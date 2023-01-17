#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
class TextureManager {

    //static means only one exists in memory at one time ever
    static std::unordered_map<std::string, sf::Texture> textures;
    static void LoadTexture(std::string textureName);// LoadTexture("tile")

public:

    static sf::Texture& GetTexture(std::string textureName); //Dont bother with LoadTexture because get texture loads ones that aren't yet loaded
    static void Clear(); //call this once, at the end of main()

};
