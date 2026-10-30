#pragma once

#include "computer.hpp"

#include <string>

namespace cyberclub {

class Session {
public:
    Session();
    Session(int id, std::string clientName, Computer* computer);
    ~Session();

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    bool start();
    bool addTime(int minutes);
    bool end();
    void printStatus() const;

    int id() const;
    bool isActive() const;

private:
    int m_id;
    std::string m_clientName;
    Computer* m_computer;  // aggregation: pointer, not owned
    bool m_isActive;
    int m_minutes;
};

}  // namespace cyberclub
