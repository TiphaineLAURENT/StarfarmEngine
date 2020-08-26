//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include "RenderSystem.hpp"
#include "RenderComponent.hpp"
#include <ComponentManager.hpp>

namespace star
{
        RenderSystem::RenderSystem(Window &window)
                : System(ecs::SYSTEM_PRIORITY::NORMAL, 0.001), _window(window)
        {}

        void RenderSystem::update(::ecs::Interval deltaTime)
        {
                for (auto &render :
                     ecs::ComponentManager::get_component_container<RenderComponent>())
                {
                        _window.draw(*render);
                }
        }

}    // namespace star
