#include "Game.hpp"

namespace rtype {
    void Game::loadCreateRoom(ecs::Scene &scene)
    {
        this->m_world.registerSystems<
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(scene);

    std::cout << "In Create Room" << std::endl;

    ecs::Entity &Bakckground = this->m_world.createEntity(scene);
    this->m_world.assign(Bakckground, ecs::Position{0, 0});
    this->m_world.assign(Bakckground, ecs::Sprite{"assets/CreateRoom/Space-Back.png", ecs::Rectangle{0, 0, 1920, 1080}, ecs::Vector2{0, 0}});
    this->m_world.assign(Bakckground, ecs::Scale{1, 1});
    this->m_world.assign(Bakckground, ecs::Rotation{0});

    ecs::Entity &ButtonBackward = this->m_world.createEntity(scene);
    this->m_world.assign(ButtonBackward, ecs::Position{5, 995});
    this->m_world.assign(ButtonBackward, ecs::Sprite{"assets/CreateRoom/buttonBackward.png", ecs::Rectangle{0, 0, 210, 210}, ecs::Vector2{0, 0}});
    this->m_world.assign(ButtonBackward, ecs::Scale{0.4f, 0.4f});
    this->m_world.assign(ButtonBackward, ecs::Rotation{0});
    this->m_world.assign(ButtonBackward, ecs::Clickable{false, [this](ecs::Clickable&) {
        std::cout << "-> ButtonBackward clicked" << std::endl;
        std::cout << "Switch to scene Choose Room" << std::endl;
        loadChooseRoom(this->m_world.getSceneById(SCENE_CHOOSEROOM));
        this->m_world.switchToScene(SCENE_CHOOSEROOM);
    }});

    ecs::Entity &ButtonPlay = this->m_world.createEntity(scene);
    this->m_world.assign(ButtonPlay, ecs::Position{810, 900});
    this->m_world.assign(ButtonPlay, ecs::Sprite{"assets/CreateRoom/buttonPlay.png", ecs::Rectangle{0, 0, 300, 153}, ecs::Vector2{0, 0}});
    this->m_world.assign(ButtonPlay, ecs::Scale{1, 1});
    this->m_world.assign(ButtonPlay, ecs::Rotation{0});
    this->m_world.assign(ButtonPlay, ecs::Clickable{false, [this](ecs::Clickable&) {
        std::cout << "-> ButtonPlay clicked" << std::endl;
        std::cout << "Switch to scene choose name" << std::endl;
        loadChooseName(this->m_world.getSceneById(SCENE_CHOOSENAME));
        this->m_world.switchToScene(SCENE_CHOOSENAME);
    }});

    ecs::Entity &TextChooseNameRoom = this->m_world.createEntity(scene);
    this->m_world.assign(TextChooseNameRoom, ecs::Position{620, 220});
    this->m_world.assign(TextChooseNameRoom, ecs::TextInput{10, ecs::Position{620, 220}, "> Choose your name of the ROOM !! <"});
    this->m_world.assign(TextChooseNameRoom, ecs::Scale{1, 1});
    this->m_world.assign(TextChooseNameRoom, ecs::Rotation{0});
    this->m_world.assign(TextChooseNameRoom, ecs::FontSize{40});
    this->m_world.assign(TextChooseNameRoom, ecs::TextColor{255, 255, 255, 255});

    ecs::Entity &fieldChangeName = this->m_world.createEntity(scene);
    this->m_world.assign(fieldChangeName, ecs::Position{857.5f, 280});
    this->m_world.assign(fieldChangeName, ecs::Sprite{"assets/CreateRoom/field.png", ecs::Rectangle{0, 0, 421, 171}, ecs::Vector2{0, 0}});
    this->m_world.assign(fieldChangeName, ecs::Scale{0.5f, 0.5f});
    this->m_world.assign(fieldChangeName, ecs::Rotation{0});

    ecs::Entity &NameRoomTextInput = this->m_world.createEntity(scene);
    this->m_world.assign(NameRoomTextInput, ecs::Position{900, 280});
    this->m_world.assign(NameRoomTextInput, ecs::Rectangle{0, 0, 300, 171});
    this->m_world.assign(NameRoomTextInput, ecs::TextInput{10, ecs::Position{900, 305}});
    this->m_world.assign(NameRoomTextInput, ecs::Scale{1, 1});
    this->m_world.assign(NameRoomTextInput, ecs::Rotation{0});
    this->m_world.assign(NameRoomTextInput, ecs::Clickable{false, [this](ecs::Clickable&) {
        ecs::Entity &NameRoomTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), 5);
        ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(NameRoomTextInput);
        textInput.isFocused = true;
    }});
    this->m_world.assign(NameRoomTextInput, ecs::FontSize{35});
    this->m_world.assign(NameRoomTextInput, ecs::TextColor{255, 255, 255, 255});
    this->m_world.assign(NameRoomTextInput, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
        if (sceneManager.has<ecs::TextInput>(*entity)) {
            ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
            this->m_network.test = textInput.content;
        }
    }});

    ecs::Entity &TextChooseNbrPlayers = this->m_world.createEntity(scene);
    this->m_world.assign(TextChooseNbrPlayers, ecs::Position{620, 520});
    this->m_world.assign(TextChooseNbrPlayers, ecs::TextInput{10, ecs::Position{600, 520}, "> Choose your number of players for the ROOM !! <"});
    this->m_world.assign(TextChooseNbrPlayers, ecs::Scale{1, 1});
    this->m_world.assign(TextChooseNbrPlayers, ecs::Rotation{0});
    this->m_world.assign(TextChooseNbrPlayers, ecs::FontSize{40});
    this->m_world.assign(TextChooseNbrPlayers, ecs::TextColor{255, 255, 255, 255});

    ecs::Entity &fielChangeNbrPlayers = this->m_world.createEntity(scene);
    this->m_world.assign(fielChangeNbrPlayers, ecs::Position{857.5f, 580});
    this->m_world.assign(fielChangeNbrPlayers, ecs::Sprite{"assets/CreateRoom/field.png", ecs::Rectangle{0, 0, 421, 171}, ecs::Vector2{0, 0}});
    this->m_world.assign(fielChangeNbrPlayers, ecs::Scale{0.5f, 0.5f});
    this->m_world.assign(fielChangeNbrPlayers, ecs::Rotation{0});

    ecs::Entity &NbrPlayersTextInput = this->m_world.createEntity(scene);
    this->m_world.assign(NbrPlayersTextInput, ecs::Position{900, 580});
    this->m_world.assign(NbrPlayersTextInput, ecs::Rectangle{0, 0, 300, 171});
    this->m_world.assign(NbrPlayersTextInput, ecs::TextInput{10, ecs::Position{900, 605}});
    this->m_world.assign(NbrPlayersTextInput, ecs::Scale{1, 1});
    this->m_world.assign(NbrPlayersTextInput, ecs::Rotation{0});
    this->m_world.assign(NbrPlayersTextInput, ecs::Clickable{false, [this](ecs::Clickable&) {
        ecs::Entity &NbrPlayersTextInput = this->m_world.getEntityById(this->m_world.getCurrentScene(), 8);
        ecs::TextInput &textInput = this->m_world.get<ecs::TextInput>(NbrPlayersTextInput);
        textInput.isFocused = true;
    }});
    this->m_world.assign(NbrPlayersTextInput, ecs::FontSize{35});
    this->m_world.assign(NbrPlayersTextInput, ecs::TextColor{255, 255, 255, 255});
    this->m_world.assign(NbrPlayersTextInput, ecs::Submit{KEY_ENTER, [this](ecs::SceneManager &sceneManager, ecs::Entity *entity) {
        if (sceneManager.has<ecs::TextInput>(*entity)) {
            ecs::TextInput &textInput = sceneManager.get<ecs::TextInput>(*entity);
            this->m_network.test = textInput.content;
        }
    }});
    }
}
