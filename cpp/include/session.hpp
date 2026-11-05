#pragma once

#include "computer.hpp"

#include <memory>
#include <string>

namespace cyberclub {

class Session {
public:
    Session();
    Session(int id, std::string clientName, std::weak_ptr<Computer> computer);
    ~Session();

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    bool start();
    bool addTime(int minutes);
    bool end();
    void printStatus() const;

    [[nodiscard]] int id() const;
    [[nodiscard]] bool isActive() const;

private:
    int m_id;
    std::string m_clientName;
    std::weak_ptr<Computer> m_computer;  // aggregation: observe, do not own
    bool m_isActive;
    int m_minutes;
};

}  // namespace cyberclub
