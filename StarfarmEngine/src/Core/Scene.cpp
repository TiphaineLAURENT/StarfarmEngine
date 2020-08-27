//
// Created by Tiphaine LAURENT on 05/08/2019.
//

#include <string>

#include "Scene.hpp"
#include "../Log/LogSystem.hpp"

namespace star
{

        Scene::Scene(const Vector<2> &gravity)
        {
            cpSpaceSetGravity(m_world.get(), gravity);
        }

        void Scene::update(::ecs::Interval deltaTime)
        {
                LogSystem::log("Update after " + std::to_string(deltaTime) + " seconds");
                m_systems.update(deltaTime);
        }

        void Scene::refresh()
        {
                m_systems.update_systems_order();
        }

        cpSpace &Scene::get_world()
        {
                return *m_world;
        }

}
