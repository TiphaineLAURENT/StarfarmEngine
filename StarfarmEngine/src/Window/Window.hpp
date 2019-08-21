//
// Created by Tiphaine LAURENT on 20/08/2019.
//

#ifndef STARFARMENGINE_WINDOW_HPP
#define STARFARMENGINE_WINDOW_HPP

# include <ostream>
# include <SFML/Graphics/RenderWindow.hpp>

# include "WindowEventHandler.hpp"


namespace star
{
  class Game;

  class Window
          : public sf::RenderWindow
  {
// ATTRIBUTES
  public:
  private:

// METHODS
  public:// CONSTRUCTORS
          Window() = default;
          Window(
                  const sf::VideoMode &mode,
                  const sf::String &title,
                  sf::Uint32 style
          );
          ~Window() override = default;
          Window(const Window &copy) = delete;
          Window(Window &&) = delete;

  public: //OPERATORS
          Window &operator=(const Window &other) = delete;
          Window &operator=(Window &&) noexcept = delete;

  public:
          void processEvents();
          WindowEventHandler &getEventHandler();

          const std::string &getName() const;

  private:
          WindowEventHandler _eventHandler;

          std::string _name;
  };

  std::ostream &operator<<(std::ostream &out, const Window &);

}

#endif //STARFARMENGINE_WINDOW_HPP
