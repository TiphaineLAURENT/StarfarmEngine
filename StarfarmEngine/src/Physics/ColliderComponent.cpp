//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include "ColliderComponent.hpp"


namespace star
{

  void ColliderComponent::setup()
  {
          auto *rigidbodyNonConstPointer = const_cast<RigidbodyComponent **>(&_rigidbodyComponent);
          *rigidbodyNonConstPointer = get_owner()->get_component<RigidbodyComponent>();
          auto *transformNonConstPointer = const_cast<TransformComponent **>(&_transformComponent);
          *transformNonConstPointer = get_owner()->get_component<TransformComponent>();
  }
}
