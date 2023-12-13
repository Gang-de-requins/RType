#ifndef MUSIC_SYSTEM_HPP
#define MUSIC_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Music.hpp"
#include "ISystem.hpp"

namespace ecs {
    class MusicSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}

#endif /* MUSIC_SYSTEM_HPP */
