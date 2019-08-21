//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include "ColliderComponent.hpp"


namespace star
{

  void ColliderComponent::setup()
  {
          _rigidbodyComponent = getOwner()->getComponent<RigidbodyComponent>();
          _transformComponent = getOwner()->getComponent<TransformComponent>();
  }
}
