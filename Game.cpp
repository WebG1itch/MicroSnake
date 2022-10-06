//
// Created by Jake on 2/5/2022.
//

#include "Game.h"

Game::Game(): m_window("Testing Chamber Constructed", sf::Vector2u(150, 100)), m_snake(m_world.getBlockSize()), m_world(sf::Vector2u(150, 100)) {
    // Set up members
    m_textbox.setup(5, 1, 150, sf::Vector2f(255, 0));
    m_textbox.add("Seeded random number generator with: " + std::to_string(time(nullptr)));
}

Game::~Game() {}

void Game::update() {
    float timeStep = 1.0f / m_snake.getSpeed();

    if (m_elapsed.asSeconds() >= timeStep) {
        m_snake.tick();
        m_world.update(m_snake);
        m_elapsed -= sf::seconds(timeStep);
        if(m_snake.hasLost()) {
            m_snake.reset();
        }
    }
    m_window.update(); // Update the window
}

void Game::render() {
    m_window.beginDraw(); // To clear the screen
    m_world.render(*m_window.getRenderWindow());
    m_snake.render(*m_window.getRenderWindow());
    m_textbox.render(*m_window.getRenderWindow());
    m_window.endDraw(); // Send to display
}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.getDirection() != Direction::Down) {
        m_snake.setDirection(Direction::Up);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.getDirection() != Direction::Up) {
        m_snake.setDirection(Direction::Down);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.getDirection() != Direction::Left) {
        m_snake.setDirection(Direction::Right);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.getDirection() != Direction::Right) {
        m_snake.setDirection(Direction::Left);
    }
}
