//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include "WindowEventHandler.hpp"


namespace star
{

  void WindowEventHandler::dispatch(const sf::Event &event)
  {
          switch (event.type) {
          case sf::Event::Closed:
                  OnClosed(event);
                  break;
          case sf::Event::Resized:
                  OnResized(event);
                  break;
          case sf::Event::LostFocus:
                  OnLostFocus(event);
                  break;
          case sf::Event::GainedFocus:
                  OnGainedFocus(event);
                  break;
          case sf::Event::TextEntered:
                  OnTextEntered(event);
                  break;
          case sf::Event::EventType::KeyPressed:
                  OnKeyPressed(event);
                  break;
          case sf::Event::KeyReleased:
                  OnKeyReleased(event);
                  break;
          case sf::Event::MouseWheelScrolled:
                  OnMouseWheelScrolled(event);
                  break;
          case sf::Event::MouseButtonPressed:
                  OnMouseButtonPressed(event);
                  break;
          case sf::Event::MouseButtonReleased:
                  OnMouseButtonReleased(event);
                  break;
          case sf::Event::MouseMoved:
                  OnMouseMoved(event);
                  break;
          case sf::Event::MouseEntered:
                  OnMouseEntered(event);
                  break;
          case sf::Event::MouseLeft:
                  OnMouseLeft(event);
                  break;
          case sf::Event::Count:
                  break;
          default:
                  break;
          }
  }

}
