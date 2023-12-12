#include <gtest/gtest.h>
#include "CustomExceptions.hpp"

TEST(CustomExceptionsTest, DuplicateComponentTypeException) {
    std::string expected = "Duplicate component type added to entity.";
    std::string actual = "";

    try {
        throw ecs::DuplicateComponentTypeException("Duplicate component type added to entity.");
    } catch (const ecs::DuplicateComponentTypeException &e) {
        actual = e.what();
    }

    EXPECT_EQ(actual, expected);
}
