# include "Vector.hpp"

namespace star
{

        template <>
        Length Vector<2>::calculate_magnitude() const
        {
                return std::sqrt(tail.x * tail.x + tail.y * tail.y);
        }

        template <>
        Length Vector<3>::calculate_magnitude() const
        {
                return std::sqrt(tail.x * tail.x
                                 + tail.y * tail.y
                                 + tail.z * tail.z);
        }

        template <>
        Angle Vector<2>::calculate_direction() const
        {
                return std::atan(tail.y / tail.x);
        }

        template <>
        Angle Vector<3>::calculate_direction() const
        {}

}