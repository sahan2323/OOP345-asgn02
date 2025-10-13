#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca
{
    class Guild
    {
        std::string m_name{};
        Character** m_members{};
        size_t m_count{};
        size_t m_capacity{};

        void ensure_capacity(size_t minCap)
        {
            if (m_capacity >= minCap) return;
            size_t newCap = m_capacity ? m_capacity * 2 : 4;
            if (newCap < minCap) newCap = minCap;
            Character** tmp = new Character*[newCap];
            for (size_t i = 0; i < m_count; ++i) tmp[i] = m_members[i];
            delete[] m_members;
            m_members = tmp;
            m_capacity = newCap;
        }

    public:
        Guild() = default;
        Guild(const char* name) : m_name{name} {}

        // copy ctor - shallow copy of pointers (aggregation)
        Guild(const Guild& other)
            : m_name(other.m_name), m_members(nullptr), m_count(0), m_capacity(0)
        {
            if (other.m_count > 0)
            {
                ensure_capacity(other.m_count);
                for (size_t i = 0; i < other.m_count; ++i)
                    m_members[i] = other.m_members[i];
                m_count = other.m_count;
            }
        }

        // move ctor
        Guild(Guild&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members),
              m_count(other.m_count), m_capacity(other.m_capacity)
        {
            other.m_members = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }

        // copy assignment
        Guild& operator=(const Guild& other)
        {
            if (this == &other) return *this;
            delete[] m_members;
            m_members = nullptr;
            m_count = m_capacity = 0;
            m_name = other.m_name;
            if (other.m_count > 0)
            {
                ensure_capacity(other.m_count);
                for (size_t i = 0; i < other.m_count; ++i)
                    m_members[i] = other.m_members[i];
                m_count = other.m_count;
            }
            return *this;
        }

        // move assignment
        Guild& operator=(Guild&& other) noexcept
        {
            if (this == &other) return *this;
            delete[] m_members;
            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_count = other.m_count;
            m_capacity = other.m_capacity;
            other.m_members = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
            return *this;
        }

        ~Guild()
        {
            // aggregation: do NOT delete pointed characters
            delete[] m_members;
        }

        void addMember(Character* c)
        {
            if (!c) return;
            // check if already in guild by pointer (or name)
            for (size_t i = 0; i < m_count; ++i)
                if (m_members[i] == c) return;

            // also check by name to be safe
            for (size_t i = 0; i < m_count; ++i)
                if (m_members[i]->getName() == c->getName()) return;

            ensure_capacity(m_count + 1);
            m_members[m_count++] = c;
            // increase health by 300
            int newMax = c->getHealthMax() + 300;
            c->setHealthMax(newMax);
        }

        void removeMember(const std::string& name)
        {
            for (size_t i = 0; i < m_count; ++i)
            {
                if (m_members[i]->getName() == name)
                {
                    // restore health max by subtracting 300
                    int newMax = m_members[i]->getHealthMax() - 300;
                    m_members[i]->setHealthMax(newMax);
                    // remove pointer from array
                    for (size_t j = i + 1; j < m_count; ++j) m_members[j - 1] = m_members[j];
                    --m_count;
                    return;
                }
            }
        }

        Character* operator[](size_t idx) const
        {
            if (idx >= m_count) return nullptr;
            return m_members[idx];
        }

        void showMembers() const
        {
            if (m_count == 0)
            {
                std::cout << "No guild.\n";
                return;
            }
            std::cout << "[Guild] " << m_name << '\n';
            for (size_t i = 0; i < m_count; ++i)
            {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << '\n';
            }
        }
    };
}

#endif
