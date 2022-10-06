//
// Created by Jake on 2/14/2022.
//

#ifndef SNAKEGAME_TEXTBOX_H
#define SNAKEGAME_TEXTBOX_H


#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Textbox {
public:
    Textbox() { setup(5, 9, 200, sf::Vector2f(0, 0)); }
    Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) { setup(l_visible, l_charSize, l_width, l_screenPos); }
    ~Textbox() { clear(); }

    void setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
    void add(std::string l_message);
    void clear() { m_messages.clear(); }

    void render(sf::RenderWindow& l_window);
private:
    std::vector<std::string> m_messages;
    int m_numVisible;

    sf::RectangleShape m_backdrop;
    sf::Font m_font;
    sf::Text m_content;
};


#endif //SNAKEGAME_TEXTBOX_H
