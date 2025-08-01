#ifndef GAME_HPP
#define GAME_HPP

#include "fruit.hpp"
#include "snake.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <string>
#include <thread>

using namespace std;

class Game {
public:
  // #### Constructor and Destructor ####

  /**
   * @brief Construct a new Game object
   *
   */

  Game(unsigned short int dif);

  // #### Methods ####

  /**
   * @brief Run the game
   *
   */
  void run();

private:
  // #### Attributs ####
  unsigned short int dif;
  unsigned int score;

  sf::Font font;
  sf::Text scoreText;

  Window window;

  Snake snake;

  vector<Fruit> fruits;

  void drawBackgroundGrid();

  void drawElem();

  bool displayGameOverScreen();
};

#endif // GAME_HPP