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

#ifndef STARFARMENGINE_ISLAND_HPP
#define STARFARMENGINE_ISLAND_HPP

#include <util.hpp>
#include <vector>

#include "box2d/b2_time_step.h"

namespace star
{
    class RigidbodyComponent;
    class Profile;
    class Contact;
    class Joint;

    class Island
    {
        // ATTRIBUTES
    private:
        std::vector<std::reference_wrapper<RigidbodyComponent>> _rigidbodies{};
        std::vector<std::reference_wrapper<Contact>> _contacts{};
        std::vector<std::reference_wrapper<Joint>> _joints{};

         std::vector<b2Position> _positions{};
         std::vector<b2Velocity> _velocities{};

    public:
        // METHODS
    public:   // CONSTRUCTORS
        explicit Island(std::size_t rigidbodyCapacity,
                        std::size_t contactCapacity,
                        std::size_t jointCapacity);
        ~Island() = default;
        Island(const Island &copy) = delete;
        Island(Island &&) noexcept = delete;

    public:   // OPERATORS
        Island &operator=(const Island &other) = delete;
        Island &operator=(Island &&) noexcept = delete;

    public:
        void clear();

        void solve(ecs::NonOwningPointer<Profile> profile,
                   ecs::Interval step,
                   const Vector2D &gravity,
                   bool allowSleep);
        void solve_toi(ecs::Interval step, int toiIndexA, int toiIndexB);

        void add(ecs::NonOwningPointer<RigidbodyComponent> body);
        void add(ecs::NonOwningPointer<Contact> contact);
        void add(ecs::NonOwningPointer<Joint> joint);

        // void report(const ContactVelocityConstraint *constraints);
    };
}   // namespace star

#endif /* !STARFARMENGINE_ISLAND_HPP */