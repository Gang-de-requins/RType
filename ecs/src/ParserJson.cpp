#include "ParserJson.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ParserJson::loadEntitiesFromJson(SceneManager &sceneManager, Scene &scene) {
        rapidjson::Document document;
        std::ifstream file(scene.path.data());
        std::string jsonString = "";

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << scene.path << std::endl;
            return;
        }

        jsonString = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        document.Parse(jsonString.c_str());

        if (document.HasParseError()) {
            std::cerr << "Failed to parse JSON file: " << scene.path << std::endl;
            return;
        }

        if (!document.IsArray()) {
            std::cerr << "JSON file is not an array: " << scene.path << std::endl;
            return;
        }

        for (auto &entity : document.GetArray()) {
            Entity &e = sceneManager.createEntity(scene);

            if (entity.HasMember("components") && entity["components"].IsArray()) {
                this->loadComponentsFromJson(sceneManager, scene, e, entity["components"]);
            } else {
                std::cerr << "One entity in JSON file has no components or is not an object in file: " << scene.path << std::endl;
            }
        }
    }

    void ParserJson::loadComponentsFromJson(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &components) {
        std::vector<std::string_view> componentsNames = std::vector<std::string_view>{ALL_COMPONENTS};
        std::vector<void (ParserJson::*)(SceneManager &, Scene &, Entity &, rapidjson::Value &)> componentsLoaders = {
            &ParserJson::loadAcceleration, &ParserJson::loadAnimation,
            &ParserJson::loadColor, &ParserJson::loadControllable,
            &ParserJson::loadFontSize, &ParserJson::loadMusic,
            &ParserJson::loadPosition, &ParserJson::loadRectangle,
            &ParserJson::loadRotation, &ParserJson::loadScale,
            &ParserJson::loadSprite, &ParserJson::loadText,
            &ParserJson::loadVelocity
        };

        for (auto &component : components.GetArray()) {
            if (!component.IsObject()) {
                std::cerr << "One component in JSON file is not an object in file: " << scene.path << std::endl;
                return;
            }

            for (int i = 0; i < componentsNames.size(); i++) {
                if (component.HasMember(componentsNames[i].data()) && component[componentsNames[i].data()].IsObject()) {
                    (this->*componentsLoaders[i])(sceneManager, scene, entity, component[componentsNames[i].data()]);
                }
            }
        }
    }

    /* Private functions */
    void ParserJson::loadAcceleration(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &acceleration) {
        std::array<std::string_view, 3> accelerationNames = {"ddx", "ddy", "maxSpeed"};

        for (auto &accel : accelerationNames) {
            if (!acceleration.HasMember(accel.data()) || !acceleration[accel.data()].IsNumber()) {
                std::cerr << "Acceleration has no " << accel << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Acceleration>(entity, Acceleration{
            acceleration["ddx"].GetFloat(),
            acceleration["ddy"].GetFloat(),
            acceleration["maxSpeed"].GetFloat()
        });
    }

    void ParserJson::loadAnimation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &animation) {
        std::array<std::string_view, 4> animationNames = {"offset", "frames", "currentFrame", "frameTime"};
        std::array<std::string_view, 4> offsetNames = {"x", "y", "width", "height"};

        for (int i = 0; i < animationNames.size(); i++) {
            if (i == 0 && (!animation.HasMember(animationNames[i].data()) || !animation[animationNames[i].data()].IsObject())) {
                std::cerr << "Animation has no " << animationNames[i] << " or is not an object in file: " << scene.path << std::endl;
                return;
            } else if (i != 0 && (!animation.HasMember(animationNames[i].data()) || !animation[animationNames[i].data()].IsInt())) {
                std::cerr << "Animation has no " << animationNames[i] << " or is not an integer in file: " << scene.path << std::endl;
                return;
            }
        }

        for (auto &offset : offsetNames) {
            if (!animation["offset"].HasMember(offset.data()) || !animation["offset"][offset.data()].IsNumber()) {
                std::cerr << "Animation offset has no " << offset << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Animation>(entity, Animation{
            Rectangle{
                animation["offset"]["x"].GetFloat(),
                animation["offset"]["y"].GetFloat(),
                animation["offset"]["width"].GetFloat(),
                animation["offset"]["height"].GetFloat()
            },
            animation["frames"].GetInt(),
            animation["currentFrame"].GetInt(),
            animation["frameTime"].GetInt(),
            std::chrono::steady_clock::now()
        });
    }

    void ParserJson::loadColor(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &color) {
        std::array<std::string_view, 4> colorNames = {"r", "g", "b", "a"};
        std::array<unsigned char, 4> colorValues = {0, 0, 0, 0};

        for (int i = 0; i < colorNames.size(); i++) {
            if (!color.HasMember(colorNames[i].data()) || !color[colorNames[i].data()].IsInt()) {
                std::cerr << "Color has no " << colorNames[i] << " or is not an integer in file: " << scene.path << std::endl;
                return;
            }

            colorValues[i] = color[colorNames[i].data()].GetInt();
            if (colorValues[i] < 0 || colorValues[i] > 255) {
                std::cerr << "Color " << colorNames[i] << " is not between 0 and 255 in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Color>(entity, Color{colorValues[0], colorValues[1], colorValues[2], colorValues[3]});
    }

    void ParserJson::loadControllable(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &controllable) {
        std::array<std::string_view, 4> controllableNames = {"keyUp", "keyDown", "keyLeft", "keyRight"};
        std::array<int, 4> controllableValues = {0, 0, 0, 0};

        for (int i = 0; i < controllableNames.size(); i++) {
            if (!controllable.HasMember(controllableNames[i].data()) || !controllable[controllableNames[i].data()].IsInt()) {
                std::cerr << "Controllable has no " << controllableNames[i] << " or is not a valid key in file: " << scene.path << std::endl;
                return;
            }

            controllableValues[i] = controllable[controllableNames[i].data()].GetInt();
        }

        sceneManager.assign<Controllable>(entity, Controllable{controllableValues[0], controllableValues[1], controllableValues[2], controllableValues[3]});
    }

    void ParserJson::loadFontSize(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &fontSize) {
        if (!fontSize.HasMember("size") || !fontSize["size"].IsNumber()) {
            std::cerr << "FontSize has no size or is not an integer in file: " << scene.path << std::endl;
            return;
        }

        sceneManager.assign<FontSize>(entity, FontSize{fontSize["size"].GetFloat()});
    }

    void ParserJson::loadMusic(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &music) {
        if (!music.HasMember("path") || !music["path"].IsString()) {
            std::cerr << "Music has no path or is not a string in file: " << scene.path << std::endl;
            return;
        }

        sceneManager.assign<Music>(entity, Music{music["path"].GetString()});
    }

    void ParserJson::loadPosition(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &position) {
        const std::array<std::string_view, 2> positionNames = {"x", "y"};

        for (const auto &positionName : positionNames) {
            if (!position.HasMember("x") || !position["x"].IsNumber()) {
                std::cerr << "Position has no " << positionName << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Position>(entity, Position{position["x"].GetFloat(), position["y"].GetFloat()});
    }

    void ParserJson::loadRectangle(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rectangle) {
        std::array<std::string_view, 4> rectangleNames = {"x", "y", "width", "height"};

        for (auto &rect : rectangleNames) {
            if (!rectangle.HasMember(rect.data()) || !rectangle[rect.data()].IsNumber()) {
                std::cerr << "Rectangle has no " << rect << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Rectangle>(entity, Rectangle{
            rectangle["x"].GetFloat(),
            rectangle["y"].GetFloat(),
            rectangle["width"].GetFloat(),
            rectangle["height"].GetFloat()
        });
    }

    void ParserJson::loadRotation(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &rotation) {
        if (!rotation.HasMember("angle") || !rotation["angle"].IsNumber()) {
            std::cerr << "Rotation has no angle or is not a number in file: " << scene.path << std::endl;
            return;
        }

        sceneManager.assign<Rotation>(entity, Rotation{rotation["angle"].GetFloat()});
    }

    void ParserJson::loadScale(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &scale) {
        std::array<std::string_view, 2> scaleNames = {"x", "y"};

        for (auto &sca : scaleNames) {
            if (!scale.HasMember(sca.data()) || !scale[sca.data()].IsNumber()) {
                std::cerr << "Scale has no " << sca << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Scale>(entity, Scale{scale["x"].GetFloat(), scale["y"].GetFloat()});
    }

    void ParserJson::loadSprite(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &sprite) {
        std::array<std::string_view, 3> spriteNames = {"path", "source", "origin"};
        std::array<std::string_view, 4> sourceNames = {"x", "y", "width", "height"};
        std::array<std::string_view, 2> originNames = {"x", "y"};

        for (int i = 0; i < spriteNames.size(); i++) {
            if (i == 0 && (!sprite.HasMember(spriteNames[i].data()) || !sprite[spriteNames[i].data()].IsString())) {
                std::cerr << "Sprite has no " << spriteNames[i] << " or is not a string in file: " << scene.path << std::endl;
                return;
            } else if (i == 1 && (!sprite.HasMember(spriteNames[i].data()) || !sprite[spriteNames[i].data()].IsObject())) {
                std::cerr << "Sprite has no " << spriteNames[i] << " or is not an object in file: " << scene.path << std::endl;
                return;
            } else if (i == 2 && (!sprite.HasMember(spriteNames[i].data()) || !sprite[spriteNames[i].data()].IsObject())) {
                std::cerr << "Sprite has no " << spriteNames[i] << " or is not an object in file: " << scene.path << std::endl;
                return;
            }
        }

        for (auto &source : sourceNames) {
            if (!sprite["source"].HasMember(source.data()) || !sprite["source"][source.data()].IsNumber()) {
                std::cerr << "Sprite source has no " << source << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        for (auto &origin : originNames) {
            if (!sprite["origin"].HasMember(origin.data()) || !sprite["origin"][origin.data()].IsNumber()) {
                std::cerr << "Sprite origin has no " << origin << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Sprite>(entity, Sprite{
            sprite["path"].GetString(),
            Rectangle{
                sprite["source"]["x"].GetFloat(),
                sprite["source"]["y"].GetFloat(),
                sprite["source"]["width"].GetFloat(),
                sprite["source"]["height"].GetFloat()
            },
            Vector2{
                sprite["origin"]["x"].GetFloat(),
                sprite["origin"]["y"].GetFloat()
            }
        });

        std::cout << "Path sprite: " << sprite["path"].GetString() << std::endl;
    }

    void ParserJson::loadText(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &text) {
        if (!text.HasMember("content") || !text["content"].IsString()) {
            std::cerr << "Text has no content or is not a string in file: " << scene.path << std::endl;
            return;
        }

        sceneManager.assign<Text>(entity, Text{text["content"].GetString()});
    }
    
    void ParserJson::loadVelocity(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &velocity) {
        std::array<std::string_view, 2> velocityNames = {"dx", "dy"};

        for (auto &vel : velocityNames) {
            if (!velocity.HasMember(vel.data()) || !velocity[vel.data()].IsNumber()) {
                std::cerr << "Velocity has no " << vel << " or is not a number in file: " << scene.path << std::endl;
                return;
            }
        }

        sceneManager.assign<Velocity>(entity, Velocity{velocity["dx"].GetFloat(), velocity["dy"].GetFloat()});
    }
}
