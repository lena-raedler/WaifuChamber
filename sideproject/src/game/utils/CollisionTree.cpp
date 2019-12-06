//
// Created by auki on 06.12.19.
//
//TODO
#include "CollisionTree.h"

{
using bounding_box_t = std::pair<vec_t, vec_t>;
explicit CollisionTree(const particle_field_t& particles)
{
    if(particles.size() <= MAX_LEAF_ELEMS) {
        m_particles = particles;
        return;
    }

    const auto [minBound, maxBound] = getBoundingBox(particles);

    const auto xHalf = minBound.x + (maxBound.x - minBound.x) / 2;
    const auto yHalf = minBound.y + (maxBound.y - minBound.y) / 2;

    bounding_box_t subBoundingBoxes[4];
    subBoundingBoxes[0] = {minBound, {xHalf, yHalf}};
    subBoundingBoxes[1] = {{xHalf, minBound.y}, {maxBound.x, yHalf}};
    subBoundingBoxes[2] = {{minBound.x, yHalf}, {xHalf, maxBound.y}};
    subBoundingBoxes[3] = {{xHalf, yHalf}, maxBound};

    particle_field_t subParticles[4];

    for(const auto& movable: movables) {
        const Movable& object = *movable;
        for(auto i = 0; i < 4; ++i) {
            if(isInsideBox(particle, subBoundingBoxes[i])) {
                children[i].push_back(particle);
                break;
            }
        }
    }

    particle_field_t childrenCenterOfMass;

    for(auto i = 0; i < 4; ++i) {
        if(!subParticles[i].empty()) {
            m_subTree[i] = std::make_unique<Quadtree>(subParticles[i]);
            childrenCenterOfMass.push_back(Particle{m_subTree[i]->m_centerOfMass, {0, 0}, m_subTree[i]->m_totalMass});
        }
    }

    const auto centerOfMass = calcCenterOfMass(childrenCenterOfMass);
    m_centerOfMass = centerOfMass.first;
    m_totalMass = centerOfMass.second;
}


CollisionTree::bounding_box_t getBoundingBox(const particle_field_t &particles) {
    constexpr auto MIN_VEC = vec_t{std::numeric_limits<value_t>::max(), std::numeric_limits<value_t>::max()};
    constexpr auto MAX_VEC = vec_t{std::numeric_limits<value_t>::lowest(), std::numeric_limits<value_t>::lowest()};

    auto min = MIN_VEC;
    auto max = MAX_VEC;

    for (const auto movablePtr: movables) {
        const Movable& object = *movablePtr;
        const auto minX = std::min(min.x, object.position.x);
        const auto minY = std::min(min.y, object.position.y);

        const auto maxX = std::max(max.x, object.position.x);
        const auto maxY = std::max(max.y, object.position.y);

        min = {minX, minY};
        max = {maxX, maxY};
    }

    return {min, max};
}
CollisionTree::bool isInsideBox(const vec_t& position, const bounding_box_t& boundingBox)
{
    if(position.x >= boundingBox.first.x && position.x <= boundingBox.second.x) {
        if(position.y >= boundingBox.first.y && position.y <= boundingBox.second.y)
            return true;
    }

    return false;
}


}