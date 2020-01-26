//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
#define STARFARMENGINE_RIGIDBODYCOMPONENT_HPP

# include <ostream>
# include <utility>
# include <Component.hpp>

# include "../Util/Point.hpp"
# include "TransformComponent.hpp"

namespace star
{
  enum class RIGIDBODY_TYPE
          : unsigned
  {
          DYNAMIC,
          KINEMATIC,
          STATIC
  };

  enum class RIGIDBODY_CONSTRAINTS
          : unsigned
  {
          NONE = 1,
          FREEZE_X = NONE << 1u,
          FREEZE_Y = FREEZE_X << 1u,
          FREEZE_Z = FREEZE_Y << 1u,
          FREEZE_POSITION = FREEZE_X | FREEZE_Y,
          FREEZE_ROTATION = FREEZE_Z,
          FREEZE_ALL = FREEZE_ROTATION | FREEZE_POSITION
  };

  enum class RIGIDBODY_COLLISION_MODE
          : unsigned
  {
          DISCRETE,
          CONTINUOUS
  };

  enum class RIGIDBODY_FORCE_MODE
          : unsigned
  {
          IMPULSE,
          VELOCITYCHANGE
  };

  class COMPONENT(RigidbodyComponent)
  {
// ATTRIBUTES
  private:
          ecs::NonOwningPointer<TransformComponent> _transformComponent{nullptr};

          Force _angularDrag{0.};

          Speed _angularVelocity{0.};

          Force _torque{0.};

          RIGIDBODY_TYPE _rigidbodyType{RIGIDBODY_TYPE::DYNAMIC};

          RIGIDBODY_CONSTRAINTS _constraints{RIGIDBODY_CONSTRAINTS::NONE};

          RIGIDBODY_COLLISION_MODE _collisionMode{RIGIDBODY_COLLISION_MODE::DISCRETE};

          Point<2> _centerOfMass{0., 0.};

          Force _gravityScale{1.};

          Force _drag{0.};

          std::pair<Speed, Speed> _velocity{0., 0.};
          std::pair<Speed, Speed> _acceleration{0., 0.};

          std::pair<Force, Force> _forces{0., 0.};

          Force _inertia{0.};

          Weight _mass{1.};

          Weight _massInv{1.};

  public:

// METHODS
  public:// CONSTRUCTORS
          RigidbodyComponent() = default;
          ~RigidbodyComponent() override = default;
          RigidbodyComponent(const RigidbodyComponent &copy) = default;
          RigidbodyComponent(RigidbodyComponent &&) noexcept = default;

  public: //OPERATORS
          RigidbodyComponent &operator=(const RigidbodyComponent &other) = default;
          RigidbodyComponent &operator=(RigidbodyComponent &&) noexcept = default;

  public:
          void setup() override;

          template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
          void add_force(std::pair<Force, Force> force);
          template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
          void add_force(Force x, Force y);

          void move(Vector<2> offsets);
          void move(Coordinate x, Coordinate y);

          void set_position(Vector<2> coordinates);
          void set_position(Coordinate x, Coordinate y);

          void add_rotation(Angle angle);
          void set_rotation(Angle angle);

          void update_velocity(ecs::Interval deltaTime); // const Vector<2> &gravity, 
          void update_position(ecs::Interval deltaTime);
          void update(ecs::Interval deltaTime);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const RigidbodyComponent&);

}

#endif //STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
