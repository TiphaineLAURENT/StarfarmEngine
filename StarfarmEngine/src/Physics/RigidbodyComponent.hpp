//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
# define STARFARMENGINE_RIGIDBODYCOMPONENT_HPP

# include <ostream>
# include <utility>
# include <Component.hpp>

# include <box2d/b2_body.h>
# include <box2d/b2_polygon_shape.h>
# include <box2d/b2_fixture.h>

# include "../Util/Vector.hpp"

namespace star
{
        class TransformComponent;
        class Scene;

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
          FORCE,
          IMPULSE,
          VELOCITYCHANGE,
          ACCELERATION
  };

  class COMPONENT(RigidbodyComponent)
  {
// ATTRIBUTES
  private:
          ecs::NonOwningPointer<TransformComponent> _transformComponent{nullptr};

          b2BodyDef _bodyDef{};
          ecs::NonOwningPointer<b2Body> _body{nullptr};
          b2PolygonShape _dynamicBox{};
          b2FixtureDef _fixtureDef{};

          //Force _angularDrag{0.};

          //Speed _angularVelocity{0.};

          //Force _torque{0.};

          //b2BodyType _rigidbodyType{b2BodyType::b2_dynamicBody};

          //RIGIDBODY_CONSTRAINTS _constraints{RIGIDBODY_CONSTRAINTS::NONE};

          //RIGIDBODY_COLLISION_MODE _collisionMode{RIGIDBODY_COLLISION_MODE::DISCRETE};

          //Point<2> _centerOfMass{0., 0.};

          //Force _gravityScale{1.};

          //Force _drag{0.};

          //std::pair<Speed, Speed> _velocity{0., 0.};
          //std::pair<Speed, Speed> _acceleration{0., 0.};

          //std::pair<Force, Force> _forces{0., 0.};

          //Force _inertia{0.};

          //Weight _mass{1.};

          //Weight _massInv{1.};

  public:

// METHODS
  public:// CONSTRUCTORS
          explicit RigidbodyComponent();
          ~RigidbodyComponent() override = default;
          RigidbodyComponent(const RigidbodyComponent &copy) = default;
          RigidbodyComponent(RigidbodyComponent &&) noexcept = default;

  public: //OPERATORS
          RigidbodyComponent &operator=(const RigidbodyComponent &other) = default;
          RigidbodyComponent &operator=(RigidbodyComponent &&) noexcept = default;

  public:
          void setup() override;

          template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
          void add_force(const Vector<2> &force)
          {
                  if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                  {
                          _body->ApplyLinearImpulseToCenter(force, false);
                  }
                  else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                  {
                          _body->SetLinearVelocity(_body->GetLinearVelocity() + force);
                  }
                  else if constexpr (mode == RIGIDBODY_FORCE_MODE::ACCELERATION)
                  {
                  }
                  else if constexpr (mode == RIGIDBODY_FORCE_MODE::FORCE)
                  {
                          _body->ApplyForceToCenter(force, false);
                  }
                  //add_force<mode>(force.x, force.y);
          }
          template <RIGIDBODY_FORCE_MODE mode = RIGIDBODY_FORCE_MODE::IMPULSE>
          void add_force(Force x, Force y)
          {
                  add_force<mode>({x, y});
                  //if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                  //{
                  //        _forces.x += x;
                  //        _forces.y += y;
                  //}
                  //else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                  //{
                  //        _velocity.x += x;
                  //        _velocity.y += y;
                  //}
          }

          void move(const Vector<2> &offsets);
          void move(Coordinate x, Coordinate y);

          void set_position(const Vector<2> &coordinates);
          void set_position(Coordinate x, Coordinate y);
          const b2Transform &get_transform() const;

          void add_rotation(Angle angle);
          void set_rotation(Angle angle);

          //void update_velocity(ecs::Interval deltaTime); // const Vector<2> &gravity, 
          //void update_position(ecs::Interval deltaTime);
          //void update(ecs::Interval deltaTime);

  private:
  };

  std::ostream &operator<<(std::ostream &out, const RigidbodyComponent&);

}

#endif //STARFARMENGINE_RIGIDBODYCOMPONENT_HPP
