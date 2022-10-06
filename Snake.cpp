//
// Created by Jake on 2/8/2022.
//

#include "Snake.h"

Snake::Snake(int l_blockSize) {
    m_size = l_blockSize;
    m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    reset();
}

Snake::~Snake() {}

void Snake::reset() {
    m_snakeBody.clear();

    // Add 3 body segments to start
    m_snakeBody.emplace_back(5,7);
    m_snakeBody.emplace_back(5,6);
    m_snakeBody.emplace_back(5,5);

    setDirection(Direction::None);
    m_speed = 15;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
}

void Snake::extend() {
    if (m_snakeBody.empty()) { return; }
    SnakeSegment& head = m_snakeBody[m_snakeBody.size() - 1];
    SnakeSegment& tail = m_snakeBody[m_snakeBody.size() - 1];

    if (m_snakeBody.size() > 1) {
        tail = m_snakeBody[m_snakeBody.size() - 2];

        if (head.position.x == tail.position.x) {
            if (head.position.y > tail.position.y) {
                m_snakeBody.emplace_back(head.position.x, head.position.y + 1);
            } else {
                m_snakeBody.emplace_back(head.position.x, head.position.y - 1);
            }
        } else if (head.position.y == tail.position.y) {
            if (head.position.x > tail.position.x) {
                m_snakeBody.emplace_back(head.position.x + 1, head.position.y);
            } else {
                m_snakeBody.emplace_back(head.position.x - 1, head.position.y);
            }
        }
    } else {
        if (m_dir == Direction::Up) {
            m_snakeBody.emplace_back(head.position.x, head.position.y + 1);
        } else if (m_dir == Direction::Down) {
            m_snakeBody.emplace_back(head.position.x, head.position.y - 1);
        } else if (m_dir == Direction::Left) {
            m_snakeBody.emplace_back(head.position.x + 1, head.position.y);
        } else if (m_dir == Direction::Right) {
            m_snakeBody.emplace_back(head.position.x - 1, head.position.y);
        }
    }
}

void Snake::tick() {
    if (m_snakeBody.empty()) { return; }
    if (m_dir == Direction::None) { return; }
    move();
    checkCollision();
}

void Snake::move() {
    for (int i = m_snakeBody.size() - 1; i > 0; --i) {
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }
    if (m_dir == Direction::Left) {
        --m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Right) {
        ++m_snakeBody[0].position.x;
    } else if (m_dir == Direction::Up) {
        --m_snakeBody[0].position.y;
    } else if (m_dir == Direction::Down) {
        ++m_snakeBody[0].position.y;
    }
}

void Snake::checkCollision() {
    if (m_snakeBody.size() <= 5) { return; }
    SnakeSegment& head = m_snakeBody.front();
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
        if (itr->position == head.position) {
            int segments = m_snakeBody.end() - itr;
            cut(segments);
            return;
        }
    }
}

void Snake::cut(int l_segments) {
    for (int i = 0; i < l_segments; ++i) {
        m_snakeBody.pop_back();
    }
    --m_lives;
    if (!m_lives) {
        lose();
        return;
    }
}

void Snake::render(sf::RenderWindow &l_window) {
    if (m_snakeBody.empty()) { return; }

    auto head = m_snakeBody.begin();
    m_bodyRect.setFillColor(sf::Color::Yellow);
    m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
    l_window.draw(m_bodyRect);

    m_bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
        m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
        l_window.draw(m_bodyRect);
    }
}

Direction Snake::getDirection() {
    if (m_snakeBody.size() <= 1) {
        return Direction::None;
    }

    SnakeSegment& head = m_snakeBody[0];
    SnakeSegment& neck = m_snakeBody[1];

    if (head.position.x == neck.position.x) {
        return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
    } else if (head.position.y == neck.position.y) {
        return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
    }

    return Direction::None;
}

