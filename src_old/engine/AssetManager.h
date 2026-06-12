#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace RawEngine {
    class AssetManager{
    public :
        AssetManager(){};
        virtual ~AssetManager(){};

        void loadTexture(std::string name, std::string fileName);
        void loadAndSet(std::string name, std::string fileName, sf::Sprite& sprite);
        void loadFromSpriteSheet(sf::Sprite& sprite, std::string tName, int x, int y, int sizeX, int sizeY);
        sf::Texture& getTexture (std::string name);


    private:
        std::map<std::string,sf::Texture> _textures;
    };
}
