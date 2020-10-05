//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <stdexcept>

#include <ComponentManager.hpp>
#include <IEntity.hpp>
#include <util.hpp>

#include "../Core/Scene.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Log/LogSystem.hpp"
#include "../Util/Vector.hpp"
#include "RigidbodyComponent.hpp"
#include "TransformComponent.hpp"

namespace star
{
        RigidbodyComponent::RigidbodyComponent(RIGIDBODY_TYPE type) : m_body{ cpBodyNew(1, 1) }
        {
                cpBodySetType(m_body.get(), static_cast<cpBodyType>(type));
        }

        void RigidbodyComponent::setup()
        {
                auto &scene =
                        static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                ecs::replace_pointer(m_space, &scene.get_world());
                cpSpaceAddBody(m_space, m_body.get());
        }

        void RigidbodyComponent::set_position(Coordinate x, Coordinate y)
        {
                set_position({ x, y });
        }
        void RigidbodyComponent::set_position(const Vector<2> &coordinates)
        {
                cpBodySetPosition(
                        m_body.get(),
                        coordinates + cpTransformVect(get_transform(), { m_offset.x, m_offset.y }));
                refresh();
        }

        const cpTransform &RigidbodyComponent::get_transform() const { return m_body->transform; }

        void RigidbodyComponent::set_rotation(Angle angle)
        {
                cpBodySetAngle(m_body.get(), angle);
                refresh();
        }

        void RigidbodyComponent::update(::ecs::Interval deltaTime)
        {
                const auto vec = get_position();
                const auto cog = get_center_of_gravity();
                spdlog::info("x:{} y:{}; x:{} y:{}", vec.x, vec.y, cog.x, cog.y);
        }

        Vector<2> RigidbodyComponent::get_position() const
        {
                auto vec = cpBodyLocalToWorld(m_body.get(), -m_offset);
                return { vec.x, vec.y };
        }

        Angle RigidbodyComponent::get_rotation() const { return cpBodyGetAngle(m_body.get()); }

        Vector<2> RigidbodyComponent::get_velocity() const
        {
                auto vec = cpBodyGetVelocity(m_body.get());
                return { vec.x, vec.y };
        }

        void RigidbodyComponent::refresh() { cpSpaceReindexShapesForBody(m_space, m_body.get()); }

        Vector<2> RigidbodyComponent::get_center_of_gravity() const
        {
                auto vec = cpBodyLocalToWorld(m_body.get(), cpBodyGetCenterOfGravity(m_body.get()));
                return Vector<2>{ vec.y, vec.y };
        }

        void RigidbodyComponent::set_center_of_gravity(const Vector<2> &cog)
        {
                cpBodySetCenterOfGravity(m_body.get(), cpBodyWorldToLocal(m_body.get(), cog));
        }

        void RigidbodyComponent::set_moment_of_inertia(Force inertia)
        {
                cpBodySetMoment(m_body.get(), inertia);
        }

        void RigidbodyComponent::set_mass(Weight mass) { cpBodySetMass(m_body.get(), mass); }

}    // namespace star
