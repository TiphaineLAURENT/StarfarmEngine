//
// Created by Tiphaine LAURENT on 09/08/2019.
//

#include <cassert>

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
        RigidbodyComponent::RigidbodyComponent()
                : m_body{ cpBodyNew(1, 1) }, m_shape{
                          cpBoxShapeNew(m_body.get(), 1, 1, 1)
                  }
        {
                cpBodySetType(m_body.get(), cpBodyType::CP_BODY_TYPE_DYNAMIC);
        }

        void RigidbodyComponent::setup()
        {
                ecs::replace_pointer(
                        m_transformComponent,
                        get_owner()->get_component<TransformComponent>());
                assert(("A entity cannot have a rigidbogy without having a "
                        "transform",
                        m_transformComponent != nullptr));

                auto &scene = static_cast<ecs::NonOwningPointer<GameObject>>(
                                      get_owner())
                                      ->get_scene();
                ecs::replace_pointer(m_space, &scene.get_world());
        }

        void RigidbodyComponent::move(const Vector<2> &offsets)
        {
                move(offsets.x, offsets.y);
        }
        void RigidbodyComponent::move(Coordinate x, Coordinate y)
        {
                auto old_position = get_position();
                set_position({ x + old_position.x, y + old_position.y });
        }

        void RigidbodyComponent::set_position(const Vector<2> &coordinates)
        {
                cpBodySetPosition(m_body.get(), coordinates);
        }
        void RigidbodyComponent::set_position(Coordinate x, Coordinate y)
        {
                set_position({ x, y });
        }

        const cpTransform &RigidbodyComponent::get_transform() const
        {
                return m_body->transform;
        }

        void RigidbodyComponent::add_rotation(Angle angle)
        {
                cpBodySetAngle(m_body.get(), get_rotation() + angle);
        }
        void RigidbodyComponent::set_rotation(Angle angle)
        {
                cpBodySetAngle(m_body.get(), angle);
        }

        void RigidbodyComponent::update(ecs::Interval deltaTime)
        {
                cpSpaceReindexShapesForBody(m_space, m_body.get());
        }

        Vector<2> RigidbodyComponent::get_position() const
        {
                auto vec = cpBodyGetPosition(m_body.get());
                return { vec.x, vec.y };
        }

        Angle RigidbodyComponent::get_rotation() const
        {
                return cpBodyGetAngle(m_body.get());
        }

}   // namespace star
