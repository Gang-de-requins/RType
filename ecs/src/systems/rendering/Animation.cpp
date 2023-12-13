#include "systems/rendering/Animation.hpp"
#include "World.hpp"

namespace ecs {
    void AnimationSystem::update(World &world) {
        auto entities = world.view<Animation, Sprite>();

        for (auto entity : entities) {
            auto &animation = world.get<Animation>(*entity);
            auto &sprite = world.get<Sprite>(*entity);

            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - animation.lastUpdate).count() >= animation.frameTime) {
                animation.lastUpdate = std::chrono::steady_clock::now();
                animation.currentFrame = (animation.currentFrame + 1) % animation.frames;
                sprite.source.x = animation.offset.width * animation.currentFrame;
                sprite.source.y = animation.offset.height * animation.currentFrame;
            }
        }
    }
}
