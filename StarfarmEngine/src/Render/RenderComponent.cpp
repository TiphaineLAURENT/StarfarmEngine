//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#include <numbers>

#include <Entity.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Log/LogSystem.hpp"
#include "../Physics/ColliderComponent.hpp"
#include "RenderComponent.hpp"

namespace star
{
        RenderComponent::RenderComponent()
        {
                if (sf::VertexBuffer::isAvailable())
                        m_verticesBuffer.create(4);
        }

        RenderComponent::RenderComponent(const sf::Texture &texture)
        {
                if (sf::VertexBuffer::isAvailable())
                        m_verticesBuffer.create(4);

                set_texture(texture);
        }

        RenderComponent::RenderComponent(const sf::Texture &texture, const sf::IntRect &rectangle)
        {
                if (sf::VertexBuffer::isAvailable())
                        m_verticesBuffer.create(4);

                set_texture(texture);
                set_texture_rect(rectangle);
        }

        void RenderComponent::set_texture(const sf::Texture &texture, bool resetRect)
        {
                // Recompute the texture area if requested, or if there was no valid texture & rect
                // before
                if (resetRect || (!m_texture && (m_textureRect == sf::IntRect{})))
                        set_texture_rect({ 0,
                                           0,
                                           static_cast<int>(texture.getSize().x),
                                           static_cast<int>(texture.getSize().y) });

                // Assign the new texture
                //::ecs::replace_pointer<const sf::Texture>(m_texture, &texture); // NOT WORKING
                const_cast<const sf::Texture *&>(m_texture) = &texture;
        }

        const ::ecs::NonOwningPointer<sf::Texture> RenderComponent::get_texture() const
        {
                return m_texture;
        }

        void RenderComponent::set_texture_rect(const sf::IntRect &rectangle)
        {
                if (rectangle != m_textureRect)
                {
                        m_textureRect = rectangle;
                        update_position();
                        update_texture_coordinates();

                        // Update the vertex buffer if it is being used
                        if (sf::VertexBuffer::isAvailable())
                                m_verticesBuffer.update(m_vertices);
                }
        }

        const sf::IntRect &RenderComponent::getTextureRect() const { return m_textureRect; }

        void RenderComponent::set_color(const sf::Color &color)
        {
                // Update the vertices' color
                m_vertices[0].color = color;
                m_vertices[1].color = color;
                m_vertices[2].color = color;
                m_vertices[3].color = color;

                // Update the vertex buffer if it is being used
                if (sf::VertexBuffer::isAvailable())
                        m_verticesBuffer.update(m_vertices);
        }

        const sf::Color &RenderComponent::get_color() const { return m_vertices[0].color; }

        sf::FloatRect RenderComponent::get_local_bounds() const
        {
                auto width = static_cast<float>(std::abs(m_textureRect.width));
                auto height = static_cast<float>(std::abs(m_textureRect.height));

                return { 0.f, 0.f, width, height };
        }

        void RenderComponent::update_position()
        {
                auto bounds = get_local_bounds();

                m_vertices[0].position = { 0, 0 };
                m_vertices[1].position = { 0, bounds.height };
                m_vertices[2].position = { bounds.width, 0 };
                m_vertices[3].position = { bounds.width, bounds.height };
        }

        void RenderComponent::update_texture_coordinates()
        {
                auto left = static_cast<float>(m_textureRect.left);
                auto right = left + m_textureRect.width;
                auto top = static_cast<float>(m_textureRect.top);
                auto bottom = top + m_textureRect.height;

                m_vertices[0].texCoords = { left, top };
                m_vertices[1].texCoords = { left, bottom };
                m_vertices[2].texCoords = { right, top };
                m_vertices[3].texCoords = { right, bottom };
        }

        void RenderComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const
        {
                auto position = m_transformComponent->get_position();
                states.transform.translate(position.x - m_textureRect.width / 2,
                                           position.y - m_textureRect.height / 2);

                auto rotation = m_transformComponent->get_rotation() * 180. / std::numbers::pi;
                states.transform.rotate(rotation);

                if (m_texture)
                {
                        states.texture = m_texture;

                        if (sf::VertexBuffer::isAvailable())
                        {
                                // target.draw(m_verticesBuffer, states);
                        }
                        else
                        {
                                target.draw(m_vertices, 4, sf::TriangleStrip, states);
                        }
                }
                const auto shape = get_owner()->get_component<ColliderComponent>()->m_shape.get();
                switch (shape->klass->type)
                {
                        case CP_CIRCLE_SHAPE:
                        {
                                cpCircleShape *circle = (cpCircleShape *)shape;
                                auto bbrender = sf::CircleShape{
                                        float(circle->r / 2.)
                                };    // TODO: Dunno why but it seems that the radius of the circle
                                      // is interpreted as a diameter by circleshape so whe have to
                                      // divide it by 2
                                bbrender.setOutlineColor(sf::Color::Red);
                                bbrender.setFillColor(sf::Color::Transparent);
                                bbrender.setOutlineThickness(1);
                                bbrender.setPosition(circle->tc.x, circle->tc.y);
                                target.draw(bbrender);
                                break;
                        }
                        case CP_SEGMENT_SHAPE:
                        {
                                cpSegmentShape *segment = (cpSegmentShape *)shape;
                                sf::Vertex vertices[2]{};
                                vertices[0] = { { (float)segment->ta.x, (float)segment->ta.y },
                                                sf::Color::Red };
                                vertices[1] = { { (float)segment->tb.x, (float)segment->tb.y },
                                                sf::Color::Red };
                                target.draw(vertices, 2, sf::Lines);
                                break;
                        }
                }
        }

        void RenderComponent::setup()
        {
                ecs::replace_pointer(m_transformComponent,
                                     get_owner()->get_component<RigidbodyComponent>());
        }

}    // namespace star
