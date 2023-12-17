#include "systems/rendering/Animation.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void AnimationSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Animation, Sprite>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &animation = sceneManager.get<Animation>(*entity);
            auto &sprite = sceneManager.get<Sprite>(*entity);

            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - animation.lastUpdate).count() >= animation.frameTime) {
                animation.lastUpdate = std::chrono::steady_clock::now();
                animation.currentFrame = (animation.currentFrame + 1) % animation.frames;
                sprite.source.x = animation.offset.width * animation.currentFrame;
                sprite.source.y = animation.offset.height * animation.currentFrame;
            }
        }
    }
}
