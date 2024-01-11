#include "Game.hpp"

namespace rtype {
    void Game::loadSettings(ecs::Scene &scene)
    {
        this->m_world.registerSystems<
            ecs::RenderSystem,
            ecs::ClickableSystem,
            ecs::SubmitSystem
        >(scene);

        std::cout << "In Settings" << std::endl;

        ecs::Entity &Bakckground_Settings = this->m_world.createEntity(scene);
        this->m_world.assign(Bakckground_Settings, ecs::Position{0, 0});
        this->m_world.assign(Bakckground_Settings, ecs::Sprite{"assets/Settings/Space-Back-Settings.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
        this->m_world.assign(Bakckground_Settings, ecs::Scale{1, 1});
        this->m_world.assign(Bakckground_Settings, ecs::Rotation{0});

        ecs::Entity &ButtonMusic = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonMusic, ecs::Position{650, 90});
        this->m_world.assign(ButtonMusic, ecs::Sprite{"assets/Settings/buttonMusic.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonMusic, ecs::Scale{0.6f, 0.6f});
        this->m_world.assign(ButtonMusic, ecs::Rotation{0});
        this->m_world.assign(ButtonMusic, ecs::Clickable{false, [this](ecs::Clickable&, ecs::Entity *) {this->m_world.switchToScene(1);}});

        ecs::Entity &ButtonPause = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonPause, ecs::Position{630, 230});
        this->m_world.assign(ButtonPause, ecs::Sprite{"assets/Settings/buttonPause.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPause, ecs::Scale{0.3f, 0.3f});
        this->m_world.assign(ButtonPause, ecs::Rotation{0});

        ecs::Entity &ButtonPlayMusic = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonPlayMusic, ecs::Position{730, 230});
        this->m_world.assign(ButtonPlayMusic, ecs::Sprite{"assets/Settings/buttonPlay.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonPlayMusic, ecs::Scale{0.3f, 0.3f});
        this->m_world.assign(ButtonPlayMusic, ecs::Rotation{0});
        this->m_world.assign(ButtonPlayMusic, ecs::Clickable{false, [this](ecs::Clickable&, ecs::Entity *) {this->m_world.switchToScene(1);}});

        ecs::Entity &ButtonBackward = this->m_world.createEntity(scene);
        this->m_world.assign(ButtonBackward, ecs::Position{5, 995});
        this->m_world.assign(ButtonBackward, ecs::Sprite{"assets/Settings/buttonBackward.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(ButtonBackward, ecs::Scale{0.4f, 0.4f});
        this->m_world.assign(ButtonBackward, ecs::Rotation{0});
        this->m_world.assign(ButtonBackward, ecs::Clickable{false, [this](ecs::Clickable&, ecs::Entity *) {
            std::cout << "-> ButtonPlay clicked" << std::endl;
            std::cout << "Switch scene Menu" << std::endl;
            loadMenu(this->m_world.getSceneById(SCENE_MENU));
            this->m_world.switchToScene(SCENE_MENU);
        }});

        ecs::Entity &SettingPort = this->m_world.createEntity(scene);
        this->m_world.assign(SettingPort, ecs::Position{1147, 90});
        this->m_world.assign(SettingPort, ecs::Sprite{"assets/Settings/settingIP.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(SettingPort, ecs::Scale{0.6f, 0.6f});
        this->m_world.assign(SettingPort, ecs::Rotation{0});

        ecs::Entity &ChangePort = this->m_world.createEntity(scene);
        this->m_world.assign(ChangePort, ecs::Position{1100.5f, 230});
        this->m_world.assign(ChangePort, ecs::Sprite{"assets/Settings/nickname.png", ecs::Rectangle{0, 0, 421, 171}, ecs::Vector2{0, 0}});
        this->m_world.assign(ChangePort, ecs::Scale{0.5f, 0.5f});
        this->m_world.assign(ChangePort, ecs::Rotation{0});

        ecs::Entity &PortTextInput = this->m_world.createEntity(scene);
        this->m_world.assign(PortTextInput, ecs::Position{1147, 260});
        this->m_world.assign(PortTextInput, ecs::Rectangle{0, 0, 421, 171});
        this->m_world.assign(PortTextInput, ecs::TextInput{10, ecs::Position{1147, 260}});
        this->m_world.assign(PortTextInput, ecs::Scale{1, 1});
        this->m_world.assign(PortTextInput, ecs::Rotation{0});
        this->m_world.assign(PortTextInput, ecs::Clickable{false, [this](ecs::Clickable&, ecs::Entity *entity) {
            // ecs::Entity &PortTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), entity->id);
            ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(*entity);
            textInput.isFocused = true;
        }});
        this->m_world.assign(PortTextInput, ecs::Color{200, 200, 200, 255});
        this->m_world.assign(PortTextInput, ecs::FontSize{35});
        this->m_world.assign(PortTextInput, ecs::TextColor{255, 255, 255, 255});
        this->m_world.assign(PortTextInput, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
            if (sceneManager.has<ecs::TextInput>(*entity)) {
                ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);

                try {
                    this->m_network.m_port = static_cast<unsigned short>(std::stoi(textInput.content));
                    std::cout << "m_port: " << this->m_network.m_port << std::endl;
                } catch (const std::exception &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
        }}});

        ecs::Entity &SettingIP = this->m_world.createEntity(scene);
        this->m_world.assign(SettingIP, ecs::Position{900, 350});
        this->m_world.assign(SettingIP, ecs::Sprite{"assets/Settings/settingIP.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
        this->m_world.assign(SettingIP, ecs::Scale{0.6f, 0.6f});
        this->m_world.assign(SettingIP, ecs::Rotation{0});

        ecs::Entity &ChangeIP = this->m_world.createEntity(scene);
        this->m_world.assign(ChangeIP, ecs::Position{857.5f, 490});
        this->m_world.assign(ChangeIP, ecs::Sprite{"assets/Settings/nickname.png", ecs::Rectangle{0, 0, 421, 171}, ecs::Vector2{0, 0}});
        this->m_world.assign(ChangeIP, ecs::Scale{0.5f, 0.5f});
        this->m_world.assign(ChangeIP, ecs::Rotation{0});

        ecs::Entity &IPTextInput = this->m_world.createEntity(scene);
        this->m_world.assign(IPTextInput, ecs::Position{900, 510});
        this->m_world.assign(IPTextInput, ecs::Rectangle{0, 0, 421, 171});
        this->m_world.assign(IPTextInput, ecs::TextInput{10, ecs::Position{900, 510}});
        this->m_world.assign(IPTextInput, ecs::Scale{1, 1});
        this->m_world.assign(IPTextInput, ecs::Rotation{0});
        this->m_world.assign(IPTextInput, ecs::Clickable{false, [this](ecs::Clickable&, ecs::Entity *entity) {
            // ecs::Entity &IPTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), 10);
            ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(*entity);
            textInput.isFocused = true;
        }});
        this->m_world.assign(IPTextInput, ecs::Color{200, 200, 200, 255});
        this->m_world.assign(IPTextInput, ecs::FontSize{35});
        this->m_world.assign(IPTextInput, ecs::TextColor{255, 255, 255, 255});
        this->m_world.assign(IPTextInput, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
            if (sceneManager.has<ecs::TextInput>(*entity)) {
                ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
                this->m_network.m_ip = textInput.content;
            }
        }});
    }
}
