//
// Created by Tiphaine LAURENT on 20/08/2019.
//

#ifndef STARFARMENGINE_WINDOW_HPP
#define STARFARMENGINE_WINDOW_HPP

#include <ostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "WindowEventHandler.hpp"

namespace star
{
        class Game;

        class Window : public sf::RenderWindow
        {
                // ATTRIBUTES
            public:
            private:
                // METHODS
            public:    // CONSTRUCTORS
                Window() = default;
                Window(unsigned int modeWidth,
                       unsigned int modeHeight,
                       const ::sf::String &title,
                       ::sf::Uint32 style = ::sf::Style::Default,
                       unsigned int modeBitsPerPixel = 32);
                ~Window() override = default;
                Window(const Window &copy) = delete;
                Window(Window &&) = delete;

            public:    // OPERATORS
                Window &operator=(const Window &other) = delete;
                Window &operator=(Window &&) noexcept = delete;

            public:
                void process_events();
                WindowEventHandler &get_event_handler();

                const std::string &get_title() const;

            private:
                WindowEventHandler m_eventHandler{};

                std::string m_title{};
        };

        std::ostream &operator<<(std::ostream &out, const Window &);

}    // namespace star

#endif    // STARFARMENGINE_WINDOW_HPP
