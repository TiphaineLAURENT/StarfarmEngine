//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Game.hpp"

namespace star
{
        bool Game::run()
        {
                if (!m_running)
                {
                        return false;
                }

                if (!m_activeScene)
                        return false;

                const auto nextTick = m_clock.now();
                const std::chrono::duration<float> deltaTime = nextTick - m_lastTick;
                m_lastTick = nextTick;

                for (auto it = m_windows.begin(); it != m_windows.end();)
                {
                        if (!it->second.isOpen())
                        {
                                it = m_windows.erase(it);
                        }
                        else
                        {
                                it++;
                        }
                }
                if (m_windows.empty())
                {
                        return false;
                }

                for (auto &[key, window] : m_windows)
                {
                        window.process_events();
                }

                m_activeScene->update(deltaTime.count());
                return true;
        }
        void Game::set_active_scene(::ecs::NonOwningPointer<Scene> scene)
        {
                ecs::replace_pointer(m_activeScene, scene);
        }

        Window &Game::create_window(unsigned int width,
                                    unsigned int height,
                                    const ::std::string &title,
                                    ::sf::Uint32 style,
                                    unsigned int bitsPerPixel)
        {
                const auto [iterator, emplaced] = m_windows.try_emplace(
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

                                          if (m_windows.empty())
                                          {
                                                  quit();
                                          }
                                  });

                return window;
        }

        void Game::quit() { m_running = false; }

}    // namespace star
