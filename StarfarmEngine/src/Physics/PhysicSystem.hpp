//
// Created by Tiphaine LAURENT on 21/08/2019.
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

#ifndef STARFARMENGINE_PHYSICSYSTEM_HPP
#define STARFARMENGINE_PHYSICSYSTEM_HPP

# include <ostream>
# include <System.hpp>

# include "../Util/Vector.hpp"

namespace star
{

        struct Profile
        {
                ecs::Interval step;
                float collide;
                float solve;
                float solveInit;
                float solveVelocity;
                float solvePosition;
                float broadphase;
                float solveTOI;
        };

        class RigidbodyComponent;
        class Joint;
        class ContactManager;

        class SYSTEM(PhysicSystem)
        {
                // ATTRIBUTES
        private:
                enum class FLAGS
                {
                        NEW_FIXTURE = 0x0001,
                        LOCKED = 0x0002,
                        CLEAR_FORCES = 0x0004
                } _flags{ FLAGS::CLEAR_FORCES };

                ContactManager _contactManager{};

                ecs::ComponentContainer<RigidbodyComponent> &_rigidbodies{
                        ecs::ComponentManager::get_component_container<RigidbodyComponent>()
                };
                ecs::ComponentContainer<Joint> &_joints{
                        ecs::ComponentManager::get_component_container<Joint>()
                };

                Vector2D _gravity{ 0, EarthGravity };
                bool _allowSleep{ true };

                float _invDt{ 0 };

                bool _warmStarting{ true };
                bool _continuousPhysics{ true };
                bool _subStepping{ false };

                bool _stepComplete{ true };

                Profile _profile{};

                static constexpr auto TIME_STEP{ 1. / 60. };
                static constexpr auto VELOCITY_ITERATIONS{ 8 };
                static constexpr auto POSITION_ITERATIONS{ 3 };
        public:

                // METHODS
        public:// CONSTRUCTORS
                explicit PhysicSystem(const Vector2D &gravity);
                ~PhysicSystem() override = default;
                PhysicSystem(const PhysicSystem &copy) = delete;
                PhysicSystem(PhysicSystem &&) noexcept = delete;

        public: //OPERATORS
                PhysicSystem &operator=(const PhysicSystem & other) = delete;
                PhysicSystem &operator=(PhysicSystem &&) noexcept = delete;

        public:
                void update(::ecs::Interval deltaTime) override;

                void set_allow_sleeping(bool flag);
                void solve(const ecs::Interval &deltaTime);
        };

        std::ostream &operator<<(std::ostream &out, const PhysicSystem &);

}

#endif //STARFARMENGINE_PHYSICSYSTEM_HPP
