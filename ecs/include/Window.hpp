#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <SFML/Graphics.hpp>

namespace ecs {
    struct Window {
        std::shared_ptr<sf::RenderWindow> window;
        sf::Event event;
    };
}

#endif /* WINDOW_HPP */
