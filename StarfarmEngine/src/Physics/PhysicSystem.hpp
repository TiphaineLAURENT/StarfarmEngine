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

# include "box2d/b2_contact_manager.h"
# include "box2d/b2_math.h"
# include "box2d/b2_time_step.h"
# include "box2d/b2_world_callbacks.h"
# include "box2d/b2_stack_allocator.h"

# include "../Util/enum_flags.hpp"
# include "../Util/Vector.hpp"
# include "RigidbodyComponent.hpp"

namespace star
{

        enum class PHYSICSYSTEM_FLAGS
                : unsigned
        {
                NEW_FIXTURE = 1u << 0,
                LOCKED = 1u << 1,
                CLEAR_FORCES = 1u << 2
        };
        ENUM_FLAGS(PHYSICSYSTEM_FLAGS);

        class SYSTEM(PhysicSystem)
        {
                // ATTRIBUTES
        private:
                PHYSICSYSTEM_FLAGS _flags{ PHYSICSYSTEM_FLAGS::CLEAR_FORCES };

                b2ContactManager _contactManager{};

                ecs::ComponentContainer<RigidbodyComponent> &_rigidbodies{
                        ecs::ComponentManager::get_component_container<RigidbodyComponent>()
                };
                ecs::ComponentContainer<b2Joint> &_joints{
                        ecs::ComponentManager::get_component_container<b2Joint>()
                };

                Vector2D _gravity{ 0, EarthGravity };
                bool _allowSleep{ true };

                float _invDt{ 0 };

                bool _warmStarting{ true };
                bool _continuousPhysics{ true };
                bool _subStepping{ false };

                bool _stepComplete{ true };

                b2Profile _profile{};

                static constexpr auto TIME_STEP{ 1. / 60. };
                static constexpr auto VELOCITY_ITERATIONS{ 8 };
                static constexpr auto POSITION_ITERATIONS{ 3 };

                b2StackAllocator _allocator{};
        public:

                // METHODS
        public:// CONSTRUCTORS
                explicit PhysicSystem() = default;
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
