//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Game.hpp"

namespace star
{

  bool Game::run()
  {
          auto deltaTime = _clock.restart().asMicroseconds();

          if (!_activeScene)
                  return false;

          _activeScene->update(deltaTime);
          return true;
  }
  void Game::setActiveScene(Scene *scene)
  {
        _activeScene = scene;
  }

  Scene &Game::createScene()
  {
          _scenes.emplace_back();
          return _scenes.back();
  }

  Window &Game::createWindow(
          const sf::VideoMode &mode,
          const std::string &name,
          unsigned int style
  )
  {
          _windows.try_emplace(
                  name, mode, name, style
          ); // error C2512: 'star::Window::Window'ÿ: aucun constructeur par d‚faut appropri‚ disponible
          return _windows[name];
  }
}
