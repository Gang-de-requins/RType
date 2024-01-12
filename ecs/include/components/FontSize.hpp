#ifndef FONT_SIZE_COMPONENT_HPP
#define FONT_SIZE_COMPONENT_HPP

namespace ecs {

    /**
     * @struct FontSize
     * @brief Font Size component
     * 
     * @details
     * This component is used to store the font size for text rendering associated with an entity. It allows for flexible control over the text size in rendering operations.
     * 
     * @var FontSize::size
     * The size of the font. This value determines how large the text appears when rendered.
     */
    struct FontSize {
        float size;
    };
}

#endif /* FONT_SIZE_COMPONENT_HPP */
