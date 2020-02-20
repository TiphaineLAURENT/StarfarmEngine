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

#include <SFML/System/Clock.hpp>
#include "Island.hpp"

namespace star
{
        Island::Island(int rigidbodyCapacity, int contactCapacity, int jointCapacity)
                : _rigidbodies{ rigidbodyCapacity },
                _contacts{ contactCapacity },
                _joints{ jointCapacity }
        {}

        void Island::clear()
        {
                _rigidbodies.clear();
                _contacts.clear();
                _joints.clear();
        }

        void Island::solve(ecs::NonOwningPointer<Profile> profile, ecs::Interval step, const Vector2D &gravity, bool allowSleep)
        {
                sf::Clock timer{};

                for (auto &body : _rigidbodies)
                {

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
        void Island::report(const ContactVelocityConstraint *constraints)
        {}
}