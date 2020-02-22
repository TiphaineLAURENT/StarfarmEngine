//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>

#include "dynamics/b2_island.h"

#include "PhysicSystem.hpp"

namespace star
{

        PhysicSystem::PhysicSystem(const Vector2D &gravity)
                : _gravity{ gravity }
        {}

        void PhysicSystem::update(ecs::Interval deltaTime)
        {
                //step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
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

                auto island = b2Island{
                        (int32)_rigidbodies.size(),
                        _contactManager.m_contactCount,
                        (int32)_joints.size(),
                        &_allocator,
                        _contactManager.m_contactListener
                };

                for (const auto &body : _rigidbodies)
                {
                        body->_flags &= ~RIGIDBODY_FLAGS::ISLAND;
                }
                for (b2Contact *c = _contactManager.m_contactList; c; c = c->m_next)
                {
                        c->m_flags &= ~b2Contact::e_islandFlag;
                }
                for (const auto &joint : _joints)
                {
                        joint->m_islandFlag = false;
                }
        }

}
