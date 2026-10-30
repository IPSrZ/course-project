#include "computer.hpp"

#include <iostream>

namespace cyberclub {

Computer::Computer() : m_id(0), m_name("unnamed"), m_hardware(), m_isOn(false) {
    std::cout << "[ctor] Computer created: " << m_name << "\n";
}

Computer::Computer(int id, std::string name, std::string hardwareModel)
    : m_id(id), m_name(std::move(name)), m_hardware(std::move(hardwareModel)), m_isOn(false) {
    std::cout << "[ctor] Computer created: id=" << m_id << " name=" << m_name << "\n";
}

Computer::~Computer() {
    std::cout << "[dtor] Computer destroyed: id=" << m_id << " name=" << m_name << "\n";
}

bool Computer::powerOn() {
    if (m_hardware.isBroken()) {
        std::cout << "  [rule] cannot power on, hardware broken\n";
        return false;
    }
    if (m_isOn) {
        std::cout << "  [rule] already on\n";
        return false;
    }
    m_isOn = true;
    std::cout << "  " << m_name << " powered on\n";
    return true;
}

bool Computer::powerOff() {
    if (!m_isOn) {
        std::cout << "  [rule] already off\n";
        return false;
    }
    m_isOn = false;
    std::cout << "  " << m_name << " powered off\n";
    return true;
}

bool Computer::requestRepair(const std::string& reason) {
    if (m_isOn) {
        powerOff();
    }
    return m_hardware.markBroken(reason);
}

bool Computer::finishRepair() {
    return m_hardware.markFixed();
}

void Computer::printStatus() const {
    std::cout << "Computer #" << m_id << " " << m_name
              << (m_isOn ? " ON" : " OFF") << "\n";
    m_hardware.inspect();
}

int Computer::id() const {
    return m_id;
}

const std::string& Computer::name() const {
    return m_name;
}

bool Computer::isOn() const {
    return m_isOn;
}

bool Computer::isBroken() const {
    return m_hardware.isBroken();
}

}  // namespace cyberclub
