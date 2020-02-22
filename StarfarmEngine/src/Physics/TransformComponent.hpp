//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_TRANSFORMCOMPONENT_HPP
# define STARFARMENGINE_TRANSFORMCOMPONENT_HPP

# include <ostream>

# include <Component.hpp>
# include <SFML/Graphics/Transformable.hpp>

namespace star
{

        class COMPONENT(TransformComponent), public sf::Transformable
        {
                // ATTRIBUTES
                  private:
                  public:

                          // METHODS
                            public:// CONSTRUCTORS
                                    TransformComponent() = default;
                                    TransformComponent(const TransformComponent &copy) = default;
                                    TransformComponent(TransformComponent &&) noexcept = default;

                            public: //OPERATORS
                                    TransformComponent &operator=(const TransformComponent &other) = default;
                                    TransformComponent &operator=(TransformComponent &&) noexcept = default;

                            public:
                            private:
        };

        std::ostream &operator<<(std::ostream &out, const TransformComponent &);

}

#endif //STARFARMENGINE_TRANSFORMCOMPONENT_HPP
