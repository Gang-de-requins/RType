#ifndef TEXT_SYSTEM_HPP
#define TEXT_SYSTEM_HPP

#include <memory>
#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "components/Color.hpp"
#include "components/FontSize.hpp"
#include "Archetype.hpp"
#include "System.hpp"

namespace ecs {
    class RenderTextSystem : public System {
        public:
            void update() override;
    };
}

#endif /* TEXT_SYSTEM_HPP */
