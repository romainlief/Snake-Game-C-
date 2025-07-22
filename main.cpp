#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "src/const.hpp"
#include "src/fruit.hpp"
#include "src/snake.hpp"

using namespace std;

int score = 0;

int choix_difficulte() {
  int choix;
  int diffi = 1;
  bool choixValide = false;
  while (!choixValide) {
    try {
      cout << "Choisissez la difficulté : " << endl;
      cout << "1. Normal" << endl;
      cout << "2. Multi Fruit" << endl;
      cout << "3. Hard core" << endl;
      cin >> choix;

      if (cin.fail()) {
        throw invalid_argument("Entrée invalide");
      }
      if (choix == 1) {
        diffi = 1;
        choixValide = true;
      } else if (choix == 2) {
        diffi = 2;
        choixValide = true;
      } else if (choix == 3) {
        diffi = 3;
        choixValide = true;
      } else {
        throw invalid_argument("Choix invalide");
      }
    } catch (const invalid_argument &e) {
      cin.clear(); // clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << e.what() << ", veuillez réessayer." << endl;
    }
  }
  return diffi;
}

void drawBackgroundGrid(sf::RenderWindow &window) {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
      rectangle.setPosition(i * tileSize, j * tileSize);
      rectangle.setFillColor(
          sf::Color(50, 50, 50)); // Gris foncé pour les cases
      window.draw(rectangle);
    }
  }
}

void dessiner_elem(sf::RenderWindow &window, Snake &snake,
                   std::vector<Fruit> &fruits, sf::Text &scoreText) {
  window.clear();
  drawBackgroundGrid(window); // Dessiner la grille de fond
  snake.draw(window);
  for (const auto &fruit : fruits) {
    fruit.draw(window);
  }
  window.draw(scoreText);
  window.display();
}

bool displayGameOverScreen(sf::RenderWindow &window, sf::Font &font,
                           int score) {
  window.clear();

  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("Game Over! Score: " + to_string(score));
  gameOverText.setCharacterSize(50);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 250, static_cast<float>(SCREENHEIGHT) / 2 - 100);

  sf::RectangleShape replayButton(sf::Vector2f(200, 50));
  replayButton.setFillColor(sf::Color::Blue);
  replayButton.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 90, static_cast<float>(SCREENHEIGHT) / 2 + 50);

  sf::Text replayText;
  replayText.setFont(font);
  replayText.setString("Rejouer");
  replayText.setCharacterSize(30);
  replayText.setFillColor(sf::Color::White);
  replayText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 60, static_cast<float>(SCREENHEIGHT) / 2 + 60);

  window.draw(gameOverText);
  window.draw(replayButton);
  window.draw(replayText);
  window.display();

  sf::Event event;
  while (true) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return false;
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (replayButton.getGlobalBounds().contains(mousePosition.x,
                                                    mousePosition.y)) {
          return true; // Rejouer
        }
      }
    }
  }
}

int main() {
  int diffi;
  diffi = choix_difficulte();

  sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT),
                          "Snake Game");

  sf::Font font;
  if (!font.loadFromFile("res/BungeeTint-Regular.ttf")) {
    cerr << "Erreur lors du chargement de la police" << endl;
    return -1;
  }

  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setStyle(sf::Text::Bold);
  scoreText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 50, 10);
  scoreText.setString("Score: 0");

  while (window.isOpen()) {
    score = 0;
    Snake snake(width / 2, height / 2);
    std::vector<Fruit> fruits;
    fruits.emplace_back();

    if (diffi == 2) {
      fruits.emplace_back(); // extra fruit diffi 2
    } else if (diffi == 3) {
      fruits.emplace_back(); // extra fruit diffi 3
      fruits.emplace_back(); // extra fruit diffi 3
    }

    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;

    if (diffi == 3) {
      delay = 0.06f;
    }

    scoreText.setString("Score: 0");

    bool gameRunning = true;
    while (window.isOpen() && gameRunning) {
      float time = clock.getElapsedTime().asSeconds();
      clock.restart();
      timer += time;

      sf::Event event{};
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.close();
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        snake.setDirection(Up);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        snake.setDirection(Down);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        snake.setDirection(Left);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        snake.setDirection(Right);

      if (timer > delay) {
        timer = 0;

        for (auto &fruit : fruits) {
          if (snake.getHeadPosition() == fruit.position) {
            score++;
            snake.move(true);
            fruit.respawn();
            scoreText.setString("Score: " + to_string(score));
          }
        }

        snake.move();

        if (snake.checkCollision() || snake.checkWallCollision()) {
          gameRunning = false;
        }
      }
      dessiner_elem(window, snake, fruits, scoreText);
    }
    if (!displayGameOverScreen(window, font, score)) {
      break;
    }
  }
  return 0;
}
