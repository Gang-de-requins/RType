#include "systems/Music.hpp"

namespace ecs {
    void MusicSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Music> &musics = archetype->getComponentVector<Music>();

            UpdateMusicStream(musics[0].music);
        }
    }
}
