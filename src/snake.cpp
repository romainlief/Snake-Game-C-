#include "snake.hpp"

Snake::Snake(int x, int y) {
  body.emplace_back(x, y);
  direction = Right;
}

void Snake::move(bool hasEaten) {
  sf::Vector2i head = body.front();
  switch (direction) {
  case Up:
    head.y -= 1;
    break;
  case Down:
    head.y += 1;
    break;
  case Left:
    head.x -= 1;
    break;
  case Right:
    head.x += 1;
    break;
  }
  body.push_front(head);

  if (!hasEaten) {
    body.pop_back();
  }
}

bool Snake::checkCollision() const {
  sf::Vector2i head = body.front();
  for (int i = 1; i < body.size(); ++i) {
    if (head == body[i])
      return true;
  }
  return false;
}

bool Snake::checkWallCollision() const {
  sf::Vector2i head = body.front();
  return (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height);
}

void Snake::setDirection(Direction dir) {
  if ((dir == Up && direction != Down) || (dir == Down && direction != Up) ||
      (dir == Left && direction != Right) ||
      (dir == Right && direction != Left)) {
    direction = dir;
  }
}

void Snake::draw(sf::RenderWindow &window) const {
  for (auto segment : body) {
    sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
    rectangle.setPosition(segment.x * tileSize, segment.y * tileSize);
    rectangle.setFillColor(sf::Color::Green);
    window.draw(rectangle);
  }
}

sf::Vector2i Snake::getHeadPosition() const { return body.front(); }
