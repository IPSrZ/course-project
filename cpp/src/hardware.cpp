#include "hardware.hpp"

#include <iostream>

namespace cyberclub {

Hardware::Hardware() : m_model("unknown"), m_isBroken(false) {
    std::cout << "[ctor] Hardware created: " << m_model << "\n";
}

Hardware::Hardware(std::string model) : m_model(std::move(model)), m_isBroken(false) {
    std::cout << "[ctor] Hardware created: " << m_model << "\n";
}

Hardware::~Hardware() {
    std::cout << "[dtor] Hardware destroyed: " << m_model << "\n";
}

void Hardware::inspect() const {
    std::cout << "  Hardware " << m_model
              << (m_isBroken ? " BROKEN" : " OK");
    if (!m_lastReason.empty()) {
        std::cout << " (" << m_lastReason << ")";
    }
    std::cout << "\n";
}

bool Hardware::markBroken(const std::string& reason) {
    if (m_isBroken) {
        std::cout << "  [rule] already broken, refuse\n";
        return false;
    }
    if (reason.empty()) {
        std::cout << "  [rule] reason required\n";
        return false;
    }
    m_isBroken = true;
    m_lastReason = reason;
    std::cout << "  marked broken: " << reason << "\n";
    return true;
}

bool Hardware::markFixed() {
    if (!m_isBroken) {
        std::cout << "  [rule] not broken, nothing to fix\n";
        return false;
    }
    m_isBroken = false;
    m_lastReason.clear();
    std::cout << "  marked fixed\n";
    return true;
}

bool Hardware::isBroken() const {
    return m_isBroken;
}

const std::string& Hardware::model() const {
    return m_model;
}

}  // namespace cyberclub
