#ifndef SOUND_COMPONENT_HPP_
#define SOUND_COMPONENT_HPP_

#include <string>

namespace ecs {

    /**
     * @struct Sound
     * @brief Sound component
     * 
     * @details
     * This component is used to associate a sound effect with an entity. It stores the path to the sound file, which can be used for playing sound effects in the game or application.
     * 
     * @var Sound::path
     * The file path to the sound resource. This path is used to locate and play the associated sound file.
     */
    struct Sound {
        std::string path;
    };
}

#endif /* SOUND_COMPONENT_HPP_ */
