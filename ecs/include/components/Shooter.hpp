#ifndef SHOOTER_COMPONENT_HPP
#define SHOOTER_COMPONENT_HPP

#include <chrono>

namespace ecs {
	struct Shooter {
		std::chrono::milliseconds cooldown;
		std::chrono::steady_clock::time_point lastShotTime;
	};
}

#endif /* SHOOTER_COMPONENT_HPP */
