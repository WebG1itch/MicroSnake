//
// Created by Jake on 2/10/2022.
//

#ifndef SNAKEGAME_WORLD_H
#define SNAKEGAME_WORLD_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Snake;

class World {
public:
    World(sf::Vector2u l_windowSize);
    ~World();

    int getBlockSize() const { return m_blockSize; }

    void respawnApple();

    void update(Snake& l_player);
    void render(sf::RenderWindow& l_window);

private:
    sf::Vector2u m_windowSize;
    sf::Vector2i m_item;
    int m_blockSize;

    sf::CircleShape m_appleShape;
    sf::RectangleShape m_bounds[4];

};


#endif //SNAKEGAME_WORLD_H
