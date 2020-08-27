//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <stdexcept>

#include <ComponentManager.hpp>
#include <IEntity.hpp>
#include <util.hpp>

#include "../Core/Scene.hpp"
#include "../GameObject/GameObject.hpp"
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
                ecs::replace_pointer(m_transformComponent,
                                     get_owner()->get_component<TransformComponent>());
                if (m_transformComponent == nullptr)
                        throw std::invalid_argument(
                                "A entity cannot have a rigidbogy without having a "
                                "transform");

                auto &scene =
                        static_cast<ecs::NonOwningPointer<GameObject>>(get_owner())->get_scene();
                ecs::replace_pointer(m_space, &scene.get_world());
                cpSpaceAddBody(m_space, m_body.get());
        }

        void RigidbodyComponent::move(const Vector<2> &offsets) { move(offsets.x, offsets.y); }
        void RigidbodyComponent::move(Coordinate x, Coordinate y)
        {
                auto old_position = get_position();
                set_position({ x + old_position.x, y + old_position.y });
        }

        void RigidbodyComponent::set_position(const Vector<2> &coordinates)
        {
                cpBodySetPosition(m_body.get(), coordinates);
                cpSpaceReindexShapesForBody(m_space, m_body.get());
        }
        void RigidbodyComponent::set_position(Coordinate x, Coordinate y)
        {
                set_position({ x, y });
        }

        const cpTransform &RigidbodyComponent::get_transform() const { return m_body->transform; }

        void RigidbodyComponent::add_rotation(Angle angle)
        {
                cpBodySetAngle(m_body.get(), get_rotation() + angle);
        }
        void RigidbodyComponent::set_rotation(Angle angle) { cpBodySetAngle(m_body.get(), angle); }

        void RigidbodyComponent::update(ecs::Interval deltaTime)
        {
                cpSpaceReindexShapesForBody(m_space, m_body.get());
        }

        Vector<2> RigidbodyComponent::get_position() const
        {
                auto vec = cpBodyGetPosition(m_body.get());
                return { vec.x, vec.y };
        }

        Angle RigidbodyComponent::get_rotation() const { return cpBodyGetAngle(m_body.get()); }

        Vector<2> RigidbodyComponent::get_velocity() const
        {
                auto vec = cpBodyGetVelocity(m_body.get());
                return { vec.x, vec.y };
        }

}    // namespace star
