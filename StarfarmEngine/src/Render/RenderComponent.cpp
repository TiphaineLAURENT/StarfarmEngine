//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Entity.hpp>
#include <cassert>

#include "RenderComponent.hpp"

namespace star
{

        RenderComponent::RenderComponent()
        {
                if (sf::VertexBuffer::isAvailable())
                        _verticesBuffer.create(4);
        }

        RenderComponent::RenderComponent(const sf::Texture &texture)
        {
                if (sf::VertexBuffer::isAvailable())
                        _verticesBuffer.create(4);

                set_texture(texture);
        }

        RenderComponent::RenderComponent(
                const sf::Texture &texture,
                const sf::IntRect &rectangle
        )
        {
                if (sf::VertexBuffer::isAvailable())
                        _verticesBuffer.create(4);

                set_texture(texture);
                set_texture_rect(rectangle);
        }

        void RenderComponent::set_texture(const sf::Texture &texture, bool resetRect)
        {
                // Recompute the texture area if requested, or if there was no valid texture & rect before
                if (resetRect || (!_texture && (_textureRect == sf::IntRect())))
                        set_texture_rect({0, 0,
                                        static_cast<int>(texture.getSize().x),
                                        static_cast<int>(texture.getSize().y)});

                // Assign the new texture
                auto *textureNonConstPointer = const_cast<const sf::Texture **>(&_texture);
                *textureNonConstPointer = &texture;
        }

        const ecs::NonOwningPointer<sf::Texture> RenderComponent::get_texture() const
        {
                return _texture;
        }

        void RenderComponent::set_texture_rect(const sf::IntRect &rectangle)
        {
                if (rectangle != _textureRect)
                {
                        _textureRect = rectangle;
                        update_position();
                        update_texture_coordinates();

                        // Update the vertex buffer if it is being used
                        if (sf::VertexBuffer::isAvailable())
                                _verticesBuffer.update(_vertices);
                }
        }

        const sf::IntRect &RenderComponent::getTextureRect() const
        {
                return _textureRect;
        }

        void RenderComponent::set_color(const sf::Color &color)
        {
                // Update the vertices' color
                _vertices[0].color = color;
                _vertices[1].color = color;
                _vertices[2].color = color;
                _vertices[3].color = color;

                // Update the vertex buffer if it is being used
                if (sf::VertexBuffer::isAvailable())
                        _verticesBuffer.update(_vertices);
        }

        const sf::Color &RenderComponent::get_color() const
        {
                return _vertices[0].color;
        }

        sf::FloatRect RenderComponent::get_local_bounds() const
        {
                auto width = static_cast<float>(std::abs(_textureRect.width));
                auto height = static_cast<float>(std::abs(_textureRect.height));

                return sf::FloatRect{0.f, 0.f, width, height};
        }

        void RenderComponent::update_position()
        {
                auto bounds = get_local_bounds();

                _vertices[0].position = sf::Vector2f(0, 0);
                _vertices[1].position = sf::Vector2f(0, bounds.height);
                _vertices[2].position = sf::Vector2f(bounds.width, 0);
                _vertices[3].position = sf::Vector2f(bounds.width, bounds.height);
        }

        void RenderComponent::update_texture_coordinates()
        {
                auto left = static_cast<float>(_textureRect.left);
                auto right = left + _textureRect.width;
                auto top = static_cast<float>(_textureRect.top);
                auto bottom = top + _textureRect.height;

                _vertices[0].texCoords = sf::Vector2f(left, top);
                _vertices[1].texCoords = sf::Vector2f(left, bottom);
                _vertices[2].texCoords = sf::Vector2f(right, top);
                _vertices[3].texCoords = sf::Vector2f(right, bottom);
        }

        void RenderComponent::draw(
                sf::RenderTarget &target,
                sf::RenderStates states
        ) const
        {
                if (_texture)
                {
                        states.transform *= _transformComponent->getTransform();
                        states.texture = _texture;

                        if (sf::VertexBuffer::isAvailable())
                        {
                                target.draw(_verticesBuffer, states);
                        }
                        else
                        {
                                target.draw(_vertices, 4, sf::TriangleStrip, states);
                        }
                }
        }

        void RenderComponent::setup()
        {
                auto *transformNonConstPointer = const_cast<TransformComponent **>(&_transformComponent);
                *transformNonConstPointer = get_owner()->get_component<TransformComponent>();
        }

}
