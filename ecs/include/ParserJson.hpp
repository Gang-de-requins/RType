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

    /**
     * @class ParserJson
     * @brief Parser json
     * 
     * @details
     * This class is used to parse json files.
     */
    class ParserJson {
        public:
            /**
             * @fn ParserJson::ParserJson
             * @brief Construct a new Parser Json object
             * 
             */
            ParserJson() = default;
            /**
             * @fn ParserJson::~ParserJson
             * @brief Destroy the Parser Json object
             * 
             */
            ~ParserJson() = default;

            /**
             * @fn ParserJson::loadSceneFromJson
             * @brief Load a scene from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             */
            void loadEntitiesFromJson(SceneManager &sceneManager, Scene &scene);
            /**
             * @fn ParserJson::loadComponentsFromJson
             * @brief Load the components of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param components The components
             */
            void loadComponentsFromJson(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &components);

        private:
            /**
             * @fn ParserJson::loadAcceleration
             * @brief Load the acceleration component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param acceleration The acceleration component
             */
            void loadAcceleration(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &acceleration);
            /**
             * @fn ParserJson::loadAnimation
             * @brief Load the animation component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param animation The animation component
             */
            void loadAnimation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &animation);
            /**
             * @fn ParserJson::loadColor
             * @brief Load the color component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param color The color component
             */
            void loadColor(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &color);
            /**
             * @fn ParserJson::loadControllable
             * @brief Load the controllable component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param controllable The controllable component
             */
            void loadControllable(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &controllable);
            /**
             * @fn ParserJson::loadFontSize
             * @brief Load the font size component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param fontSize The font size component
             */
            void loadFontSize(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &fontSize);
            /**
             * @fn ParserJson::loadMusic
             * @brief Load the music component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param music The music component
             */
            void loadMusic(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &music);
            /**
             * @fn ParserJson::loadPosition
             * @brief Load the position component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param position The position component
             */
            void loadPosition(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &position);
            /**
             * @fn ParserJson::loadRectangle
             * @brief Load the rectangle component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param rectangle The rectangle component
             */
            void loadRectangle(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rectangle);
            /**
             * @fn ParserJson::loadRotation
             * @brief Load the rotation component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param rotation The rotation component
             */
            void loadRotation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rotation);
            /**
             * @fn ParserJson::loadScale
             * @brief Load the scale component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param scale The scale component
             */
            void loadScale(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &scale);
            /**
             * @fn ParserJson::loadSprite
             * @brief Load the sprite component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param sprite The sprite component
             */
            void loadSprite(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &sprite);
            /**
             * @fn ParserJson::loadText
             * @brief Load the text component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param text The text component
             */
            void loadText(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &text);
            /**
             * @fn ParserJson::loadVelocity
             * @brief Load the velocity component of an entity from a json file
             * 
             * @param sceneManager The scene manager
             * @param scene The scene
             * @param entity The entity
             * @param velocity The velocity component
             */
            void loadVelocity(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &velocity);
    };
}

#endif /* PARSER_JSON_HPP */
