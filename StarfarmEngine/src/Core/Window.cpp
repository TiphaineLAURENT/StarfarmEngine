//
// Created by Tiphaine LAURENT on 20/08/2019.
//

#include <SFML/Window/Event.hpp>

#include "Window.hpp"


namespace star
{

  Window::Window(
          const sf::VideoMode &mode,
          const sf::String &title,
          sf::Uint32 style
  )
          : RenderWindow(mode, title, style)
  {
  }

  void Window::processEvents()
  {
          auto event = sf::Event{};

          while (pollEvent(event)) {
                  _eventHandler.dispatch(event);
          }
  }

}
