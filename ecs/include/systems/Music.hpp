#ifndef MUSIC_SYSTEM_HPP
#define MUSIC_SYSTEM_HPP

#include <memory>
#include <vector>
#include "components/Music.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class MusicSystem : public System {
        public:
            void update(World &world) override;
    };
}

#endif /* MUSIC_SYSTEM_HPP */
