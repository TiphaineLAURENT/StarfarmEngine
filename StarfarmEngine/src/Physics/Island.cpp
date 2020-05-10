//
// Created by Tiphaine LAURENT
//

// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "Island.hpp"

#include <SFML/System/Clock.hpp>

#include "box2d/dynamics/b2_contact_solver.h"

#include "../Util/Vector.hpp"
#include "RigidbodyComponent.hpp"

namespace star
{
    Island::Island(std::size_t rigidbodyCapacity,
                   std::size_t contactCapacity,
                   std::size_t jointCapacity)
        : _rigidbodies{ rigidbodyCapacity }, _contacts{ contactCapacity }, _joints{
              jointCapacity
          }
    {}

    void Island::clear()
    {
        _rigidbodies.clear();
        _contacts.clear();
        _joints.clear();
    }

    void Island::solve(ecs::NonOwningPointer<Profile> profile,
                       ecs::Interval step,
                       const Vector2D &gravity,
                       bool allowSleep)
    {
        sf::Clock timer{};

        const auto rigidbodiesSize = _rigidbodies.size();
        for (decltype(rigidbodiesSize) i = 0; i < rigidbodiesSize; ++i)
        {
            auto &body = _rigidbodies[i].get();

            auto worldPositionCenter = body._sweep.c;
            auto worldAngles = body._sweep.a;
            auto linearVelocity = body._linearVelocity;
            auto angularVelocity = body._angularVelocity;

            body._sweep.c0 = worldPositionCenter;
            body._sweep.a0 = worldAngles;

            if (body.get_type() == RIGIDBODY_TYPE::DYNAMIC)
            {
                linearVelocity += step
                                  * (body._gravityScale * gravity * body._massInv
                                     * body._force);
                angularVelocity += step * (body._inertiaInv * body._torque);

                linearVelocity
                    *= 1.f / (1.f + linearVelocity * body->_linearDamping);
            }

            m_positions[i].c = c;
            m_positions[i].a = a;
            m_velocities[i].v = v;
            m_velocities[i].w = w;
        }

        timer.restart();

        // Solver data
        b2SolverData solverData;
        solverData.step = step;
        solverData.positions = _positions.data();
        solverData.velocities = _velocities.data();

        // Initialize velocity constraints.
        b2ContactSolverDef contactSolverDef;
        contactSolverDef.step = step;
        contactSolverDef.contacts = _contacts.data();
        contactSolverDef.count = _contacts.size();
        contactSolverDef.positions = _positions.data();
        contactSolverDef.velocities = _velocities.data();
        contactSolverDef.allocator = new;

        b2ContactSolver contactSolver(&contactSolverDef);
        contactSolver.InitializeVelocityConstraints();

        if (step.warmStarting)
        {
            contactSolver.WarmStart();
        }

        for (auto &joint : _joints)
        {
            joint->InitVelocityConstraints(solverData);
        }

        profile->solveInit = timer.getElapsedTime().asMilliseconds();

        // Solve velocity constraints
        timer.restart();
        for (int32 i = 0; i < step.velocityIterations; ++i)
        {
            for (auto &joint : _joints)
            {
                _joint->SolveVelocityConstraints(solverData);
            }

            contactSolver.SolveVelocityConstraints();
        }

        // Store impulses for warm starting
        contactSolver.StoreImpulses();
        profile->solveVelocity = timer.getElapsedTime().asMilliseconds();

        // Integrate positions
        auto rigidbodiesSize = _rigidbodies.size();
        for (decltype(rigidbodiesSize) i = 0; i < rigidbodiesSize; ++i)
        {
            auto c = _positions[i].c;
            auto a = _positions[i].a;
            auto v = _velocities[i].v;
            auto w = _velocities[i].w;

            // Check for large velocities
            b2Vec2 translation = h * v;
            if (b2Dot(translation, translation) > b2_maxTranslationSquared)
            {
                auto ratio = b2_maxTranslation / translation.Length();
                v *= ratio;
            }

            auto rotation = step * w;
            if (rotation * rotation > b2_maxRotationSquared)
            {
                auto ratio = b2_maxRotation / b2Abs(rotation);
                w *= ratio;
            }

            // Integrate
            c += h * v;
            a += h * w;

            _positions[i].c = c;
            _positions[i].a = a;
            _velocities[i].v = v;
            _velocities[i].w = w;
        }

        // Solve position constraints
        timer.restart();
        bool positionSolved = false;
        for (int32 i = 0; i < step.positionIterations; ++i)
        {
            bool contactsOkay = contactSolver.SolvePositionConstraints();

            bool jointsOkay = true;
            for (auto &joint : _joints)
            {
                bool jointOkay = _joint->SolvePositionConstraints(solverData);
                jointsOkay = jointsOkay && jointOkay;
            }

            if (contactsOkay && jointsOkay)
            {
                // Exit early if the position errors are small.
                positionSolved = true;
                break;
            }
        }

        // Copy state buffers back to the bodies
        const auto rigidbodiesSize = _rigidbodies.size();
        for (decltype(rigidbodiesSize) i = 0; i < rigidbodiesSize; ++i)
        {
            auto &body = _rigidbodies[i].get();
            body._sweep.c = _positions[i].c;
            body._sweep.a = _positions[i].a;
            body._linearVelocity = _velocities[i].v;
            body._angularVelocity = _velocities[i].w;
            body.SynchronizeTransform();
        }

        profile->solvePosition = timer.getElapsedTime().asMilliseconds();

        Report(contactSolver.m_velocityConstraints);

        if (allowSleep)
        {
            constexpr auto minSleepTime = std::numeric_limits<float>::max();

            constexpr auto linTolSqr
                = b2_linearSleepTolerance * b2_linearSleepTolerance;
            constexpr auto angTolSqr
                = b2_angularSleepTolerance * b2_angularSleepTolerance;

            for (auto &rigidbody : _rigidbodies)
            {
                if (rigidbody->get_type() == RIGIDBODY_TYPE::STATIC)
                {
                    continue;
                }

                if ((rigidbody->_flags & RIGIDBODY_FLAGS::AUTO_SLEEP) == 0
                    || rigidbody->_angularVelocity * rigidbody->_angularVelocity
                           > angTolSqr
                    || b2Dot(rigidbody->_linearVelocity,
                             rigidbody->_linearVelocity)
                           > linTolSqr)
                {
                    rigidbody->_sleepTime = 0.0f;
                    minSleepTime = 0.0f;
                }
                else
                {
                    rigidbody->_sleepTime += h;
                    minSleepTime = b2Min(minSleepTime, rigidbody->_sleepTime);
                }
            }

            if (minSleepTime >= b2_timeToSleep && positionSolved)
            {
                for (auto &rigidbody : _rigidbodies)
                {
                    rigidbody->SetAwake(false);
                }
            }
        }
    }

    void Island::solve_toi(ecs::Interval step, int toiIndexA, int toiIndexB)
    {

    }

    void Island::add(ecs::NonOwningPointer<RigidbodyComponent> body)
    {
        _rigidbodies.push_back(body);
    }

    void Island::add(ecs::NonOwningPointer<Contact> contact)
    {
        _contacts.push_back(contact);
    }

    void Island::add(ecs::NonOwningPointer<Joint> joint)
    {
        _joints.push_back(joint);
    }
    void Island::report(const ContactVelocityConstraint *constraints) {}
}   // namespace star