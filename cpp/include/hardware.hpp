#pragma once

#include <string>

namespace cyberclub {

class Hardware {
public:
    Hardware();
    explicit Hardware(std::string model);
    ~Hardware();

    Hardware(const Hardware&) = delete;
    Hardware& operator=(const Hardware&) = delete;

    void inspect() const;
    bool markBroken(const std::string& reason);
    bool markFixed();

    [[nodiscard]] bool isBroken() const;
    [[nodiscard]] const std::string& model() const;

private:
    std::string m_model;
    bool m_isBroken;
    std::string m_lastReason;
};

}  // namespace cyberclub
