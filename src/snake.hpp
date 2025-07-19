#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "const.hpp"
#include "direction.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>

using namespace std;

class Snake {
public:
  // #### Constructor####
  Snake(int x, int y);

  // #### Methods ####

  /**
   * @brief Move the snake in the current direction.
   *
   * @param hasEaten Indicates if the snake has eaten food.
   */
  void move(bool hasEaten = false);

  /**
   * @brief Check if the snake has collided with itself.
   *
   * @return true if there is a collision, false otherwise.
   */
  [[nodiscard]] bool checkCollision() const;

  /**
   * @brief Check if the snake has collided with the walls.
   *
   * @return true if there is a wall collision, false otherwise.
   */
  [[nodiscard]] bool checkWallCollision() const;

  /**
   * @brief Draw the snake on the given window.
   *
   * @param window The window to draw the snake on.
   */
  void draw(sf::RenderWindow &window) const;

  // #### Getters and Setters ####

  /**
   * @brief Get the position of the snake's head.
   *
   * @return The position of the snake's head.
   */
  [[nodiscard]] sf::Vector2i getHeadPosition() const;

  /**
   * @brief Set the direction of the snake.
   *
   * @param newDirection The new direction to set.
   */
  void setDirection(Direction newDirection);

  /**
   * @brief Get the current direction of the snake.
   *
   * @return The current direction.
   */
  [[nodiscard]] Direction getDirection() const;

private:
  // #### Attributes ####
  deque<sf::Vector2i> body;
  Direction direction;
};

#endif // SNAKE_HPP