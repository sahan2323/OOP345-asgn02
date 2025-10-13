#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include <cmath>

namespace seneca
{
    template<typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth>
    {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon{};
    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<SuperHealth>(name, healthMax),
              m_baseDefense{ baseDefense }, m_baseAttack{ baseAttack }, m_weapon{ weapon }
        {}

        int getAttackAmnt() const override
        {
            // 1.3 * base attack
            double val = 1.3 * m_baseAttack;
            return static_cast<int>(val);
        }

        int getDefenseAmnt() const override
        {
            double val = 1.2 * m_baseDefense;
            return static_cast<int>(val);
        }

        Character* clone() const override
        {
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character* enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            int dmg = getAttackAmnt();
            std::cout << "    Archer deals " << dmg << " ranged damage!\n";
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            int defense = getDefenseAmnt();
            std::cout << "    Archer has a defense of " << defense << ". Reducing damage received.\n";
            int actual = dmg - defense;
            if (actual < 0) actual = 0;
            CharacterTpl<SuperHealth>::takeDamage(actual);
        }
    };
}

#endif
