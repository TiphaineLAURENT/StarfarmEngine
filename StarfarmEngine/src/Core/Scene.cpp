//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include <string>

#include "Scene.hpp"
#include "../Log/LogSystem.hpp"

namespace star
{

  void Scene::update(long deltaTime)
  {
          LogSystem::log("Update after " + std::to_string(deltaTime) + " micros\n");
          _systems.update(deltaTime);
  }

  void Scene::refresh()
  {
          _systems.updateSytemsOrder();
  }

}
