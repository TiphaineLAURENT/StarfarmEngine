//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <ComponentManager.hpp>
#include <IEntity.hpp>
#include <util.hpp>

#include "../GameObject/GameObject.hpp"
#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Util/Vector.hpp"


namespace star
{

        RigidbodyComponent::RigidbodyComponent()
        {
                _bodyDef.type = b2BodyType::b2_dynamicBody;
                _bodyDef.position.SetZero();

                _dynamicBox.SetAsBox(1., 1.);

                _fixtureDef.shape = &_dynamicBox;
                _fixtureDef.density = 1.;
                _fixtureDef.friction = 0.3;
        }

        void RigidbodyComponent::setup()
        {
                ecs::replace_pointer(_transformComponent, get_owner()->get_component<TransformComponent>());
                assert(("A entity cannot have a rigidbogy without having a transform",
                        _transformComponent != nullptr));

                auto &scene = static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                auto &world = scene.get_world();
                ecs::replace_pointer(_body, world.CreateBody(&_bodyDef));
                _body->CreateFixture(&_fixtureDef);

                //_massInv = 1 / _mass;
        }

        void RigidbodyComponent::move(const Vector<2> &offsets)
        {
                set_position(offsets);
                //move(offsets.x, offsets.y);
        }
        void RigidbodyComponent::move(Coordinate x, Coordinate y)
        {
                move({x, y});
                //if (!_transformComponent)
                //        return;

                //_transformComponent->move(x, y);
        }

        void RigidbodyComponent::set_position(const Vector<2> &coordinates)
        {
                _body->SetTransform(coordinates, _body->GetAngle());
                //set_position(coordinates.x, coordinates.y);
        }
        void RigidbodyComponent::set_position(Coordinate x, Coordinate y)
        {
                set_position({x, y});
                //_transformComponent->setPosition(x, y);
        }

        const b2Transform &RigidbodyComponent::get_transform() const
        {
                return _body->GetTransform();
        }

        void RigidbodyComponent::add_rotation(Angle angle)
        {
                set_rotation(_body->GetAngle() + angle);
                //if (!_transformComponent)
                //        return;

                //_transformComponent->rotate(angle);
        }
        void RigidbodyComponent::set_rotation(Angle angle)
        {
                _body->SetTransform(_body->GetPosition(), angle);
                //if (!_transformComponent)
                //        return;

                //_transformComponent->setRotation(angle);
        }

        //void RigidbodyComponent::update_velocity(ecs::Interval deltaTime)
        //        const sf::Vector2f &gravity,
        //{
        //        _acceleration.first = _forces.first * std::sin(_rotation);
        //        _acceleration.second = _forces.second * std::cos(_rotation);

        //        _velocity.first += _acceleration.first * deltaTime;
        //        _velocity.second += _acceleration.second * deltaTime;
        //        /*auto objectGravity = gravity * _gravityScale;
        //                auto draggedVelocity = _velocity * _drag;
        //                _velocity = draggedVelocity + (objectGravity + _forces * _massInv)
        //                                              * static_cast<float>(deltaTime);

        //                _angularVelocity = _angularVelocity * _angularDrag
        //                                   + _torque * _massInv * deltaTime;

        //                _forces = {0., 0.};
        //                _torque = 0.;*/
        //}

        //void RigidbodyComponent::update_position(ecs::Interval deltaTime)
        //{
        //        auto position = _transformComponent->getPosition();
        //        position += _velocity * static_cast<float>(deltaTime);
        //        set_position(position);

        //        auto angle = _transformComponent->getRotation();
        //        angle += _angularVelocity * deltaTime;
        //        set_rotation(angle);
        //}

        //void RigidbodyComponent::update(ecs::Interval deltaTime)
        //{
        //        update_velocity({SpaceGravity, SpaceGravity}, deltaTime);
        //        update_position(deltaTime);
        //}

}
