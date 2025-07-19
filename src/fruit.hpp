#ifndef FRUIT_HPP
#define FRUIT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "const.hpp"


/**
 * @brief Structure representing a fruit in the game.
 * 
 */
struct Fruit {
    sf::Vector2i position;

    Fruit() {
        respawn();
    }

    void respawn() {
        position = sf::Vector2i(rand() % width, rand() % height);
    }

    void draw(sf::RenderWindow &window) const {
        sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
        rectangle.setPosition(position.x * tileSize, position.y * tileSize);
        rectangle.setFillColor(sf::Color::Red);
        window.draw(rectangle);
    }
};

#endif // FRUIT_HPP