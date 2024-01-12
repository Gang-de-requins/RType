#ifndef DAMAGE_COMPONENT_HPP
#define DAMAGE_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Damage
     * @brief Damage component
     * 
     * @details
     * This component is used to store and manage damage information of an entity. It includes arithmetic operators to easily manipulate damage values.
     * 
     * @var Damage::damage
     * The amount of damage.
     * 
     * The operators (+, +=, -, -=) are defined to facilitate the addition and subtraction of damage values.
     */
    struct Damage {
        float damage;

        Damage operator+(const Damage& other) const {
            return { damage + other.damage };
        }

        Damage &operator+=(const Damage& other) {
            damage += other.damage;
            return *this;
        }

        Damage operator-(const Damage& other) const {
            return { damage - other.damage };
        }

        Damage &operator-=(const Damage& other) {
            damage -= other.damage;
            return *this;
        }
    };
}

#endif /* DAMAGE_COMPONENT_HPP */
