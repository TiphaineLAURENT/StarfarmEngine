//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#ifndef STARFARMENGINE_COLLIDERCOMPONENT_HPP
#define STARFARMENGINE_COLLIDERCOMPONENT_HPP

# include <ostream>
# include <vector>
# include <array>
# include <Component.hpp>
# include <IEntity.hpp>
# include <SFML/Graphics/Vertex.hpp>

# include "RigidbodyComponent.hpp"


namespace star
{

  class COMPONENT(ColliderComponent)
  {
// ATTRIBUTES
  private:
          float _bounciness{0.};

          float _density{0.};

          float _friction{0.};

          bool _isTrigger{false};

  protected:
          ecs::NonOwningPointer<RigidbodyComponent> _rigidbodyComponent{nullptr};

          ecs::NonOwningPointer<TransformComponent> _transformComponent{nullptr};

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
          void setup() override;

          [[nodiscard]] virtual std::vector<sf::Vector2f> get_vertices() const = 0;

          [[nodiscard]] virtual float distance_to(const sf::Vector2f &point)
          const = 0;
          [[nodiscard]] virtual bool contains(const sf::Vector2f &point)
          const = 0;

  private:
  };

  std::ostream &operator<<(std::ostream &out, const ColliderComponent &);

}

#endif //STARFARMENGINE_COLLIDERCOMPONENT_HPP
