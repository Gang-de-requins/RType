#ifndef SUBMIT_SYSTEM_HPP_
#define SUBMIT_SYSTEM_HPP_

#include <vector>
#include <algorithm>
// #include "raylib.h"
#include "components/Submit.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

namespace ecs {
    class SubmitSystem : public ISystem {
        public:

            void update(SceneManager &sceneManager) override;
    };
}

#endif /* SUBMIT_SYSTEM_HPP_ */