//
// Created by Tiphaine LAURENT on 07/08/2019.
//

#ifndef STARFARMENGINE_RENDERCOMPONENT_HPP
#define STARFARMENGINE_RENDERCOMPONENT_HPP

# include <ostream>

# include <Component.hpp>
# include <SFML/Graphics/Drawable.hpp>
# include <SFML/Graphics/Transformable.hpp>
# include <SFML/Graphics/Vertex.hpp>
# include <SFML/Graphics/Rect.hpp>
# include <SFML/Graphics/VertexBuffer.hpp>
#include "../Physics/TransformComponent.hpp"


namespace star
{

  class COMPONENT(RenderComponent), public sf::Drawable
  {
// ATTRIBUTES
  private:
          sf::Vertex         _vertices[4]{};
          sf::VertexBuffer   _verticesBuffer{sf::TrianglesStrip,
                                             sf::VertexBuffer::Stream};
          const sf::Texture* _texture = nullptr;
          sf::IntRect        _textureRect{};

          TransformComponent *_transformComponent = nullptr;

  public:

// METHODS
  public:// CONSTRUCTORS
          RenderComponent();
          explicit RenderComponent(const sf::Texture &texture);
          RenderComponent(const sf::Texture &texture,
                          const sf::IntRect &rectangle);
          ~RenderComponent() override = default;
          RenderComponent(const RenderComponent &copy) = default;
          RenderComponent(RenderComponent &&) = default;

  public: //OPERATORS
          RenderComponent &operator=(const RenderComponent &other) = default;
          RenderComponent &operator=(RenderComponent &&) = default;

  public:
          void setup() override;

          void setTexture(const sf::Texture& texture, bool resetRect = false);
          [[nodiscard]] const sf::Texture* getTexture() const;

          void setTextureRect(const sf::IntRect& rectangle);
          [[nodiscard]] const sf::IntRect& getTextureRect() const;

          void setColor(const sf::Color& color);
          [[nodiscard]] const sf::Color& getColor() const;

          [[nodiscard]] sf::FloatRect getLocalBounds() const;

  private:
          void draw (sf::RenderTarget &target,
                     sf::RenderStates states
          ) const override;

          void updatePositions();
          void updateTexCoords();
  };

  std::ostream &operator<<(std::ostream &out, const RenderComponent &);

}

#endif //STARFARMENGINE_RENDERCOMPONENT_HPP
