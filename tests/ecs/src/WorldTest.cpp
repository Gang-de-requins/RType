#include <gtest/gtest.h>
#include "StdoutCapture.hpp"
#include "StderrCapture.hpp"
#include "Core.hpp"

TEST(WorldTest, CreateWorld) {
    StdoutCaptureTest stdoutCaptureTest;

    stdoutCaptureTest.capture();
    ecs::World world;

    std::string expected = "New world created.\n";
    std::string actual = stdoutCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, CreateEntity) {
    ecs::World world;

    EntityID entity = world.createEntity();

    ASSERT_EQ(entity, 0);
}

TEST(WorldTest, AddSystem) {
    ecs::World world;

    world.addSystem<ecs::MovementSystem>();

    std::shared_ptr<ecs::MovementSystem> movementSystem = world.getSystem<ecs::MovementSystem>();

    ASSERT_EQ(world.getSystem<ecs::MovementSystem>(), movementSystem);
}

TEST(WorldTest, AddSystemTwice) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.addSystem<ecs::MovementSystem>();
    world.addSystem<ecs::MovementSystem>();

    std::string expected = "Added system more than once.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, RemoveInvalidSystem) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.removeComponentFromSystem<ecs::MovementSystem, ecs::Position>();

    std::string expected = "System not registered.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, RemoveInvalidComponent) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.addSystem<ecs::MovementSystem>();
    world.removeComponentFromSystem<ecs::MovementSystem, ecs::Position>();

    std::string expected = "Component type not registered.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, GetInvalidSystem) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.getSystem<ecs::MovementSystem>();

    std::string expected = "System not registered.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, AddComponentToInvalidSystem) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.addComponentToSystem<ecs::MovementSystem, ecs::Position>();

    std::string expected = "System not registered.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}

TEST(WorldTest, UpdateInvalidComponentToEntity) {
    ecs::World world;
    StderrCaptureTest stderrCaptureTest;

    stderrCaptureTest.capture();
    world.updateComponentToEntity<ecs::Position>(0, ecs::Position());

    std::string expected = "Component type not registered.\n";
    std::string actual = stderrCaptureTest.get();

    EXPECT_EQ(actual, expected);
}
