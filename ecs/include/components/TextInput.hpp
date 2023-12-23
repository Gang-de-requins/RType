#ifndef TEXTINPUT_COMPONENT_HPP_
#define TEXTINPUT_COMPONENT_HPP_

#include <string>

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
        std::string content;
    };

}

#endif /* TEXTINPUT_COMPONENT_HPP_ */
