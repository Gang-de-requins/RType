/*
** EPITECH PROJECT, 2024
** RType
** File description:
** LoadEnd
*/

#include "Pong.hpp"

namespace game
{
    void Pong::LoadEnd(ecs::Scene &scene)
    {
        this->world.registerSystems<
            ecs::MusicSystem,
            ecs::TextSystem,
            ecs::RenderSystem,
            ecs::ClickableSystem
        >(scene);

        ecs::Entity &Winner = this->world.createEntity(scene);
        this->world.assign(Winner, ecs::Position{800, 400});
        this->world.assign(Winner, ecs::Text({this->winner.append(" wins !")}));
        this->world.assign(Winner, ecs::FontSize({50}));
        this->world.assign(Winner, ecs::TextColor({255, 255, 255, 255}));



        // ecs::Entity &ButtonBack = this->world.createEntity(scene);
        // this->world.assign(ButtonBack, ecs::Position{725, 700});
        // this->world.assign(ButtonBack, ecs::Sprite{"../assets/pong_back.png", ecs::Rectangle{0, 0, 245, 60}, ecs::Vector2{0, 0}});
        // this->world.assign(ButtonBack, ecs::Scale{2, 2});
        // this->world.assign(ButtonBack, ecs::Rotation{0});
        // this->world.assign(ButtonBack, ecs::Clickable{false, [this](ecs::Clickable&) {
        //     std::cout << "-> ButtonPlay clicked" << std::endl;
        //     std::cout << "Switch scene Menu" << std::endl;
        //     LoadMenu(this->world.getSceneById(MENU));
        //     this->world.switchToScene(MENU);
        // }});
    }
}