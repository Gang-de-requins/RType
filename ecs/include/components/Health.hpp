#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

namespace ecs {
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
