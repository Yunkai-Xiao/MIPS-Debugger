#pragma once

#include "IFormat.hpp"
#include "../../../Machine.hpp"
#include "../Word/word.hpp"

class SW : public IFormat {
  public:
    SW(unsigned int s, unsigned int t, unsigned int i) : IFormat{0b000100, s, t, i} {}
    SW(SW const &rhs) = default;
    SW(SW &&rhs) = default;
    ~SW() = default;

    SW &operator=(SW const &rhs) = default;
    SW &operator=(SW &&rhs) = default;

    void exec(Machine &machine) override;

    Data clone() override { return std::make_unique<SW>(*this); }
    Instruction clone_inst() override { return std::make_unique<SW>(*this); }

    std::ostream &print(std::ostream &out) override {
        out << std::left << std::setw(5) << "sw";
        out << "$" << std::setw(2) << t_ << ",";
        out << std::setw(6) << static_cast<short>(i_) << "(";
        out << "$" << std::setw(2) << s_ << ")";
        out << std::right;
        return out;
    }
};

inline void SW::exec(Machine &machine) {
    long reg_s_ = static_cast<unsigned int>(machine.get_reg(s_));
    int reg_t_ = machine.get_reg(t_);
    int offset = static_cast<short>(i_);
    
    machine.set_mem(reg_s_ + offset, reg_t_);
}
