//
// Created by Tiphaine LAURENT on 13/08/2019.
//

# include "BoxCollider.hpp"
# include "../Util/Vector.hpp"

namespace star
{

  BoxCollider::BoxCollider(float width, float height)
          : ColliderComponent(),
            _bounds(_transformComponent->getPosition(), {width, height})
  {
          updateAngles();
  }

  BoxCollider::BoxCollider(const sf::FloatRect &bounds)
          : ColliderComponent(), _bounds(bounds)
  {
          updateAngles();
  }

  float BoxCollider::distanceTo(const sf::Vector2f &point) const
  {
          auto distances = std::array<float, 4>{};
          distances[0] = distance(_angles[0] + _transformComponent->getPosition(), point);
          distances[1] = distance(_angles[1] +
                  _transformComponent->getPosition(), point);
          distances[2] = distance(_angles[2] +
                  _transformComponent->getPosition(), point);
          distances[3] = distance(_angles[3] +
                  _transformComponent->getPosition(), point);

          auto it = std::min_element(distances.begin(), distances.end(),
                  [](float distance1, float distance2){
                        return distance1 < distance2;
          });
          return *it;
  }

  bool BoxCollider::contains(const sf::Vector2f &point) const
  {
          return _bounds.contains(point);
  }

  bool BoxCollider::intersects(const BoxCollider &other) const
  {
          return _bounds.intersects(other._bounds);
  }

  const sf::FloatRect &BoxCollider::getBounds() const
  {
          return _bounds;
  }

  std::vector<sf::Vector2f> BoxCollider::getVertices() const
  {
          return {_angles.begin(), _angles.end()};
  }

  void BoxCollider::setOffset(float x, float y)
  {
          _offset = {x, y};
          auto position = _transformComponent->getPosition();
          _bounds.left = position.x + x;
          _bounds.top = position.y + y;
          updateAngles();
  }

  void BoxCollider::updateAngles()
  {
          _angles[0] = {_bounds.left, _bounds.top};
          _angles[1] = {_bounds.left + _bounds.width, _bounds.top};
          _angles[2] = {
                  _bounds.left + _bounds.width, _bounds.top + _bounds.height
          };
          _angles[3] = {_bounds.left, _bounds.top + _bounds.height};
  }

  void BoxCollider::collide(const std::vector<BoxCollider *> &colliders)
  {
          for (
                  auto &collider : colliders
                  ) {
                  if (collider->intersects(*this)) {
                          // Trigger something
                  }
          }
  }

}

