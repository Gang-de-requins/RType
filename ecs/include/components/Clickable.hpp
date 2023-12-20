#ifndef CLICKABLE_COMPONENT_HPP_
#define CLICKABLE_COMPONENT_HPP_

#include <functional>

namespace ecs {
    struct Clickable;

    using Clickhandler = std::function<void(Clickable&)>;

    struct Clickable {
        bool clickable;
        Clickhandler onClick;
    };
}

#endif /* !CLICKABLE_HPP_ */
