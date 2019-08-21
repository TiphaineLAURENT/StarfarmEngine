//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include "WindowEventHandler.hpp"


namespace star
{

  void WindowEventHandler::dispatch(const sf::Event &event)
  {
          switch (event.type) {
          case sf::Event::EventType::KeyPressed:
                  OnKeyPressed(event);
                  break;
          }
  }

}
