//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
#define STARFARMENGINE_RIGIDBODYCOMPONENT_HPP

# include <ostream>
# include <Component.hpp>

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
          TransformComponent *_transformComponent = nullptr;

          float _angularDrag = 0.;

          float _angularVelocity = 0.;

          RIGIDBODY_TYPE _rigidbodyType = RIGIDBODY_TYPE::DYNAMIC;

          RIGIDBODY_CONSTRAINTS _constraints = RIGIDBODY_CONSTRAINTS::NONE;

          RIGIDBODY_COLLISION_MODE _collisionMode =
                  RIGIDBODY_COLLISION_MODE::DISCRETE;

          sf::Vector2f _centerOfMass = {0., 0.};

          float _gravityScale = 1.;

          float _drag = 0.;

          sf::Vector2f _velocity = {0., 0.};

          float _inertia = 0.;

          float _mass = 1.;

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

          void addForce(
                  sf::Vector2f force, RIGIDBODY_FORCE_MODE mode =
          RIGIDBODY_FORCE_MODE::IMPULSE
          );
          void addForce(
                  float x, float y, RIGIDBODY_FORCE_MODE mode =
          RIGIDBODY_FORCE_MODE::IMPULSE
          );

          void move(sf::Vector2f offsets);
          void move(float x, float y);

          void setPosition(sf::Vector2f coordinates);
          void setPosition(float x, float y);

          void addRotation(float angle);
          void setRotation(float angle);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const RigidbodyComponent &);

}

#endif //STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
