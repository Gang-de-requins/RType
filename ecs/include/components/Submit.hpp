#ifndef SUBMIT_COMPONENT_HPP
#define SUBMIT_COMPONENT_HPP

#include <functional>
#include "TextInput.hpp"
#include "Entity.hpp"

namespace ecs {
    class SceneManager;

    struct Submit {
        int activationKey;
        std::function<void(SceneManager&, Entity*)> onSubmit;
    };
}

#endif /* SUBMIT_COMPONENT_HPP */