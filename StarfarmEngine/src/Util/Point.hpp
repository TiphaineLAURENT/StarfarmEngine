//
//
//

#ifndef STARFARMENGINE_POINT_HPP
# define STARFARMENGINE_POINT_HPP

# include <SFML/System/Vector2.hpp>
# include <SFML/System/Vector3.hpp>

namespace star
{

        using Coordinate = double;
        using Dimension = size_t;

        template <Dimension> struct Point;
        template <> class Point<2> : public sf::Vector2<Coordinate>
        {
        public:
                Point(Coordinate x_, Coordinate y_)
                        : Vector2(x_, y_)
                {}
        };
        template <> class Point<3> : public sf::Vector3<Coordinate>
        {
        public:
                Point(Coordinate x_, Coordinate y_, Coordinate z_)
                        : Vector3(x_, y_, z_)
                {}
        };

}

#endif // !STARFARMENGINE_POINT_HPP
