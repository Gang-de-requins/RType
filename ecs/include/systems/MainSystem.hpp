#ifndef MAIN_SYSTEM_HPP
#define MAIN_SYSTEM_HPP

#include <vector>
#include <memory>
#include "ISystem.hpp"

namespace ecs {
    class MainSystem : public ISystem {
        protected:
            std::vector<std::shared_ptr<ISystem>> m_systems;

        public:
            virtual void update(SceneManager &sceneManager) = 0;
        };
}

#endif /* MAIN_SYSTEM_HPP */
