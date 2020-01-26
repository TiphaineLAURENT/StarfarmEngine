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
          : RenderWindow(mode, title, style), _name(title)
  {
  }

  void Window::process_events()
  {
          auto event = sf::Event{};

          while (pollEvent(event)) {
                  _eventHandler.dispatch(event);
          }
  }

  WindowEventHandler &Window::get_event_handler()
  {
          return _eventHandler;
  }

  const std::string &Window::get_name() const
  {
          return _name;
  }

}
