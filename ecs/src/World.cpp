#include "World.hpp"

namespace ecs {
    Entity &World::createEntity() {
        this->m_entities.emplace_back(Entity{this->m_nextEntityId++, {}});
        return this->m_entities.back();
    }

    void World::destroyEntity(Entity &entity) {
        this->m_entities.erase(std::remove_if(this->m_entities.begin(), this->m_entities.end(), [&entity](const Entity &e) {
            return e.id == entity.id;
        }), this->m_entities.end());
    }

    Texture2D &World::getTexture(std::string_view path) {
        if (this->m_textures.find(path) == this->m_textures.end()) {
            this->m_textures.insert({path, LoadTexture(path.data())});
        }

        return this->m_textures.at(path);
    }

    ::Music &World::getMusic(std::string_view path) {
        if (this->m_musics.find(path) == this->m_musics.end()) {
            this->m_musics.insert({path, LoadMusicStream(path.data())});
        }

        return this->m_musics.at(path);
    }
}
