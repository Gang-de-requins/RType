#include <gtest/gtest.h>
#include "Core.hpp"

TEST(ArchetypeTest, CreateArchetype) {
    ecs::Archetype archetype(0);

    ASSERT_EQ(archetype.getNumEntities(), 0);
}
