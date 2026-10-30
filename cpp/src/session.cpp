#include "session.hpp"

#include <iostream>

namespace cyberclub {

Session::Session() : m_id(0), m_clientName("guest"), m_computer(nullptr), m_isActive(false), m_minutes(0) {
    std::cout << "[ctor] Session created: id=" << m_id << "\n";
}

Session::Session(int id, std::string clientName, Computer* computer)
    : m_id(id),
      m_clientName(std::move(clientName)),
      m_computer(computer),
      m_isActive(false),
      m_minutes(0) {
    std::cout << "[ctor] Session created: id=" << m_id << " client=" << m_clientName << "\n";
}

Session::~Session() {
    std::cout << "[dtor] Session destroyed: id=" << m_id
              << " (computer is NOT deleted)\n";
}

bool Session::start() {
    if (m_computer == nullptr) {
        std::cout << "  [rule] no computer attached\n";
        return false;
    }
    if (m_computer->isBroken()) {
        std::cout << "  [rule] computer broken, refuse start\n";
        return false;
    }
    if (m_isActive) {
        std::cout << "  [rule] session already active\n";
        return false;
    }
    if (!m_computer->isOn()) {
        if (!m_computer->powerOn()) {
            return false;
        }
    }
    m_isActive = true;
    m_minutes = 0;
    std::cout << "  session " << m_id << " started for " << m_clientName << "\n";
    return true;
}

bool Session::addTime(int minutes) {
    if (!m_isActive) {
        std::cout << "  [rule] session not active\n";
        return false;
    }
    if (minutes <= 0) {
        std::cout << "  [rule] minutes must be > 0\n";
        return false;
    }
    m_minutes += minutes;
    std::cout << "  added " << minutes << " min, total " << m_minutes << "\n";
    return true;
}

bool Session::end() {
    if (!m_isActive) {
        std::cout << "  [rule] session not active\n";
        return false;
    }
    m_isActive = false;
    std::cout << "  session " << m_id << " ended, minutes=" << m_minutes << "\n";
    return true;
}

void Session::printStatus() const {
    std::cout << "Session #" << m_id << " client=" << m_clientName
              << (m_isActive ? " ACTIVE" : " idle")
              << " minutes=" << m_minutes << "\n";
    if (m_computer != nullptr) {
        std::cout << "  uses computer: " << m_computer->name() << "\n";
    } else {
        std::cout << "  no computer\n";
    }
}

int Session::id() const {
    return m_id;
}

bool Session::isActive() const {
    return m_isActive;
}

}  // namespace cyberclub
