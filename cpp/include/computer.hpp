#pragma once

#include "hardware.hpp"

#include <string>

namespace cyberclub {

class Computer {
public:
    Computer();
    Computer(int id, std::string name, std::string hardwareModel);
    ~Computer();

    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

    bool powerOn();
    bool powerOff();
    bool requestRepair(const std::string& reason);
    bool finishRepair();
    void printStatus() const;

    [[nodiscard]] int id() const;
    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] bool isOn() const;
    [[nodiscard]] bool isBroken() const;

private:
    int m_id;
    std::string m_name;
    Hardware m_hardware;  // composition: owned by value, not a pointer
    bool m_isOn;
};

}  // namespace cyberclub
