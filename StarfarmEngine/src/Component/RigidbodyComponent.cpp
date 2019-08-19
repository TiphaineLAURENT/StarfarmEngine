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
          _transformComponent = getOwner()->getComponent<TransformComponent>();
          _massInv = 1 / _mass;
  }

  void RigidbodyComponent::addForce(sf::Vector2f force, RIGIDBODY_FORCE_MODE mode)
  {
          addForce(force.x, force.y, mode);
  }
  void RigidbodyComponent::addForce(float x, float y, RIGIDBODY_FORCE_MODE mode)
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

  void RigidbodyComponent::updateVelocity(
          const sf::Vector2f &gravity,
          float deltaTime
  )
  {
          auto objectGravity = gravity * _gravityScale;
          auto draggedVelocity = _velocity * _drag;
          _velocity = draggedVelocity + (objectGravity + _forces * _massInv)
                                        * deltaTime;

          _angularVelocity = _angularVelocity * _angularDrag
                             + _torque * _massInv * deltaTime;

          _forces = {0., 0.};
          _torque = 0.;
  }

  void RigidbodyComponent::updatePosition(float deltaTime)
  {
          auto position = _transformComponent->getPosition();
          position += _velocity * deltaTime;
          setPosition(position);

          auto angle = _transformComponent->getRotation();
          angle += _angularVelocity * deltaTime;
          setRotation(angle);
  }

  void RigidbodyComponent::update(float deltaTime)
  {
          updateVelocity({SpaceGravity, SpaceGravity}, deltaTime);
          updatePosition(deltaTime);
  }

}
