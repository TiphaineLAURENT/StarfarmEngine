//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_RENDERCOMPONENT_HPP
#define STARFARMENGINE_RENDERCOMPONENT_HPP

#include <ostream>

#include "../Physics/RigidbodyComponent.hpp"
#include <Component.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace star
{
        class COMPONENT(RenderComponent), public sf::Drawable
        {
                // ATTRIBUTES
            private:
                sf::Vertex m_vertices[4]{};
                sf::VertexBuffer m_verticesBuffer{ sf::TrianglesStrip, sf::VertexBuffer::Stream };
                const ecs::NonOwningPointer<sf::Texture> m_texture{ nullptr };
                sf::IntRect m_textureRect{};

                ecs::NonOwningPointer<RigidbodyComponent> m_transformComponent{ nullptr };

            public:
                // METHODS
            public:    // CONSTRUCTORS
                RenderComponent();
                explicit RenderComponent(const sf::Texture &texture);
                RenderComponent(const sf::Texture &texture, const sf::IntRect &rectangle);
                ~RenderComponent() override = default;
                RenderComponent(const RenderComponent &copy) = default;
                RenderComponent(RenderComponent &&) = default;

            public:    // OPERATORS
                RenderComponent &operator=(const RenderComponent &other) = default;
                RenderComponent &operator=(RenderComponent &&) = default;

            public:
                void setup() override;

                void set_texture(const sf::Texture &texture, bool resetRect = false);
                [[nodiscard]] const ecs::NonOwningPointer<sf::Texture> get_texture() const;

                void set_texture_rect(const sf::IntRect &rectangle);
                [[nodiscard]] const sf::IntRect &getTextureRect() const;

                void set_color(const sf::Color &color);
                [[nodiscard]] const sf::Color &get_color() const;

                [[nodiscard]] sf::FloatRect get_local_bounds() const;

            private:
                void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

                void update_position();
                void update_texture_coordinates();
        };

        std::ostream &operator<<(std::ostream &out, const RenderComponent &);

}    // namespace star

#endif    // STARFARMENGINE_RENDERCOMPONENT_HPP
