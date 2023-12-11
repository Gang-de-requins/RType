#include <gtest/gtest.h>
#include "StdoutCapture.hpp"
#include "StderrCapture.hpp"
#include "Core.hpp"

TEST(ComponentsVectorTest, AddComponent) {
    ComponentVector<ecs::Position> componentsVector;

    EntityID entity = 0;
    ecs::Position position { 0, 0 };

    componentsVector.addComponent(entity, position);

    ASSERT_EQ(componentsVector.getVector().size(), 1);
}

TEST(ComponentsVectorTest, AddComponentTwice) {
    ComponentVector<ecs::Position> componentsVector;
    StderrCaptureTest stderrCaptureTest;

    EntityID entity = 0;
    ecs::Position position { 0, 0 };

    stderrCaptureTest.capture();
    componentsVector.addComponent(entity, position);
    componentsVector.addComponent(entity, position);

    std::string expected = "Component type added to same entity more than once.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(ComponentsVectorTest, UpdateComponent) {
    ComponentVector<ecs::Position> componentsVector;

    EntityID entity = 0;
    ecs::Position position { 0, 0 };

    componentsVector.addComponent(entity, position);

    ecs::Position newPosition { 1, 1 };
    componentsVector.updateComponent(entity, newPosition);

    ASSERT_EQ(componentsVector.getVector()[0].x, 1);
    ASSERT_EQ(componentsVector.getVector()[0].y, 1);
}

TEST(ComponentsVectorTest, UpdateInvalidComponent) {
    ComponentVector<ecs::Position> componentsVector;
    StderrCaptureTest stderrCaptureTest;

    EntityID entity = 0;
    ecs::Position position { 0, 0 };

    stderrCaptureTest.capture();
    componentsVector.updateComponent(entity, position);

    std::string expected = "Attempting to update component that does not exist.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(ComponentsVectorTest, RemoveComponent) {
    ComponentVector<ecs::Position> componentsVector;

    EntityID entity = 0;
    ecs::Position position { 0, 0 };

    componentsVector.addComponent(entity, position);
    componentsVector.removeComponent(entity);

    ASSERT_EQ(componentsVector.getVector().size(), 0);
}

TEST(ComponentsVectorTest, RemoveInvalidComponent) {
    ComponentVector<ecs::Position> componentsVector;
    StderrCaptureTest stderrCaptureTest;

    EntityID entity = 0;

    stderrCaptureTest.capture();
    componentsVector.removeComponent(entity);

    std::string expected = "Attempting to remove component that does not exist.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

// TEST(ComponentsVectorTest, GetVector) {
//     ComponentVector<ecs::Position> componentsVector;

//     EntityID entity = 0;
//     ecs::Position position { 0, 0 };

//     componentsVector.addComponent(entity, position);

//     ASSERT_EQ(componentsVector.getVector().size(), 1);
// }

// TEST(ComponentsVectorTest, GetComponent) {
//     ComponentVector<ecs::Position> componentsVector;

//     EntityID entity = 0;
//     ecs::Position position { 0, 0 };

//     componentsVector.addComponent(entity, position);

//     ASSERT_EQ(componentsVector.getComponent(entity).x, 0);
//     ASSERT_EQ(componentsVector.getComponent(entity).y, 0);
// }

// TEST(ComponentsVectorTest, GetComponentInvalid) {
//     try {
//         ComponentVector<ecs::Position> componentsVector;

//         EntityID entity = 0;
//         ecs::Position position { 0, 0 };

//         componentsVector.addComponent(entity, position);

//         componentsVector.getComponent(1);
//     } catch (std::out_of_range &e) {
//         ASSERT_STREQ(e.what(), "Attempting to retrieve component that does not exist.");
//     }
// }

// TEST(ComponentsVectorTest, EntityDestroyed) {
//     ComponentVector<ecs::Position> componentsVector;

//     EntityID entity = 0;
//     ecs::Position position { 0, 0 };

//     componentsVector.addComponent(entity, position);
//     componentsVector.entityDestroyed(entity);

//     ASSERT_EQ(componentsVector.getVector().size(), 0);
// }

// TEST(ComponentsVectorTest, CreateEmptyClone) {
//     ComponentVector<ecs::Position> componentsVector;

//     std::shared_ptr<IComponentVector> newVector = componentsVector.createEmptyClone();

//     ASSERT_EQ(newVector->getVector().size(), 0);
// }
