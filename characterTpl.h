#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include <iostream>
#include <type_traits>

namespace seneca
{
    template <typename T>
    class CharacterTpl : public Character
    {
        int m_healthMax{};
        T m_health{};

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax{ healthMax }
        {
            if constexpr (std::is_constructible_v<T, int>)
            {
                m_health = T(healthMax);
            }
            else
            {
                m_health = T{};
                // if type T has operator= for int, this works:
                m_health = healthMax;
            }
        }

        int getHealth() const override
        {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override
        {
            return m_healthMax;
        }

        void setHealth(int health) override
        {
            m_health = health;
        }

        void setHealthMax(int health) override
        {
            m_healthMax = health;
            m_health = health;
        }

        void takeDamage(int dmg) override
        {
            m_health -= dmg;
            if (static_cast<int>(m_health) <= 0)
            {
                std::cout << getName() << " has been defeated!" << std::endl;
            }
            else
            {
                std::cout << getName() << " took " << dmg
                          << " damage, " << static_cast<int>(m_health)
                          << " health remaining." << std::endl;
            }
        }

        virtual ~CharacterTpl() = default;
    };
}

#endif
