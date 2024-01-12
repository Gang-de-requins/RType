#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include <string>

namespace ecs {

    /**
     * @struct Text
     * @brief Text component
     * 
     * @details
     * This component is used to store textual content for an entity. It can be used for displaying labels, descriptions, or any other textual information associated with an entity in the game or application.
     * 
     * @var Text::content
     * The textual content to be displayed or associated with the entity.
     */
    struct Text {
        std::string content;
    };
}

#endif /* TEXT_COMPONENT_HPP */
