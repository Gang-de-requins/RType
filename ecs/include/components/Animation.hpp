#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <chrono>
#include "Rectangle.hpp"

namespace ecs {

    /**
     * @struct Animation
     * @brief Animation component
     * 
     * @details
     * This component is used to store the animation details of an entity.
     * 
     * @var Animation::offset
     * Rectangle defining the offset of the animation on the sprite sheet.
     * 
     * @var Animation::frames
     * Total number of frames in the animation.
     * 
     * @var Animation::currentFrame
     * Index of the current frame of the animation.
     * 
     * @var Animation::frameTime
     * Duration in milliseconds that each frame should last.
     * 
     * @var Animation::lastUpdate
     * The last time point when the animation was updated.
     */
    struct Animation {
        Rectangle offset;
        int frames;
        int currentFrame;
        int frameTime;
        std::chrono::steady_clock::time_point lastUpdate;
    };
}

#endif /* ANIMATION_COMPONENT_HPP */
