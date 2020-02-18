//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include <cassert>
#include "Game.hpp"

namespace star
{

  bool Game::run()
  {
          if (!_running) {
                  return false;
          }

          if (!_activeScene)
                  return false;

          auto deltaTime = _clock.restart().asMicroseconds();

          for (auto it = _windows.begin(); it != _windows.end();) {
                  if (!it->second.isOpen()) {
                          it = _windows.erase(it);
                  } else {
                          it++;
                  }
          }
          if (_windows.empty()) {
                  return false;
          }

          for (auto &[key, window] : _windows) {
                  window.process_events();
          }

          _activeScene->update(deltaTime);
          return true;
  }
  void Game::set_active_scene(::ecs::NonOwningPointer<Scene> scene)
  {
          ecs::replace_pointer(_activeScene, scene);
  }

  Scene &Game::create_scene()
  {
          return _scenes.emplace_back();
  }

  Window &Game::create_window(
          const sf::VideoMode &mode,
          const std::string &name,
          sf::Uint32 style
  )
  {
          const auto[iterator, emplaced] = _windows.try_emplace(
                  name, mode, name, style
          );
          assert(emplaced);
          auto &window = _windows[name];

          _onKeyPressed.connect(
                  window.get_event_handler().OnKeyPressed,
                  [=, &window] (const sf::Event &event)
                  {
                          if (event.key.code == ::sf::Keyboard::Escape)
                          {
                                  window.close();
                                  quit();
                          }
                  }
          );
          _onClosed.connect(
                  window.get_event_handler().OnClosed,
                  [=, &window](const sf::Event &event) {
                          window.close();

                          if (_windows.empty()) {
                                  quit();
                          }
                  }
          );

          return window;
  }

  void Game::quit()
  {
          _running = false;
  }

}
