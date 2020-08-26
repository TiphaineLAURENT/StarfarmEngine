//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>

#include "../Log/LogSystem.hpp"
#include "PhysicSystem.hpp"
#include "RigidbodyComponent.hpp"

namespace star
{
        PhysicSystem::PhysicSystem(cpSpace &space)
                : System(ecs::SYSTEM_PRIORITY::HIGHEST, 0.001), m_space{ space }
        {}

        void PhysicSystem::update(::ecs::Interval deltaTime) { cpSpaceStep(&m_space, deltaTime); }

}    // namespace star
