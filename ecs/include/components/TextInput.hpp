#ifndef TEXTINPUT_COMPONENT_HPP_
#define TEXTINPUT_COMPONENT_HPP_

#include <string>
#include "Position.hpp"

namespace ecs {

    /**
     * @struct TextInput
     * @brief TextInput component
     * 
     * @details
     * This component is used to handle text input functionality for an entity. It can be used to store and manage user-entered text, such as in text fields or forms within the game or application.
     * 
     * @var TextInput::content
     * The string that stores the current text input content. It represents the text entered by the user.
     */
    struct TextInput {
        std::size_t maxLength;
        Position textPosition;
        std::string content = "Player1";
        bool isFocused = false;
        int counter = 0;
    };

}

#endif /* TEXTINPUT_COMPONENT_HPP_ */
