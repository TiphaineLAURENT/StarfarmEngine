//
// Created by Tiphaine LAURENT on 20/08/2019.
//

#include <SFML/Window/Event.hpp>

#include "Window.hpp"

namespace star
{
        Window::Window(unsigned int width,
                       unsigned int height,
                       const sf::String &title,
                       sf::Uint32 style,
                       unsigned int bitsPerPixel)
                : RenderWindow({ width, height, bitsPerPixel }, title, style), m_title(title)
        {}

        void Window::process_events()
        {
                auto event = sf::Event{};

                while (pollEvent(event))
                {
                        m_eventHandler.dispatch(event);
                }
        }

        WindowEventHandler &Window::get_event_handler() { return m_eventHandler; }

        const std::string &Window::get_title() const { return m_title; }

}    // namespace star
