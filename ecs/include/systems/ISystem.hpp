#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

namespace ecs {
    class SceneManager;

	class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void update(SceneManager &sceneManager) = 0;
    };
}

#endif /* ISYSTEM_HPP */
