#ifndef SOUND_SYSTEM_HPP_
#define SOUND_SYSTEM_HPP_

#include <memory>
#include <vector>
#include "components/Sound.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class SoundSystem : public System {
        public:
            void update(World &world) override;
    };
}

#endif /* !SOUND_HPP_ */
