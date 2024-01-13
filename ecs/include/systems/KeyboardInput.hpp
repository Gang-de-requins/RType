#ifndef KEYBOARDINPUT_SYSTEM_HPP
#define KEYBOARDINPUT_SYSTEM_HPP

#include <vector>
#include <algorithm>
// #include "raylib.h"
#include <SFML/Graphics.hpp>
#include "ISystem.hpp"

namespace ecs {
	class KeyboardInputSystem : public ISystem {
		public:
			void update(SceneManager &sceneManager) override;
	};
}

#endif /* KEYBOARDINPUT_SYSTEM_HPP */
