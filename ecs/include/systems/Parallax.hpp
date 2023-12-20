/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Parallax
*/

#ifndef PARALLAX_SYSTEM_HPP_
#define PARALLAX_SYSTEM_HPP_

#include "ISystem.hpp"
#include "components/Parallax.hpp"
#include "components/Position.hpp"

namespace ecs {
    class SceneManager;

    class ParallaxSystem : public ISystem {
        public:

            void update(SceneManager &sceneManager) override;
    };
}

#endif /* !PARALLAX_SYSTEM_HPP_ */
