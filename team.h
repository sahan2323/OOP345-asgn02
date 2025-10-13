#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca
{
    class Team
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
        Team() = default;
        Team(const char* name) : m_name{name} {}

        // copy ctor
        Team(const Team& other)
            : m_name(other.m_name), m_members(nullptr), m_count(0), m_capacity(0)
        {
            if (other.m_count > 0)
            {
                ensure_capacity(other.m_count);
                for (size_t i = 0; i < other.m_count; ++i)
                {
                    m_members[i] = other.m_members[i]->clone();
                }
                m_count = other.m_count;
            }
        }

        // move ctor
        Team(Team&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members),
              m_count(other.m_count), m_capacity(other.m_capacity)
        {
            other.m_members = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }

        // copy assignment
        Team& operator=(const Team& other)
        {
            if (this == &other) return *this;
            // clean up current
            for (size_t i = 0; i < m_count; ++i) delete m_members[i];
            delete[] m_members;
            m_members = nullptr;
            m_count = m_capacity = 0;
            m_name = other.m_name;
            if (other.m_count > 0)
            {
                ensure_capacity(other.m_count);
                for (size_t i = 0; i < other.m_count; ++i)
                    m_members[i] = other.m_members[i]->clone();
                m_count = other.m_count;
            }
            return *this;
        }

        // move assignment
        Team& operator=(Team&& other) noexcept
        {
            if (this == &other) return *this;
            for (size_t i = 0; i < m_count; ++i) delete m_members[i];
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

        ~Team()
        {
            for (size_t i = 0; i < m_count; ++i) delete m_members[i];
            delete[] m_members;
        }

        void addMember(const Character* c)
        {
            if (!c) return;
            // check for same name
            for (size_t i = 0; i < m_count; ++i)
                if (m_members[i]->getName() == c->getName()) return;

            ensure_capacity(m_count + 1);
            m_members[m_count++] = c->clone();
        }

        void removeMember(const std::string& name)
        {
            for (size_t i = 0; i < m_count; ++i)
            {
                if (m_members[i]->getName() == name)
                {
                    delete m_members[i];
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
                std::cout << "No team.\n";
                return;
            }
            std::cout << "[Team] " << m_name << '\n';
            for (size_t i = 0; i < m_count; ++i)
            {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << '\n';
            }
        }
    };
}

#endif
