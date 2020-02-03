//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>
#include "PhysicSystem.hpp"
#include "RigidbodyComponent.hpp"


namespace star
{

        PhysicSystem::PhysicSystem(b2World &world)
                : System(), _world{world}
        {}

        void PhysicSystem::update(::ecs::Interval deltaTime)
        {
                _world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        }

}
