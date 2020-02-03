//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <ComponentManager.hpp>
#include <IEntity.hpp>

#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"
#include "../Core/Scene.hpp"
#include "../Util/Vector.hpp"


namespace star
{

        RigidbodyComponent::RigidbodyComponent(Scene &scene)
        {
                _bodyDef.type = b2BodyType::b2_dynamicBody;
                _bodyDef.position.SetZero();

                auto *bodyNonConstPointer = const_cast<b2Body **>(&_body);
                *bodyNonConstPointer = scene._world.CreateBody(&_bodyDef);

                _dynamicBox.SetAsBox(1., 1.);

                _fixtureDef.shape = &_dynamicBox;
                _fixtureDef.density = 1.;
                _fixtureDef.friction = 0.3;

                _body->CreateFixture(&_fixtureDef);
        }

        void RigidbodyComponent::setup()
        {
                auto *transformNonConstPointer = const_cast<TransformComponent **>(&_transformComponent);
                *transformNonConstPointer = get_owner()->get_component<TransformComponent>();
                //_massInv = 1 / _mass;
        }

        template <RIGIDBODY_FORCE_MODE mode>
        void RigidbodyComponent::add_force(Vector<2> force)
        {
                if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                {
                        _body->ApplyLinearImpulseToCenter(force);
                }
                else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                {
                        _body->SetLinearVelocity(_body->GetLinearVelocity() + force);
                }
                else if constexpr (mode == RIGIDBODY_FORCE_MODE::ACCELERATION)
                {
                }
                else if constexpr (mode == RIGIDBODY_FORCE_MODE::FORCE)
                {
                        _body->ApplyForceToCenter(force);
                }
                //add_force<mode>(force.x, force.y);
        }
        template <RIGIDBODY_FORCE_MODE mode>
        void RigidbodyComponent::add_force(float x, float y)
        {
                add_force({x, y});
                //if constexpr (mode == RIGIDBODY_FORCE_MODE::IMPULSE)
                //{
                //        _forces.x += x;
                //        _forces.y += y;
                //}
                //else if constexpr (mode == RIGIDBODY_FORCE_MODE::VELOCITYCHANGE)
                //{
                //        _velocity.x += x;
                //        _velocity.y += y;
                //}
        }

        void RigidbodyComponent::move(Vector<2> offsets)
        {
                move(offsets.x, offsets.y);
        }
        void RigidbodyComponent::move(float x, float y)
        {
                if (!_transformComponent)
                        return;

                _transformComponent->move(x, y);
        }

        void RigidbodyComponent::set_position(Vector<2> coordinates)
        {
                set_position(coordinates.x, coordinates.y);
        }
        void RigidbodyComponent::set_position(float x, float y)
        {
                if (!_transformComponent)
                        return;

                _transformComponent->setPosition(x, y);
        }

        void RigidbodyComponent::add_rotation(float angle)
        {
                if (!_transformComponent)
                        return;

                _transformComponent->rotate(angle);
        }
        void RigidbodyComponent::set_rotation(float angle)
        {
                if (!_transformComponent)
                        return;

                _transformComponent->setRotation(angle);
        }

        void RigidbodyComponent::update_velocity(ecs::Interval deltaTime)
                //const sf::Vector2f &gravity,
        {
                //_acceleration.first = _forces.first * std::sin(_rotation);
                //_acceleration.second = _forces.second * std::cos(_rotation);

                //_velocity.first += _acceleration.first * deltaTime;
                //_velocity.second += _acceleration.second * deltaTime;
                /*auto objectGravity = gravity * _gravityScale;
                        auto draggedVelocity = _velocity * _drag;
                        _velocity = draggedVelocity + (objectGravity + _forces * _massInv)
                                                      * static_cast<float>(deltaTime);

                        _angularVelocity = _angularVelocity * _angularDrag
                                           + _torque * _massInv * deltaTime;

                        _forces = {0., 0.};
                        _torque = 0.;*/
        }

        void RigidbodyComponent::update_position(ecs::Interval deltaTime)
        {
                //auto position = _transformComponent->getPosition();
                //position += _velocity * static_cast<float>(deltaTime);
                //set_position(position);

                //auto angle = _transformComponent->getRotation();
                //angle += _angularVelocity * deltaTime;
                //set_rotation(angle);
        }

        void RigidbodyComponent::update(ecs::Interval deltaTime)
        {
                //update_velocity({SpaceGravity, SpaceGravity}, deltaTime);
                //update_position(deltaTime);
        }

}
