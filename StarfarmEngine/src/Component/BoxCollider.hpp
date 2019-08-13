//
// Created by Tiphaine LAURENT on 13/08/2019.
//

#ifndef STARFARMENGINE_BOXCOLLIDER_HPP
#define STARFARMENGINE_BOXCOLLIDER_HPP

# include <ostream>

# include "ColliderComponent.hpp"


namespace star
{

  class BoxCollider : public ColliderComponent
  {
// ATTRIBUTES
  private:
          sf::FloatRect _bounds{};
          std::array<sf::Vector2f, 4> _angles{};

          float _size = 0.;

  public:

// METHODS
  public:// CONSTRUCTORS
          explicit BoxCollider(const sf::FloatRect &bounds);
          ~BoxCollider() override = default;
          BoxCollider(const BoxCollider &copy) = default;
          BoxCollider(BoxCollider &&) noexcept = default;

  public: //OPERATORS
          BoxCollider &operator=(const BoxCollider &other) = default;
          BoxCollider &operator=(BoxCollider &&) noexcept = default;

  public:
          [[nodiscard]] const sf::FloatRect &getBounds() const;
          [[nodiscard]] std::vector<sf::Vector2f> getVertices() const override;

          float distanceTo(const sf::Vector2f &point) const override;
          bool contains(const sf::Vector2f &point) const override;
          [[nodiscard]] bool intersects(const BoxCollider &other) const;


  private:
  };

  std::ostream &operator<<(std::ostream &out, const BoxCollider &);

}

#endif //STARFARMENGINE_BOXCOLLIDER_HPP
