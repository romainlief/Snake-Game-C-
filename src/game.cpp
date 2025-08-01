#include "game.hpp"
#include "const.hpp"

Game::Game(unsigned short int dif)
    : dif(dif), snake(SNAKEPOSX, SNAKEPOSY), window(), score(0) {
  if (!font.loadFromFile("res/BungeeTint-Regular.ttf")) {
    cerr << "Erreur de chargement de la police" << endl;
  }

  scoreText.setFont(font);
  scoreText.setCharacterSize(TEXTSIZE);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setStyle(sf::Text::Bold);
  scoreText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 50, 10);
  scoreText.setString("Score: 0");
}

void Game::run() {
  while (window.getRenderWindow().isOpen()) {
    score = 0;
    snake = Snake(SNAKEPOSX, SNAKEPOSY); // Réinitialiser le snake membre
    fruits.clear();                      // Vider le vecteur de fruits
    fruits.emplace_back();

    if (dif == 2) {
      fruits.emplace_back(); // extra fruit dif 2
    } else if (dif == 3) {   // faire une boucle pour emplace
      for (int i = 0; i < (dif - 1); i++) {
        fruits.emplace_back(); // extra fruit dif 3
      }
    }

    sf::Clock clock;
    float timer = 0.0f, delay = 0.1f;

    if (dif == 3) {
      delay = 0.06f;
    }

    scoreText.setString("Score: 0");

    bool gameRunning = true;
    while (window.getRenderWindow().isOpen() && gameRunning) {
      float time = clock.getElapsedTime().asSeconds();
      clock.restart();
      timer += time;

      sf::Event event{};
      while (window.getRenderWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window.getRenderWindow().close();
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
      drawElem();
    }
    if (!displayGameOverScreen()) {
      break;
    }
  }
}

void Game::drawBackgroundGrid() {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
      rectangle.setPosition(i * tileSize, j * tileSize);
      rectangle.setFillColor(
          sf::Color(50, 50, 50)); // Gris foncé pour les cases
      window.getRenderWindow().draw(rectangle);
    }
  }
}

void Game::drawElem() {
  window.getRenderWindow().clear();
  drawBackgroundGrid(); // Dessiner la grille de fond
  snake.draw(window.getRenderWindow());
  for (const auto &fruit : fruits) {
    fruit.draw(window.getRenderWindow());
  }
  window.getRenderWindow().draw(scoreText);
  window.getRenderWindow().display();
}

bool Game::displayGameOverScreen() {
  window.getRenderWindow().clear();

  sf::Text gameOverText;
  gameOverText.setFont(font);
  gameOverText.setString("Game Over! Score: " + to_string(score));
  gameOverText.setCharacterSize(50);
  gameOverText.setFillColor(sf::Color::White);
  gameOverText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 250,
                           static_cast<float>(SCREENHEIGHT) / 2 - 100);

  sf::RectangleShape replayButton(sf::Vector2f(200, 50));
  replayButton.setFillColor(sf::Color::Blue);
  replayButton.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 90,
                           static_cast<float>(SCREENHEIGHT) / 2 + 50);

  sf::Text replayText;
  replayText.setFont(font);
  replayText.setString("Rejouer");
  replayText.setCharacterSize(TEXTSIZE);
  replayText.setFillColor(sf::Color::White);
  replayText.setPosition(static_cast<float>(SCREENWIDTH) / 2 - 60,
                         static_cast<float>(SCREENHEIGHT) / 2 + 60);

  window.getRenderWindow().draw(gameOverText);
  window.getRenderWindow().draw(replayButton);
  window.getRenderWindow().draw(replayText);
  window.getRenderWindow().display();

  sf::Event event;
  while (true) {
    while (window.getRenderWindow().pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.getRenderWindow().close();
        return false;
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition =
            sf::Mouse::getPosition(window.getRenderWindow());
        if (replayButton.getGlobalBounds().contains(mousePosition.x,
                                                    mousePosition.y)) {
          return true; // Rejouer
        }
      }
    }
  }
}
