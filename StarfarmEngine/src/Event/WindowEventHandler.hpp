//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#ifndef STARFARMENGINE_WINDOWEVENTHANDLER_HPP
#define STARFARMENGINE_WINDOWEVENTHANDLER_HPP

# include <ostream>
# include <SFML/Window/Event.hpp>

# include "Signal.hpp"


namespace star
{

  class WindowEventHandler
  {
// ATTRIBUTES
  public:
  private:

// METHODS
  public:// CONSTRUCTORS
          WindowEventHandler() = default;
          ~WindowEventHandler() = default;
          WindowEventHandler(const WindowEventHandler &copy) = default;
          WindowEventHandler(WindowEventHandler &&) noexcept = default;

  public: //OPERATORS
          WindowEventHandler &operator=(const WindowEventHandler &other) = default;
          WindowEventHandler &operator=(WindowEventHandler &&) noexcept = default;

  public:
          void dispatch(const sf::Event &event);

          SIGNAL(OnKeyPressed, const sf::Event&);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const WindowEventHandler &);

}

#endif //STARFARMENGINE_WINDOWEVENTHANDLER_HPP
