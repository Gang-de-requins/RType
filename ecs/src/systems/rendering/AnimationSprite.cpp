#include "systems/rendering/AnimationSprite.hpp"
#include "World.hpp"

namespace ecs {
    void RenderAnimationSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<EntityID> &entityIds = archetype->getEntities();
            std::vector<Animation> &animations = archetype->getComponentVector<Animation>();
            std::vector<Sprite> &sprites = archetype->getComponentVector<Sprite>();

            for (std::size_t i = 0; i < animations.size(); ++i) {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - animations[i].chrono).count() < animations[i].elapsedTime)
                    continue;

                if (animations[i].currentFrame >= animations[i].frames)
                    animations[i].currentFrame = 0;
                else
                    animations[i].currentFrame++;

                ecs::Sprite newSprite = sprites[i];
                world.updateComponentToEntity(entityIds[i], ecs::Sprite {
                    newSprite.texture,
                    { .x = animations[i].offset.width * animations[i].currentFrame, .y = animations[i].offset.height * animations[i].currentFrame, .width = newSprite.source.width, .height = newSprite.source.height },
                    newSprite.origin
                });

                animations[i].chrono = std::chrono::steady_clock::now();
            }
        }
    }
}
