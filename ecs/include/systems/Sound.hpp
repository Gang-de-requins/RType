#ifndef SOUND_SYSTEM_HPP_
#define SOUND_SYSTEM_HPP_

#include <vector>
#include "raylib.h"
#include "components/Sound.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SoundSystem : public ISystem {
        public:
            void update(World &world) override;
    };
}

#endif /* !SOUND_HPP_ */
