#ifndef MUSIC_COMPONENT_HPP
#define MUSIC_COMPONENT_HPP

#include <string>

namespace ecs {

    /**
     * @struct Music
     * @brief Music component
     * 
     * @details
     * This component is used to associate a music file with an entity. It stores the path to the music file, allowing for easy music management and playback in the game or application.
     * 
     * @var Music::path
     * The file path to the music resource. This path is used to locate and play the associated music file.
     */
    struct Music {
        std::string path;
    };
}

#endif /* MUSIC_COMPONENT_HPP */
