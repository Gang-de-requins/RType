#ifndef CLICKABLE_SYSTEM_HPP_
#define CLICKABLE_SYSTEM_HPP_

    #include <vector>
    #include <algorithm>
    #include "components/Clickable.hpp"
    #include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    class Clickable : public ISystem {

        public:
            void update(SceneManager &sceneManager) override;
    };
}

#endif /* !CLICKABLE_HPP_ */
