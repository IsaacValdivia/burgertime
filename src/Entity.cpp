#include "Entity.hpp"

Entity::Entity() : acc_delta_t(0) {}

bool Entity::intersectsWith(const Entity &entity) const {
    return getCollisionShape().intersects(entity.getCollisionShape());
}