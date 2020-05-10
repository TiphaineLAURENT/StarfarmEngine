//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <ComponentManager.hpp>
#include <IEntity.hpp>
#include <util.hpp>

#include "../GameObject/GameObject.hpp"
#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"

namespace star
{
    void RigidbodyComponent::setup()
    {
        ecs::replace_pointer(_transformComponent,
                             get_owner()->get_component<TransformComponent>());
        assert(("A entity cannot have a rigidbogy without having a transform",
                _transformComponent != nullptr));

        auto &scene = static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())
                          ->get_scene();
        //_massInv = 1 / _mass;
    }

    void RigidbodyComponent::apply_force(Force fx,
                                         Force fy,
                                         Coordinate x,
                                         Coordinate y)
    {
        apply_force({ fx, fy }, { x, y });
    }
    void RigidbodyComponent::apply_force(const Vector2D &force,
                                         const Vector2D &point)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _force += force;
        _torque += b2Cross(point - _sweep.c, force);
    }
    void RigidbodyComponent::apply_force_to_center(Force fx, Force fy)
    {
        apply_force_to_center({ fx, fy });
    }
    void RigidbodyComponent::apply_force_to_center(const Vector2D &force)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _force += force;
    }

    void RigidbodyComponent::apply_torque(Force torque)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _torque += torque;
    }

    void RigidbodyComponent::apply_linear_impulse(Force fx,
                                                  Force fy,
                                                  Coordinate x,
                                                  Coordinate y)
    {
        apply_linear_impulse({ fx, fy }, { x, y });
    }
    void RigidbodyComponent::apply_linear_impulse(const Vector2D &impulse,
                                                  const Vector2D &point)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _linearVelocity += _massInv * impulse;
        _angularVelocity += _inertiaInv * b2Cross(point - _sweep.c, impulse);
    }
    void RigidbodyComponent::apply_linear_impulse_to_center(Force fx, Force fy)
    {
        apply_linear_impulse_to_center({ fx, fy });
    }
    void
        RigidbodyComponent::apply_linear_impulse_to_center(const Vector2D &impulse)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _linearVelocity += _massInv * impulse;
    }

    void RigidbodyComponent::apply_angular_impulse(Force impulse)
    {
        if (_type != RIGIDBODY_TYPE::DYNAMIC)
        {
            return;
        }

        if (!_awake)
        {
            set_awake(true);
        }
        _angularVelocity += _inertiaInv * impulse;
    }

    void RigidbodyComponent::move(const Vector2D &offsets)
    {
        move(offsets.x, offsets.y);
    }
    void RigidbodyComponent::move(Coordinate x, Coordinate y)
    {
        _transformComponent->move(x, y);
    }

    void RigidbodyComponent::set_position(const Vector2D &coordinates)
    {
        set_position(coordinates.x, coordinates.y);
    }
    void RigidbodyComponent::set_position(Coordinate x, Coordinate y)
    {
        _transformComponent->setPosition(x, y);
    }

    void RigidbodyComponent::add_rotation(Angle angle)
    {
        _transformComponent->rotate(angle);
    }
    void RigidbodyComponent::set_rotation(Angle angle)
    {
        _transformComponent->setRotation(angle);
    }

    // void RigidbodyComponent::update_velocity(ecs::Interval deltaTime)
    //        const sf::Vector2f &gravity,
    //{
    //        _acceleration.first = _forces.first * std::sin(_rotation);
    //        _acceleration.second = _forces.second * std::cos(_rotation);

    //        _velocity.first += _acceleration.first * deltaTime;
    //        _velocity.second += _acceleration.second * deltaTime;
    //        /*auto objectGravity = gravity * _gravityScale;
    //                auto draggedVelocity = _velocity * _drag;
    //                _velocity = draggedVelocity + (objectGravity + _forces *
    //                _massInv)
    //                                              * static_cast<float>(deltaTime);

    //                _angularVelocity = _angularVelocity * _angularDrag
    //                                   + _torque * _massInv * deltaTime;

    //                _forces = {0., 0.};
    //                _torque = 0.;*/
    //}

    // void RigidbodyComponent::update_position(ecs::Interval deltaTime)
    //{
    //        auto position = _transformComponent->getPosition();
    //        position += _velocity * static_cast<float>(deltaTime);
    //        set_position(position);

    //        auto angle = _transformComponent->getRotation();
    //        angle += _angularVelocity * deltaTime;
    //        set_rotation(angle);
    //}

    // void RigidbodyComponent::update(ecs::Interval deltaTime)
    //{
    //        update_velocity({SpaceGravity, SpaceGravity}, deltaTime);
    //        update_position(deltaTime);
    //}

    TransformComponent &RigidbodyComponent::get_transform()
    {
        return *_transformComponent;
    }
    const TransformComponent &RigidbodyComponent::get_transform() const
    {
        return *_transformComponent;
    }

    void RigidbodyComponent::set_linear_velocity(const Vector2D &velocity)
    {
        if (_type == RIGIDBODY_TYPE::STATIC)
        {
            return;
        }

        if (b2Dot(velocity, velocity) > 0.0f)
        {
            set_awake(true);
        }

        _linearVelocity = velocity;
    }
    const Vector2D &RigidbodyComponent::get_linear_velocity() const
    {
        return _linearVelocity;
    }

    void RigidbodyComponent::set_angular_velocity(Speed velocity)
    {
        if (_type == RIGIDBODY_TYPE::STATIC)
        {
            return;
        }

        if (velocity * velocity > 0.f)
        {
            set_awake(true);
        }

        _angularVelocity = velocity;
    }
    const Speed &RigidbodyComponent::get_angular_velocity() const
    {
        return _angularVelocity;
    }

    const Weight &RigidbodyComponent::get_mass() const { return _mass; }

    Force RigidbodyComponent::calculate_inertia() const
    {
        return _inertia + _mass * b2Dot(_sweep.localCenter, _sweep.localCenter);
    }

    void RigidbodyComponent::set_type(RIGIDBODY_TYPE type) { _type = type; }
    const RIGIDBODY_TYPE &RigidbodyComponent::get_type() const { return _type; }

    void RigidbodyComponent::set_linear_damping(Force damping)
    {
        _linearDamping = damping;
    }
    const Force &RigidbodyComponent::get_linear_damping() const
    {
        return _linearDamping;
    }

    void RigidbodyComponent::set_angular_damping(Force damping)
    {
        _angularDamping = damping;
    }
    const Force &RigidbodyComponent::get_angular_damping() const
    {
        return _angularDamping;
    }

    void RigidbodyComponent::set_gravity_scale(float scale)
    {
        _gravityScale = scale;
    }
    const float &RigidbodyComponent::get_gravity_scale() const
    {
        return _gravityScale;
    }

    void RigidbodyComponent::set_awake(bool flag)
    {
        if (flag)
        {
            _awake = true;
            _sleepTime = 0.;
        }
        else
        {
            _awake = false;
            _sleepTime = 0.;
            _linearVelocity.SetZero();
            _angularVelocity = 0.;
            _force.SetZero();
            _torque = 0.;
        }
    }

    bool RigidbodyComponent::is_awake() const { return _awake; }

    bool RigidbodyComponent::has_fixed_rotation() const
    {
        return (_constraints & RIGIDBODY_CONSTRAINTS::FREEZE_ROTATION)
               == RIGIDBODY_CONSTRAINTS::FREEZE_ROTATION;
    }

    void RigidbodyComponent::allow_sleeping() { _allowSleep = true; }
    void RigidbodyComponent::disallow_sleeping() { _allowSleep = false; }

    bool RigidbodyComponent::is_sleeping_allowed() const { return _allowSleep; }

    std::vector<b2Fixture> &RigidbodyComponent::get_fixtures()
    {
        return _fixtures;
    }

    const std::vector<b2Fixture> &RigidbodyComponent::get_fixtures() const
    {
        return _fixtures;
    }

    std::vector<b2JointEdge> &RigidbodyComponent::get_joints() { return _joints; }

    const std::vector<b2JointEdge> &RigidbodyComponent::get_joints() const
    {
        return _joints;
    }

    std::vector<b2ContactEdge> &RigidbodyComponent::get_contacts()
    {
        return _contacts;
    }

    const std::vector<b2ContactEdge> &RigidbodyComponent::get_contacts() const
    {
        return _contacts;
    }

    void RigidbodyComponent::synchronize_transform()
    {
        _transformComponent->setRotation(_sweep.a);

        auto newPosition = _sweep.c - _sweep.a * _sweep.localCenter;
        _transformComponent->setPosition(newPosition.x, newPosition.y);
    }

    void RigidbodyComponent::advance(float alpha)
    {
        _sweep.Advance(alpha);
        _sweep.c = _sweep.c0;
        _sweep.a = _sweep.a0;

        _transformComponent->setRotation(_sweep.a);

        auto newPosition = _sweep.c - _sweep.a * _sweep.localCenter;
        _transformComponent->setPosition(newPosition.x, newPosition.y);
    }

}   // namespace star
