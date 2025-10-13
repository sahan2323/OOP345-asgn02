#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"

namespace seneca
{
    template<typename T>
    class CharacterTpl : public Character
    {
        int m_healthMax{};
        T m_health{};
    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax{ healthMax }, m_health{ healthMax }
        {}

        // health accessors
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
            if (getHealth() <= 0)
            {
                std::cout << getName() << " has been defeated!\n";
            }
            else
            {
                std::cout << getName() << " took " << dmg << " damage, " << getHealth() << " health remaining.\n";
            }
        }

        virtual ~CharacterTpl() = default;
    };
}

#endif
