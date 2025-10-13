#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"

namespace seneca
{
    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>
    {
        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2]{};
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
                  Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax),
              m_baseDefense{ baseDefense }, m_baseAttack{ baseAttack }
        {
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        int getAttackAmnt() const override
        {
            double w1 = static_cast<double>(m_weapon[0]);
            double w2 = static_cast<double>(m_weapon[1]);
            int dmg = m_baseAttack + static_cast<int>(w1 / 2.0) + static_cast<int>(w2 / 2.0);
            return dmg;
        }

        int getDefenseAmnt() const override
        {
            return m_baseDefense;
        }

        Character* clone() const override
        {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }

        void attack(Character* enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            // use ability on self
            m_ability.useAbility(this);

            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received.\n";
            int actual = dmg - m_baseDefense;
            if (actual < 0) actual = 0;

            m_ability.transformDamageReceived(actual);

            CharacterTpl<T>::takeDamage(actual);
        }
    };
}

#endif
