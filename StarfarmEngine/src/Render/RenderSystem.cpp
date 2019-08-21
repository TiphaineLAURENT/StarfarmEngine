//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>
#include "RenderSystem.hpp"
#include "RenderComponent.hpp"


namespace star
{

  RenderSystem::RenderSystem(Window &window)
          : System(), _window(window)
  {
  }

  void RenderSystem::update(long deltaTime)
  {
          for (auto &render :
                  ecs::ComponentManager::getComponentContainer<RenderComponent>()) {
                  _window.draw(*render);
          }
  }

}
