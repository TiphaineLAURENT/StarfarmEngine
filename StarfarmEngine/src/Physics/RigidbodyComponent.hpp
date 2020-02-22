//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
# define STARFARMENGINE_RIGIDBODYCOMPONENT_HPP

# include <ostream>
# include <utility>
# include <Component.hpp>

# include "box2d/b2_math.h"
# include "box2d/b2_shape.h"
# include "box2d/b2_fixture.h"
# include "box2d/b2_joint.h"
# include "box2d/b2_contact.h"

# include "../Util/Vector.hpp"
# include "../Util/enum_flags.hpp"


namespace star
{
        class TransformComponent;
        class Scene;

        class b2Joint;
        class b2Controller;
        class b2World;
        struct b2FixtureDef;


        enum class RIGIDBODY_TYPE
                : unsigned
        {
                DYNAMIC,
                STATIC,
                KINEMATIC
        };

        enum class RIGIDBODY_CONSTRAINTS
                : unsigned
        {
                NONE = 1u << 0,
                FREEZE_X = 1u << 1,
                FREEZE_Y = 1u << 2,
                FREEZE_Z = 1u << 3,
                FREEZE_POSITION = FREEZE_X | FREEZE_Y,
                FREEZE_ROTATION = FREEZE_Z,
                FREEZE_ALL = FREEZE_ROTATION | FREEZE_POSITION
        };
        ENUM_FLAGS(RIGIDBODY_CONSTRAINTS)

        enum class RIGIDBODY_COLLISION_MODE
                : unsigned
        {
                DISCRETE,
                CONTINUOUS
        };

        enum class RIGIDBODY_FORCE_MODE
                : unsigned
        {
                FORCE,
                IMPULSE,
                VELOCITYCHANGE,
                ACCELERATION
        };

        enum class RIGIDBODY_FLAGS
                : unsigned
        {
                ISLAND = 0x0001,
                AUTO_SLEEP = 0x0004,
                BULLET = 0x0008,
                TOI = 0x0010
        };
        ENUM_FLAGS(RIGIDBODY_FLAGS)

        class COMPONENT(RigidbodyComponent)
        {
                // ATTRIBUTES
        private:
                ecs::NonOwningPointer<TransformComponent> _transformComponent{ nullptr };

                Vector2D _linearVelocity{ 0.f, 0.f };
                Speed _angularVelocity{ 0.f };

                Force _linearDamping{ 0.f };
                Force _angularDamping{ 0.f };

                bool _allowSleep{ true };
                bool _awake{ true };

                RIGIDBODY_CONSTRAINTS _constraints{ RIGIDBODY_CONSTRAINTS::NONE };
                RIGIDBODY_TYPE _type{ RIGIDBODY_TYPE::STATIC };

                float _gravityScale{ 1.f };

                long _island{};

                b2Sweep _sweep{};

                Vector2D _force{ 0.f, 0.f };
                Force _torque{ 0.f };

                std::vector<b2Fixture> _fixtures{};

                std::vector<b2JointEdge> _joints{};
                std::vector<b2ContactEdge> _contacts{};

                Weight _mass{ 0.f };
                Weight _massInv{ 0.f };

                Force _inertia{ 0.f };
                Force _inertiaInv{ 0.f };

                ecs::Interval _sleepTime{ 0 };

        public:
                RIGIDBODY_FLAGS _flags{};

                // METHODS
        public:// CONSTRUCTORS
                RigidbodyComponent() = default;
                ~RigidbodyComponent() override = default;
                RigidbodyComponent(const RigidbodyComponent & copy) = default;
                RigidbodyComponent(RigidbodyComponent &&) noexcept = default;

        public: //OPERATORS
                RigidbodyComponent &operator=(const RigidbodyComponent & other) = default;
                RigidbodyComponent &operator=(RigidbodyComponent &&) noexcept = default;

        public:
                void setup() override;

                void apply_force(Force fx, Force fy, Coordinate x, Coordinate y);
                void apply_force(const Vector2D &force, const Vector2D &point);
                void apply_force_to_center(Force fx, Force fy);
                void apply_force_to_center(const Vector2D &force);

                void apply_torque(Force torque);

                void apply_linear_impulse(Force fx, Force fy, Coordinate x, Coordinate y);
                void apply_linear_impulse(const Vector2D &impulse, const Vector2D &point);
                void apply_linear_impulse_to_center(Force fx, Force fy);
                void apply_linear_impulse_to_center(const Vector2D &impulse);

                void apply_angular_impulse(Force impulse);

                //template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
                //void add_force(const Vector2D &force)
                //{
                //        add_force<mode>(force.x, force.y);
                //}
                //template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
                //void add_force(Force x, Force y)
                //{
                //        if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                //        {
                //                ApplyLinearImpulseToCenter(force, false);
                //        }
                //        else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                //        {
                //                _body->SetLinearVelocity(_body->GetLinearVelocity() + force);
                //        }
                //        else if constexpr (mode == RIGIDBODY_FORCE_MODE::ACCELERATION)
                //        {
                //        }
                //        else if constexpr (mode == RIGIDBODY_FORCE_MODE::FORCE)
                //        {
                //                _body->ApplyForceToCenter(force, false);
                //        }

                //        if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                //        {
                //                _forces.x += x;
                //                _forces.y += y;
                //        }
                //        else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                //        {
                //                _velocity.x += x;
                //                _velocity.y += y;
                //        }
                //}

                void move(const Vector2D &offsets);
                void move(Coordinate x, Coordinate y);

                void set_position(const Vector2D & coordinates);
                void set_position(Coordinate x, Coordinate y);

                void add_rotation(Angle angle);
                void set_rotation(Angle angle);

                TransformComponent &get_transform();
                const TransformComponent &get_transform() const;

                void set_linear_velocity(const Vector2D &velocity);
                const Vector2D &get_linear_velocity() const;

                void set_angular_velocity(Speed velocity);
                const Speed &get_angular_velocity() const;

                const Weight &get_mass() const;

                Force calculate_inertia() const;

                void set_type(RIGIDBODY_TYPE type);
                const RIGIDBODY_TYPE &get_type() const;

                void set_linear_damping(Force damping);
                const Force &get_linear_damping() const;

                void set_angular_damping(Force damping);
                const Force &get_angular_damping() const;

                void set_gravity_scale(float scale);
                const float &get_gravity_scale() const;

                void set_awake(bool flag);
                bool is_awake() const;

                bool has_fixed_rotation() const;

                void allow_sleeping();
                void disallow_sleeping();

                bool is_sleeping_allowed() const;

                std::vector<b2Fixture> &get_fixtures();
                const std::vector<b2Fixture> &get_fixtures() const;

                std::vector<b2JointEdge> &get_joints();
                const std::vector<b2JointEdge> &get_joints() const;

                std::vector<b2ContactEdge> &get_contacts();
                const std::vector<b2ContactEdge> &get_contacts() const;

                void synchronize_transform();
                void advance(float alpha);

                //void update_velocity(ecs::Interval deltaTime); // const Vector<2> &gravity, 
                //void update_position(ecs::Interval deltaTime);
                //void update(ecs::Interval deltaTime);

        private:
        };

        std::ostream &operator<<(std::ostream &out, const RigidbodyComponent &);

}

#endif //STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
