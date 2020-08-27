//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#ifndef STARFARM_GAME_HPP
#define STARFARM_GAME_HPP

#include <list>
#include <ostream>
#include <unordered_map>

#include <SFML/System/Clock.hpp>

#include "../Event/Signal.hpp"
#include "../Window/Window.hpp"
#include "Scene.hpp"
#include "util.hpp"

namespace star
{
        class Game
        {
                // ATTRIBUTES
            private:
                ::std::list<Scene> _scenes{};
                ::ecs::NonOwningPointer<Scene> _activeScene{ nullptr };

                ::std::unordered_map<::std::string, Window> _windows{};

                ::sf::Clock _clock{};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit Game() = default;
                ~Game() = default;
                Game(const Game &copy) = delete;
                Game(Game &&) = delete;

            public:    // OPERATORS
                Game &operator=(const Game &other) = delete;
                Game &operator=(Game &&) = delete;

            public:
                bool run();
                void quit();

                template <typename... ARGS> Scene &create_scene(ARGS... args)
                {
                        return _scenes.emplace_back(std::forward<ARGS>(args)...);
                }
                void set_active_scene(::ecs::NonOwningPointer<Scene> scene);

                Window &create_window(unsigned int width,
                                      unsigned int height,
                                      const ::std::string &title,
                                      ::sf::Uint32 style = ::sf::Style::Default,
                                      unsigned int bitsPerPixel = 32);

            private:
                bool _running{ true };

                SLOT(WindowEventHandler, OnKeyPressed) _onKeyPressed{};
                SLOT(WindowEventHandler, OnClosed) _onClosed{};
        };

        ::std::ostream &operator<<(::std::ostream &out, const Game &);

}    // namespace star

#endif    // STARFARM_GAME_HPP
