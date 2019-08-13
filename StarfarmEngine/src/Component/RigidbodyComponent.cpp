//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <ComponentManager.hpp>
#include <IEntity.hpp>

#include "RigidbodyComponent.hpp"

namespace star
{

  void RigidbodyComponent::setup()
  {
          _transformComponent = getOwner()->getComponent<TransformComponent>();
  }

  void RigidbodyComponent::addForce(sf::Vector2f force, RIGIDBODY_FORCE_MODE mode)
  {
          addForce(force.x, force.y, mode);
  }
  void RigidbodyComponent::addForce(float x, float y, RIGIDBODY_FORCE_MODE mode)
  {
          switch (mode) {
          case RIGIDBODY_FORCE_MODE::IMPULSE: {
                  _velocity.x = x / _mass;
                  _velocity.y = y / _mass;
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

  void RigidbodyComponent::setPosition(sf::Vector2f coordinates)
  {
          setPosition(coordinates.x, coordinates.y);
  }
  void RigidbodyComponent::setPosition(float x, float y)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->setPosition(x, y);
  }

  void RigidbodyComponent::addRotation(float angle)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->rotate(angle);
  }
  void RigidbodyComponent::setRotation(float angle)
  {
          if (!_transformComponent)
                  return;

          _transformComponent->setRotation(angle);
  }

}
