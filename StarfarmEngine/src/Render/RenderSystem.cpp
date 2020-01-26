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

  void RenderSystem::update(::ecs::Interval deltaTime)
  {
          for (auto &render :
                  ecs::ComponentManager::get_component_container<RenderComponent>()) {
                  _window.draw(*render);
          }
  }

}
