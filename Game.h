//
// Created by Jake on 2/5/2022.
//
#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

class Game {

public:
    Game();
    ~Game();

    void handleInput();
    void update();
    void render();
    Window* getWindow() { return &m_window; }

    sf::Time getElapsed() { return m_elapsed; }
    void restartClock() { m_elapsed += m_clock.restart(); }

private:
    Window m_window;

    sf::Clock m_clock;
    sf::Time m_elapsed;

    World m_world;
    Snake m_snake;

    Textbox m_textbox;
};


#endif //MAIN_CPP_GAME_H
