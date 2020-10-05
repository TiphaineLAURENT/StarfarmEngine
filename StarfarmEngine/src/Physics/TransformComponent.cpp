//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include "TransformComponent.hpp"
#include "IEntity.hpp"

namespace star
{
        void TransformComponent::setup() {}

        Vector<2> TransformComponent::get_position() const
        {
            return { m_x, m_y };
        }
        void TransformComponent::set_position(const Vector<2> &coordinates)
        {
                set_position(coordinates.x, coordinates.y);
        }
        void TransformComponent::set_position(Coordinate x, Coordinate y)
        {
                m_x = x;
                m_y = y;
        }

        void TransformComponent::move(const Vector<2> &offsets) { move(offsets.x, offsets.y); }
        void TransformComponent::move(Coordinate x, Coordinate y)
        {
                m_x += x;
                m_y += y;
        }

        Angle TransformComponent::get_rotation() const { return m_rotation; }
        void TransformComponent::set_rotation(Angle rotation) { m_rotation = rotation; }
        void TransformComponent::rotate(Angle rotation) { set_rotation(get_rotation() + rotation); }
}    // namespace star
