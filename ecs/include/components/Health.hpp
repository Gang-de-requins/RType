#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Health
     * @brief Health component
     * 
     * @details
     * This component is used to manage the health of an entity. It includes operators for easy manipulation of health values.
     * 
     * @var Health::health
     * The current health value of the entity.
     * 
     * The operators (+, +=, -, -=) are defined to facilitate the addition and subtraction of health values, allowing for straightforward modifications to an entity's health.
     */
    struct Health {
        float health;

        Health operator+(const Health& other) const {
            return { health + other.health };
        }

        Health &operator+=(const Health& other) {
            health += other.health;
            return *this;
        }

        Health operator-(const Health& other) const {
            return { health - other.health };
        }

        Health &operator-=(const Health& other) {
            health -= other.health;
            return *this;
        }
    };
}

#endif /* HEALTH_COMPONENT_HPP */
