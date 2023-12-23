/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Parallax
*/

#ifndef PARALLAX_COMPONENT_HPP
#define PARALLAX_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Parallax
     * @brief Parallax component
     * 
     * @details
     * This component is used to enable and manage parallax effect for an entity. Parallax effects create an illusion of depth in 2D scenes by moving background layers at different speeds.
     * 
     * @var Parallax::check
     * A boolean that indicates whether the parallax effect is applied to the entity. If true, the entity will participate in the parallax effect.
     */
    struct Parallax {
        bool check;
    };
}

#endif /* PARALLAX_COMPONENT_HPP */
