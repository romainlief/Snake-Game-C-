#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window {
public:
  // #### Constructor and Destructor ####

  /**
   * @brief Construct a new Window object
   *
   */
  Window();

  /**
   * @brief Destroy the Window object
   *
   */
  ~Window();

  // #### Methods ####

  /**
   * @brief Get the Render Window object
   *
   * @return sf::RenderWindow&
   */
  sf::RenderWindow &getRenderWindow();

private:
  // #### Attributes ####

  sf::RenderWindow window;
};

#endif // WINDOW_HPP