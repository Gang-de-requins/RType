#ifndef NETWORKSTRUCT_HPP
#define NETWORKSTRUCT_HPP

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>

namespace ecs {
    enum class MessageType : char {
        PlayerJoinRequest = 1,
        PlayerJoinResponse = 2,
        PlayerJoined = 3,
        PlayerJoinedAccept = 4,
        NewPlayer = 5,
        EntityList = 6,
        Move = 7,
        GoRight = 8,
        GoLeft = 9,
        GoTop = 10,
        GoBottom = 11,
        StopRight = 12,
        StopLeft = 13,
        StopTop = 14,
        StopBottom = 15,
        Ping = 16,
        GetRooms = 17,
        CreateRoom = 18,
    };


struct PlayerJoinRequest {
    std::string playername;

    std::string serialize() const {
        std::ostringstream oss;
        oss << std::quoted(playername);
        return oss.str();
    }

    void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        iss >> std::ws;
        iss >> std::quoted(playername);
    }
};

struct PlayerJoinResponse {
    bool response;
    int port;

    std::vector<char> serialize() const {
        std::ostringstream oss;
        oss << response << " " << port;
        std::string serializedData = oss.str();
        return std::vector<char>(serializedData.begin(), serializedData.end());
    }
    
    void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        iss >> response >> port;
    }
};

struct PlayerJoined {
    std::string playername;

    std::vector<char> serialize() const {
        std::ostringstream oss;
        oss << std::quoted(playername);
        std::string serializedData = oss.str();
        return std::vector<char>(serializedData.begin(), serializedData.end());
    }
    
    void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        iss >> std::quoted(playername);
    }
};


struct EntityInfo {
    std::string playername;
    int id;
    int hp;
    std::pair<float, float> pos;

    std::vector<char> serialize() const {
        std::ostringstream oss;
        oss << std::quoted(playername) << " " << id << " " << hp << " " 
            << pos.first << " " << pos.second;
        std::string serializedData = oss.str();
        return std::vector<char>(serializedData.begin(), serializedData.end());
    }

    void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        iss >> std::quoted(playername) >> id >> hp >> pos.first >> pos.second;
    }
};


struct EntityList {
    std::vector<EntityInfo> entityList;

   std::vector<char> serialize() const {
        std::ostringstream oss;
        for (const auto& entity : entityList) {
            std::vector<char> serializedEntity = entity.serialize();
            oss.write(serializedEntity.data(), serializedEntity.size());
            oss << ";";
        }
        std::string serializedData = oss.str();
        return std::vector<char>(serializedData.begin(), serializedData.end());
    }

   void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        std::string entityData;
        while (std::getline(iss, entityData, ';')) {
            EntityInfo entity;
            entity.deserialize(std::vector<char>(entityData.begin(), entityData.end()));
            entityList.push_back(entity);
        }
    }
};

    struct Move {
        ecs::MessageType direction;

        std::vector<char> serialize() const {
            int directionValue = static_cast<int>(direction); // Convert enum class to int
            std::ostringstream oss;
            oss << directionValue;
            std::string serializedData = oss.str();
            return std::vector<char>(serializedData.begin(), serializedData.end());
        }

        void deserialize(const std::vector<char>& data) {
            std::string serializedData(data.begin(), data.end());
            std::istringstream iss(serializedData);
            int directionValue;
            iss >> directionValue;
            direction = static_cast<ecs::MessageType>(directionValue); // Convert int back to enum class
        }
    };

struct NewPlayer {
    std::string playername;
    int id;
    std::pair<float, float> pos;
    int hp;

    std::vector<char> serialize() const {
        std::ostringstream oss;
        oss << std::quoted(playername) << " ";
        oss << id << " ";
        oss << pos.first << " " << pos.second << " ";
        oss << hp;
        std::string serializedData = oss.str();
        return std::vector<char>(serializedData.begin(), serializedData.end());
    }
    
    void deserialize(const std::vector<char>& data) {
        std::string serializedData(data.begin(), data.end());
        std::istringstream iss(serializedData);
        iss >> std::quoted(playername) >> id >> pos.first >> pos.second >> hp;
    }
};

};

#endif /* NETWORK_HPP */