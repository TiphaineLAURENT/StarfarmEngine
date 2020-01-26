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

          sf::Vector2f _offset{0., 0.};
          std::array<sf::Vector2f, 4> _angles{};

          float _size{0.};

  public:

// METHODS
  public:// CONSTRUCTORS
          BoxCollider(float width, float height);
          explicit BoxCollider(const sf::FloatRect &bounds);
          ~BoxCollider() override = default;
          BoxCollider(const BoxCollider &copy) = default;
          BoxCollider(BoxCollider &&) noexcept = default;

  public: //OPERATORS
          BoxCollider &operator=(const BoxCollider &other) = default;
          BoxCollider &operator=(BoxCollider &&) noexcept = default;

  public:
          void set_offset(float x, float y);

          [[nodiscard]] const sf::FloatRect &get_bounds() const;
          [[nodiscard]] std::vector<sf::Vector2f> get_vertices() const override;

          [[nodiscard]] float distance_to(const sf::Vector2f &point) const override;
          [[nodiscard]] bool contains(const sf::Vector2f &point) const override;
          [[nodiscard]] bool intersects(const BoxCollider &other) const;

          void collide(const std::vector<BoxCollider *> &);

  private:
          void update_angles();
  };

  std::ostream &operator<<(std::ostream &out, const BoxCollider &);

}

#endif //STARFARMENGINE_BOXCOLLIDER_HPP
