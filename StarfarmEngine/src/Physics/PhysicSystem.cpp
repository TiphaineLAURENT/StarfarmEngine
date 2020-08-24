//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>
#include "PhysicSystem.hpp"
#include "RigidbodyComponent.hpp"


namespace star
{

        PhysicSystem::PhysicSystem(cpSpace &space)
                : System(), m_space{space}
        {}

        void PhysicSystem::update(::ecs::Interval deltaTime)
        {
            cpSpaceStep(&m_space, deltaTime);
        }

}
