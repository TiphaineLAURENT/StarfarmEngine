//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#include "ColliderComponent.hpp"


namespace star
{

  void ColliderComponent::setup()
  {
          ecs::replace_pointer(_rigidbodyComponent, get_owner()->get_component<RigidbodyComponent>());
          ecs::replace_pointer(_transformCompoent, get_owner()->get_component<TransformComponent>());
  }
}
