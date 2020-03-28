#include "Entity.hpp"

bool Entity::intersectsWith(const Entity &entity) const
{
    return getCollisionShape().intersects(entity.getCollisionShape());
}
