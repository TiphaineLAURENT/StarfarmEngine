//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
#define STARFARMENGINE_RIGIDBODYCOMPONENT_HPP

#include <memory>
#include <ostream>
#include <utility>

#include <Component.hpp>

#include <chipmunk/chipmunk_structs.h>
#include <chipmunk/cpBody.h>

#include "../Util/Vector.hpp"

namespace star
{
        class TransformComponent;
        class Scene;
        class ColliderComponent;

        enum class RIGIDBODY_CONSTRAINTS : unsigned
        {
                NONE = 1,
                FREEZE_X = NONE << 1u,
                FREEZE_Y = FREEZE_X << 1u,
                FREEZE_Z = FREEZE_Y << 1u,
                FREEZE_POSITION = FREEZE_X | FREEZE_Y,
                FREEZE_ROTATION = FREEZE_Z,
                FREEZE_ALL = FREEZE_ROTATION | FREEZE_POSITION
        };

        enum class RIGIDBODY_COLLISION_MODE : unsigned
        {
                DISCRETE,
                CONTINUOUS
        };

        enum class RIGIDBODY_FORCE_MODE : unsigned
        {
                FORCE,
                IMPULSE,
                VELOCITYCHANGE,
                ACCELERATION
        };

        class COMPONENT(RigidbodyComponent)
        {
                // ATTRIBUTES
            private:
                friend class ColliderComponent;
                friend class SegmentCollider;
                friend class CircleCollider;

                ecs::NonOwningPointer<cpSpace> m_space{ nullptr };

                ecs::NonOwningPointer<TransformComponent> m_transformComponent{ nullptr };

                std::unique_ptr<cpBody> m_body{ nullptr };

                // Force _angularDrag{0.};

                // Speed _angularVelocity{0.};

                // Force _torque{0.};

                // b2BodyType _rigidbodyType{b2BodyType::b2_dynamicBody};

                // RIGIDBODY_CONSTRAINTS _constraints{RIGIDBODY_CONSTRAINTS::NONE};

                // RIGIDBODY_COLLISION_MODE
                // _collisionMode{RIGIDBODY_COLLISION_MODE::DISCRETE};

                // Point<2> _centerOfMass{0., 0.};

                // Force _gravityScale{1.};

                // Force _drag{0.};

                // std::pair<Speed, Speed> _velocity{0., 0.};
                // std::pair<Speed, Speed> _acceleration{0., 0.};

                // std::pair<Force, Force> _forces{0., 0.};

                // Force _inertia{0.};

                // Weight _mass{1.};

                // Weight _massInv{1.};

            public:
                // METHODS
            public:    // CONSTRUCTORS
                explicit RigidbodyComponent(cpBodyType type = cpBodyType::CP_BODY_TYPE_DYNAMIC);
                ~RigidbodyComponent() override = default;
                RigidbodyComponent(const RigidbodyComponent &copy) = default;
                RigidbodyComponent(RigidbodyComponent &&) noexcept = default;

            public:    // OPERATORS
                RigidbodyComponent &operator=(const RigidbodyComponent &other) = default;
                RigidbodyComponent &operator=(RigidbodyComponent &&) noexcept = default;

            public:
                void setup() override;

                template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
                void add_force(const Vector<2> &force)
                {
                        if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                        {
                                cpBodyApplyImpulseAtLocalPoint(
                                        m_body.get(),
                                        force,
                                        cpBodyGetCenterOfGravity(m_body.get()));
                        }
                        else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                        {
                                cpBodySetVelocity(m_body.get(),
                                                  cpBodyGetVelocity(m_body.get()) + force);
                        }
                        else if constexpr (mode == RIGIDBODY_FORCE_MODE::ACCELERATION)
                        {}
                        else if constexpr (mode == RIGIDBODY_FORCE_MODE::FORCE)
                        {
                                cpBodyApplyForceAtLocalPoint(
                                        m_body.get(),
                                        force,
                                        cpBodyGetCenterOfGravity(m_body.get()));
                        }
                }
                template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
                void add_force(Force x, Force y)
                {
                        add_force<mode>({ x, y });
                }

                void move(const Vector<2> &offsets);
                void move(Coordinate x, Coordinate y);

                Vector<2> get_position() const;
                void set_position(const Vector<2> &coordinates);
                void set_position(Coordinate x, Coordinate y);

                const cpTransform &get_transform() const;

                Angle get_rotation() const;
                void add_rotation(Angle angle);
                void set_rotation(Angle angle);

                Vector<2> get_velocity() const;

                void update(ecs::Interval deltaTime);

            private:
        };

        std::ostream &operator<<(std::ostream &out, const RigidbodyComponent &);

}    // namespace star

#endif    // STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
