//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <ComponentManager.hpp>
#include <IEntity.hpp>

#include "RigidbodyComponent.hpp"
#include "../Util/Vector.hpp"


namespace star
{

  void RigidbodyComponent::setup()
  {
          auto *transformNonConstPointer = const_cast<TransformComponent **>(&_transformComponent);
          *transformNonConstPointer = get_owner()->get_component<TransformComponent>();
          _massInv = 1 / _mass;
  }

  void RigidbodyComponent::add_force(sf::Vector2f force, RIGIDBODY_FORCE_MODE mode)
  {
          add_force(force.x, force.y, mode);
  }
  void RigidbodyComponent::add_force(float x, float y, RIGIDBODY_FORCE_MODE mode)
  {
          switch (mode) {
          case RIGIDBODY_FORCE_MODE::IMPULSE: {
                  _forces.x += x;
                  _forces.y += y;
                  break;
          }
          case RIGIDBODY_FORCE_MODE::VELOCITYCHANGE: {
                  _velocity.x += x;
                  _velocity.y += y;
                  break;
          }
          }
  }

  void RigidbodyComponent::move(sf::Vector2f offsets)
  {
          move(offsets.x, offsets.y);
  }
  void RigidbodyComponent::move(float x, float y)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->move(x, y);
  }

  void RigidbodyComponent::set_position(sf::Vector2f coordinates)
  {
          set_position(coordinates.x, coordinates.y);
  }
  void RigidbodyComponent::set_position(float x, float y)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->setPosition(x, y);
  }

  void RigidbodyComponent::add_rotation(float angle)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->rotate(angle);
  }
  void RigidbodyComponent::set_rotation(float angle)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->setRotation(angle);
  }

  void RigidbodyComponent::update_velocity(
          const sf::Vector2f &gravity,
          ecs::Interval deltaTime
  )
  {
          auto objectGravity = gravity * _gravityScale;
          auto draggedVelocity = _velocity * _drag;
          _velocity = draggedVelocity + (objectGravity + _forces * _massInv)
                                        * static_cast<float>(deltaTime);

          _angularVelocity = _angularVelocity * _angularDrag
                             + _torque * _massInv * deltaTime;

          _forces = {0., 0.};
          _torque = 0.;
  }

  void RigidbodyComponent::update_position(ecs::Interval deltaTime)
  {
          auto position = _transformComponent->getPosition();
          position += _velocity * static_cast<float>(deltaTime);
          set_position(position);

          auto angle = _transformComponent->getRotation();
          angle += _angularVelocity * deltaTime;
          set_rotation(angle);
  }

  void RigidbodyComponent::update(ecs::Interval deltaTime)
  {
          update_velocity({SpaceGravity, SpaceGravity}, deltaTime);
          update_position(deltaTime);
  }

}
