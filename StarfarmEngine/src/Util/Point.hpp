//
//
//

#ifndef STARFARMENGINE_POINT_HPP
# define STARFARMENGINE_POINT_HPP

# include <SFML/System/Vector2.hpp>
# include <SFML/System/Vector3.hpp>

namespace star
{

        using Coordinate = float;
        using Dimension = size_t;

        template <Dimension> struct Point;
        template <> struct Point<2> : public sf::Vector2<Coordinate>
        {
                Point(Coordinate x_, Coordinate y_)
                        : x{x_}, y{y_}
                {}
        };
        template <> struct Point<3> : public sf::Vector3<Coordinate>
        {
                Point(Coordinate x_, Coordinate y_, Coordinate z_)
                        : x{x_}, y{y_}, z{z_}
                {}
        };

}

#endif // !STARFARMENGINE_POINT_HPP
