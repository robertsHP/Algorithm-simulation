#include "AssetManager.h"

namespace RawEngine {

    void AssetManager::loadTexture(std::string name, std::string fileName)
    {
        sf::Texture tex;

        auto exists = this->_textures.find(name);
        if(tex.loadFromFile(fileName))
            if(exists == this->_textures.end())
                this->_textures[name] = tex;
    }
    void AssetManager::loadAndSet(std::string name, std::string fileName, sf::Sprite& sprite)
    {
        sf::Texture tex;

        auto exists = this->_textures.find(name);
        if(tex.loadFromFile(fileName)){
            if(exists == this->_textures.end()){
                this->_textures[name] = tex;
            }
            sprite.setTexture(this->_textures[name]);
        }
    }
    void AssetManager::loadFromSpriteSheet(sf::Sprite& sprite, std::string tName, int x, int y, int sizeX, int sizeY)
    {
        sf::Texture& tex = getTexture(tName);
        sprite.setTexture(tex);
        sprite.setTextureRect(sf::IntRect(x * sizeX,y * sizeY, sizeX, sizeY));
    }

    sf::Texture& AssetManager::getTexture(std::string name)
    {
        return this->_textures.at(name);
    }
}
