//
// Created by Jake on 2/8/2022.
//

#ifndef SNAKEGAME_SNAKE_H
#define SNAKEGAME_SNAKE_H

#include "SFML/System.hpp"
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct SnakeSegment {
    SnakeSegment(int x, int y) : position(x,y){}
    sf::Vector2i position;
};

enum class Direction { None, Up, Down, Left, Right };

class Snake {
public:
    Snake(int l_blockSize);
    ~Snake();

    void setDirection(Direction l_dir) { m_dir = l_dir; }
    Direction getDirection();
    int getSpeed() const { return m_speed; }
    sf::Vector2i getPosition() { return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1,1)); }
    int getLives() const { return m_lives; }
    int getScore() const { return m_score; }
    void increaseScore() { m_score += 1; }
    bool hasLost() const { return m_lost; }

    void lose() { m_lost = true; }
    void toggleLost() { m_lost = !m_lost; }

    void extend(); // Grow snake
    void reset(); // Set snake to starting position

    void move();
    void tick();
    void cut(int l_segments); // Used to cut the snake
    void render(sf::RenderWindow& l_window);
private:
    void checkCollision();

    std::vector<SnakeSegment> m_snakeBody; // Stores the body of snake
    int m_size; // Size of the blocks
    Direction m_dir; // Current direction
    int m_speed;
    int m_lives;
    int m_score;
    bool m_lost;
    sf::RectangleShape m_bodyRect;
};

#endif //SNAKEGAME_SNAKE_H
