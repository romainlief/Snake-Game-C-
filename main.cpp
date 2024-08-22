#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept>

using namespace std;
const int windowWidth = 1200;
const int windowHeight = 800;
const int tileSize = 35;
const int width = windowWidth / tileSize;
const int height = windowHeight / tileSize;
auto score = 0;
int diffi = 1;

enum Direction { Up, Down, Left, Right };

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

class Snake {
private:
    deque<sf::Vector2i> body;
    Direction direction;

public:
    Snake(int x, int y) {
        body.emplace_back(x, y);
        direction = Right;
    }

    void move(bool hasEaten = false) {
        sf::Vector2i head = body.front();
        switch (direction) {
            case Up: head.y -= 1; break;
            case Down: head.y += 1; break;
            case Left: head.x -= 1; break;
            case Right: head.x += 1; break;
        }
        body.push_front(head);

        if (!hasEaten) {
            body.pop_back();
        }
    }

    [[nodiscard]] bool checkCollision() const {
        sf::Vector2i head = body.front();
        for (int i = 1; i < body.size(); ++i) {
            if (head == body[i])
                return true;
        }
        return false;
    }

    [[nodiscard]] bool checkWallCollision() const {
        sf::Vector2i head = body.front();
        return (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height);
    }

    void setDirection(Direction dir) {
        if ((dir == Up && direction != Down) ||
            (dir == Down && direction != Up) ||
            (dir == Left && direction != Right) ||
            (dir == Right && direction != Left)) {
            direction = dir;
        }
    }

    void draw(sf::RenderWindow &window) const {
        for (auto segment : body) {
            sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
            rectangle.setPosition(segment.x * tileSize, segment.y * tileSize);
            rectangle.setFillColor(sf::Color::Green);
            window.draw(rectangle);
        }
    }

    [[nodiscard]] sf::Vector2i getHeadPosition() const {
        return body.front();
    }
};

void choix_difficulte() {
    int choix;
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
}


//void dessiner_elem1_2(sf::RenderWindow &window, Snake &snake, std::vector<Fruit> &fruits, sf::Text &scoreText) {
  //  window.clear();
    //snake.draw(window);
    //for (const auto &fruit : fruits) {
      //  fruit.draw(window);
    //}
    //window.draw(scoreText);
    //window.display();
//}

void drawBackgroundGrid(sf::RenderWindow &window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::RectangleShape rectangle(sf::Vector2f(tileSize - 1, tileSize - 1));
            rectangle.setPosition(i * tileSize, j * tileSize);
            rectangle.setFillColor(sf::Color(50, 50, 50)); // Gris foncé pour les cases
            window.draw(rectangle);
        }
    }
}

void dessiner_elem(sf::RenderWindow &window, Snake &snake, std::vector<Fruit> &fruits, sf::Text &scoreText) {
    window.clear();
    drawBackgroundGrid(window); // Dessiner la grille de fond
    snake.draw(window);
    for (const auto &fruit : fruits) {
        fruit.draw(window);
    }
    window.draw(scoreText);
    window.display();
}

bool displayGameOverScreen(sf::RenderWindow &window, sf::Font &font, int score) {
    window.clear();

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over! Score: " + to_string(score));
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(windowWidth / 2 - 250, windowHeight / 2 - 100);

    sf::RectangleShape replayButton(sf::Vector2f(200, 50));
    replayButton.setFillColor(sf::Color::Blue);
    replayButton.setPosition(windowWidth / 2 - 90, windowHeight / 2 + 50);

    sf::Text replayText;
    replayText.setFont(font);
    replayText.setString("Rejouer");
    replayText.setCharacterSize(30);
    replayText.setFillColor(sf::Color::White);
    replayText.setPosition(windowWidth / 2 - 60, windowHeight / 2 + 60);

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
                if (replayButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    return true; // Rejouer
                }
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake Game");

    choix_difficulte();

    sf::Font font;
    if (!font.loadFromFile("/Users/romainliefferinckx/CLionProjects/GameTestC++/BungeeTint-Regular.ttf")) {
        cerr << "Erreur lors du chargement de la police" << endl;
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(windowWidth / 2 - 50, 10);
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.setDirection(Up);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.setDirection(Down);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.setDirection(Left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.setDirection(Right);

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
