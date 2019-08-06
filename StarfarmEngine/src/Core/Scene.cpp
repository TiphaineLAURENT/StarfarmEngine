//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include "Scene.hpp"

namespace star
{

  void Scene::update(float deltaTime)
  {
          _systems.update(deltaTime);
  }
  template <class E, class... ARGS>
  E &Scene::createEntity(ARGS &&... args)
  {
          return _entities.createEntity<E>(std::forward<ARGS>(args)...);
  }

  template <class S, class... ARGS>
  S &Scene::createSystem(ARGS &&... args)
  {
          return _systems.createSystem<S>(std::forward<ARGS>(args)...);
  }

}
