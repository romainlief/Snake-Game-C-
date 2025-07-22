#include "window.hpp"
#include "const.hpp"

Window::Window() {
    window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Ping Pong Game");
    window.setFramerateLimit(60);
}

Window::~Window() {
    window.close();
}

sf::RenderWindow &Window::getRenderWindow() {
    return window;
}
