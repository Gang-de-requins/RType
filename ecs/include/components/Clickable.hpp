#ifndef CLICKABLE_COMPONENT_HPP_
#define CLICKABLE_COMPONENT_HPP_

#include <functional>

namespace ecs {
    struct Clickable {
        bool clickable;
        std::function<void(Clickable&)> onClick;
    };
}

#endif /* !CLICKABLE_HPP_ */
