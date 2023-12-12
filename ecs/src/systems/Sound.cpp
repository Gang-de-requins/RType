#include "systems/Sound.hpp"

namespace ecs {
    void SoundSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Sound> &Sounds = archetype->getComponentVector<Sound>();

            PlaySound(Sounds[0].sound);
        }
    }
}
