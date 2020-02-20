//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>

#include "PhysicSystem.hpp"
#include "RigidbodyComponent.hpp"
#include "Island.hpp"


namespace star
{

        PhysicSystem::PhysicSystem(const Vector2D &gravity)
                : System(), _gravity{ gravity }
        {}

        void PhysicSystem::update(::ecs::Interval deltaTime)
        {
                step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        }

        void PhysicSystem::set_allow_sleeping(bool flag)
        {
                _allowSleep = flag;
                if (_allowSleep)
                {
                        for (auto &body : _rigidbodies)
                        {
                                body->set_awake(true);
                        }
                }
        }

        void PhysicSystem::solve(const ecs::Interval &deltaTime)
        {
                _profile.solveInit = 0.f;
                _profile.solveVelocity = 0.f;
                _profile.solvePosition = 0.f;

                auto island = Island{_rigidbodies.count(), ,_joints};
        }

}
