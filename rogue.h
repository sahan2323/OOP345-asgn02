#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h" // for Dagger

namespace seneca
{
    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T>
    {
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};
    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax),
              m_baseDefense{ baseDefense }, m_baseAttack{ baseAttack }, m_weapon{}
        {}

        int getAttackAmnt() const override
        {
            double dag = static_cast<double>(m_weapon);
            int dmg = m_baseAttack + static_cast<int>(2.0 * dag);
            return dmg;
        }

        int getDefenseAmnt() const override
        {
            return m_baseDefense;
        }

        Character* clone() const override
        {
            return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
        }

        void attack(Character* enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            int dmg = getAttackAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "    Rogue deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received.\n";
            int actual = dmg - m_baseDefense;
            if (actual < 0) actual = 0;

            m_firstAbility.transformDamageReceived(actual);
            m_secondAbility.transformDamageReceived(actual);

            CharacterTpl<T>::takeDamage(actual);
        }
    };
}

#endif
