//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_COLLIDERCOMPONENT_HPP
#define STARFARMENGINE_COLLIDERCOMPONENT_HPP

# include <ostream>
# include <Component.hpp>

# include "RigidbodyComponent.hpp"


namespace star
{

  class COMPONENT(ColliderComponent)
  {
// ATTRIBUTES
  private:
          RigidbodyComponent *_rigidbodyComponent = nullptr;

  public:

// METHODS
  public:// CONSTRUCTORS
          ColliderComponent() = default;
          ~ColliderComponent() override = default;
          ColliderComponent(const ColliderComponent &copy) = default;
          ColliderComponent(ColliderComponent &&) noexcept = default;

  public: //OPERATORS
          ColliderComponent &operator=(const ColliderComponent &other) = default;
          ColliderComponent &operator=(ColliderComponent &&) noexcept = default;

  public:
  private:
  };

  std::ostream &operator<<(std::ostream &out, const ColliderComponent &);

}

#endif //STARFARMENGINE_COLLIDERCOMPONENT_HPP
