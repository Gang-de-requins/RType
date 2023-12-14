#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP


/* Components */
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/Sprite.hpp"
#include "components/Controllable.hpp"
#include "components/Animation.hpp"
#include "components/Color.hpp"
#include "components/Text.hpp"
#include "components/Rectangle.hpp"
#include "components/FontSize.hpp"
#include "components/Scale.hpp"
#include "components/Vector2.hpp"
#include "components/Rotation.hpp"
#include "components/Music.hpp"
#include "components/Sound.hpp"

/* Systems */
#include "systems/Movement.hpp"
#include "systems/Controllable.hpp"
#include "systems/Music.hpp"
#include "systems/Sound.hpp"
#include "systems/rendering/Sprite.hpp"
#include "systems/rendering/Animation.hpp"
#include "systems/rendering/Text.hpp"

#include "Entity.hpp"
#include "World.hpp"

#endif /* GAME_ENGINE_HPP */
