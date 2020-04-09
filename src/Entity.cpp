#include "Entity.hpp"

Entity::Entity() : acc_delta_t(0) {}

bool Entity::intersects_with(const Entity &entity) const {
    return get_collision_shape().intersects(entity.get_collision_shape());
}