#ifndef WAVEMANAGER_HPP
#define WAVEMANAGER_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
#include <vector>
#include <mutex>
#if defined(_WIN32)
    #define NOGDI
    #define NOUSER
#endif

#include <asio.hpp>

#if defined(_WIN32)
    #undef near
    #undef far
#endif
#include "MessageType.hpp"
#include "Player.hpp"
#include "EntityTemplate.hpp"
#include "GameEngine.hpp"
#include "systems/Movement.hpp"


namespace server {
    class WaveManager {
        public:
            WaveManager();
            ~WaveManager();

            void loadStages(const std::string& folderPath);

    };
}

#endif /* WAVEMANAGER_HPP */
