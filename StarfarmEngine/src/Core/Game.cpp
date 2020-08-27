//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Game.hpp"
#include <cassert>

namespace star
{
        bool Game::run()
        {
                if (!_running)
                {
                        return false;
                }

                if (!_activeScene)
                        return false;

                auto deltaTime = _clock.restart().asSeconds();

                for (auto it = _windows.begin(); it != _windows.end();)
                {
                        if (!it->second.isOpen())
                        {
                                it = _windows.erase(it);
                        }
                        else
                        {
                                it++;
                        }
                }
                if (_windows.empty())
                {
                        return false;
                }

                for (auto &[key, window] : _windows)
                {
                        window.process_events();
                }

                _activeScene->update(deltaTime);
                return true;
        }
        void Game::set_active_scene(::ecs::NonOwningPointer<Scene> scene)
        {
                ecs::replace_pointer(_activeScene, scene);
        }

        Window &Game::create_window(unsigned int width,
                                    unsigned int height,
                                    const ::std::string &title,
                                    ::sf::Uint32 style,
                                    unsigned int bitsPerPixel)
        {
                const auto [iterator, emplaced] = _windows.try_emplace(
                        title, width, height, title, style, bitsPerPixel);
                auto &window = iterator->second;

                _onKeyPressed.connect(window.get_event_handler().OnKeyPressed,
                                      [=, &window](const ::sf::Event &event) {
                                              if (event.key.code == ::sf::Keyboard::Escape)
                                              {
                                                      window.close();
                                                      quit();
                                              }
                                      });
                _onClosed.connect(window.get_event_handler().OnClosed,
                                  [=, &window](const ::sf::Event &event) {
                                          window.close();

                                          if (_windows.empty())
                                          {
                                                  quit();
                                          }
                                  });

                return window;
        }

        void Game::quit() { _running = false; }

}    // namespace star
