#ifndef PARSER_JSON_HPP
#define PARSER_JSON_HPP

#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <array>
#include <cctype>
#include <algorithm>
#include "rapidjson/document.h"
#include "Scene.hpp"
#include "components/Components.hpp"
#include "Macros.hpp"

namespace ecs {
    class SceneManager;

    class ParserJson {
        public:
            ParserJson() = default;
            ~ParserJson() = default;

            void loadEntitiesFromJson(SceneManager &sceneManager, Scene &scene);
            void loadComponentsFromJson(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &components);

        private:
            void loadAcceleration(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &acceleration);
            void loadAnimation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &animation);
            void loadColor(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &color);
            void loadControllable(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &controllable);
            void loadFontSize(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &fontSize);
            void loadMusic(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &music);
            void loadPosition(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &position);
            void loadRectangle(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rectangle);
            void loadRotation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rotation);
            void loadScale(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &scale);
            void loadSprite(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &sprite);
            void loadText(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &text);
            void loadVelocity(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &velocity);
    };
}

#endif /* PARSER_JSON_HPP */
