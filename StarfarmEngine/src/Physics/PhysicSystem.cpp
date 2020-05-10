//
// Created by Tiphaine LAURENT on 21/08/2019.
//

#include <ComponentManager.hpp>

#include "PhysicSystem.hpp"

#include "dynamics/b2_contact_solver.h"
#include "dynamics/b2_island.h"

#include "box2d/b2_body.h"
#include "box2d/b2_broad_phase.h"
#include "box2d/b2_chain_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_collision.h"
#include "box2d/b2_contact.h"
#include "box2d/b2_draw.h"
#include "box2d/b2_edge_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_pulley_joint.h"
#include "box2d/b2_time_of_impact.h"
#include "box2d/b2_timer.h"
#include "box2d/b2_world.h"

namespace star
{
    PhysicSystem::PhysicSystem(const Vector2D &gravity) : _gravity{ gravity } {}

    void PhysicSystem::update(ecs::Interval deltaTime)
    {
        // step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
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

        auto island = b2Island{ (int)_rigidbodies.size(),
                                _contactManager.m_contactCount,
                                (int)_joints.size(),
                                &_allocator,
                                _contactManager.m_contactListener };

        for (const auto &body : _rigidbodies)
        {
            body->_flags &= ~RIGIDBODY_FLAGS::ISLAND;
        }
        for (auto *c = _contactManager.m_contactList; c; c = c->m_next)
        {
            c->m_flags &= ~b2Contact::e_islandFlag;
        }
        for (const auto &joint : _joints)
        {
            joint->m_islandFlag = false;
        }

        const auto stackSize = _rigidbodies.size();
        std::vector<RigidbodyComponent *> stack{ stackSize };
        for (auto &body : _rigidbodies)
        {
            if ((body->_flags & RIGIDBODY_FLAGS::ISLAND)
                == RIGIDBODY_FLAGS::ISLAND)
            {
                continue;
            }

            if (body->is_awake() == false || body->is_enabled() == false)
            {
                continue;
            }

            // The seed can be dynamic or kinematic.
            if (body->get_type() == RIGIDBODY_TYPE::STATIC)
            {
                continue;
            }

            // Reset island and stack.
            island.Clear();
            auto stackCount = 0;
            stack[stackCount++] = body.get();
            body->_flags |= RIGIDBODY_FLAGS::ISLAND;

            // Perform a depth first search (DFS) on the constraint graph.
            while (stackCount > 0)
            {
                // Grab the next body off the stack and add it to the island.
                auto *b = stack[--stackCount];
                b2Assert(b->is_enabled() == true);
                island.Add(b);

                // Make sure the body is awake (without resetting sleep timer).
                body->set_awake(true);

                // To keep islands as small as possible, we don't
                // propagate islands across static bodies.
                if (b->get_type() == RIGIDBODY_TYPE::STATIC)
                {
                    continue;
                }

                // Search all contacts connected to this body.
                for (auto &ce : b->_contacts)
                {
                    auto *contact = ce.contact;

                    // Has this contact already been added to an island?
                    if (contact->m_flags & b2Contact::e_islandFlag)
                    {
                        continue;
                    }

                    // Is this contact solid and touching?
                    if (contact->IsEnabled() == false
                        || contact->IsTouching() == false)
                    {
                        continue;
                    }

                    // Skip sensors.
                    bool sensorA = contact->m_fixtureA->m_isSensor;
                    bool sensorB = contact->m_fixtureB->m_isSensor;
                    if (sensorA || sensorB)
                    {
                        continue;
                    }

                    island.Add(contact);
                    contact->m_flags |= b2Contact::e_islandFlag;

                    b2Body *other = ce.other;

                    // Was the other body already added to this island?
                    if (other->m_flags & b2Body::e_islandFlag)
                    {
                        continue;
                    }

                    b2Assert(stackCount < stackSize);
                    stack[stackCount++] = other;
                    other->m_flags |= b2Body::e_islandFlag;
                }

                // Search all joints connect to this body.
                for (b2JointEdge *je = b->m_jointList; je; je = je->next)
                {
                    if (je->joint->m_islandFlag == true)
                    {
                        continue;
                    }

                    b2Body *other = je->other;

                    // Don't simulate joints connected to inactive bodies.
                    if (other->IsActive() == false)
                    {
                        continue;
                    }

                    island.Add(je->joint);
                    je->joint->m_islandFlag = true;

                    if (other->m_flags & b2Body::e_islandFlag)
                    {
                        continue;
                    }

                    b2Assert(stackCount < stackSize);
                    stack[stackCount++] = other;
                    other->m_flags |= b2Body::e_islandFlag;
                }
            }

            b2Profile profile;
            island.Solve(&profile, step, m_gravity, m_allowSleep);
            m_profile.solveInit += profile.solveInit;
            m_profile.solveVelocity += profile.solveVelocity;
            m_profile.solvePosition += profile.solvePosition;

            // Post solve cleanup.
            for (int32 i = 0; i < island.m_bodyCount; ++i)
            {
                // Allow static bodies to participate in other islands.
                b2Body *b = island.m_bodies[i];
                if (b->GetType() == b2_staticBody)
                {
                    b->m_flags &= ~b2Body::e_islandFlag;
                }
            }
        }

        m_stackAllocator.Free(stack);

        {
            b2Timer timer;
            // Synchronize fixtures, check for out of range bodies.
            for (b2Body *b = m_bodyList; b; b = b->GetNext())
            {
                // If a body was not in an island then it did not move.
                if ((b->m_flags & b2Body::e_islandFlag) == 0)
                {
                    continue;
                }

                if (b->GetType() == b2_staticBody)
                {
                    continue;
                }

                // Update fixtures (for broad-phase).
                b->SynchronizeFixtures();
            }

            // Look for new contacts.
            m_contactManager.FindNewContacts();
            m_profile.broadphase = timer.GetMilliseconds();
        })
    }
}   // namespace star
}
