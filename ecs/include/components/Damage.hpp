#ifndef DAMAGE_COMPONENT_HPP
#define DAMAGE_COMPONENT_HPP

namespace ecs {
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
