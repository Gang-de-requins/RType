#ifndef ENTITY_TEMPLATE_HPP
#define ENTITY_TEMPLATE_HPP

#include "GameEngine.hpp"

namespace server {
    class EntityTemplate {
        public:
            EntityTemplate();
            ~EntityTemplate();

            void player(ecs::World &world, const std::string &tag, int x, int y);
            void playerBullet(ecs::World &world, const std::string &tag, int x, int y);
            void enemy(ecs::World &world, int x, int y);
            void enemyBullet(ecs::World &world, const std::string &tag, int x, int y);

        private:
    };
}

#endif /* ENTITY_TEMPLATE_HPP */
