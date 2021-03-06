#pragma once

#include "../../../Machine.hpp"
#include "../Word/word.hpp"
#include "RFormat.hpp"

class DIV : public RFormat {
  public:
    DIV(unsigned int s, unsigned int t) : RFormat{s, t, 0, 0b011010} {}
    DIV(DIV const &rhs) = default;
    DIV(DIV &&rhs) = default;
    ~DIV() = default;

    DIV &operator=(DIV const &rhs) = default;
    DIV &operator=(DIV &&rhs) = default;

    void exec(Machine &machine) override;

    Data clone() override { return std::make_unique<DIV>(*this); }
    Instruction clone_inst() override { return std::make_unique<DIV>(*this); }

    std::ostream &print(std::ostream &out) override {
        return RFormat::print(out, "div", -1, s_, t_);
    }
};

inline void DIV::exec(Machine &machine) {
    int reg_s_ = machine.get_reg(s_);
    int reg_t_ = machine.get_reg(t_);

    if (reg_t_ == 0) {
        throw std::runtime_error{"Error: Dividing zero!"};
    }

    machine.set_high(reg_s_ % reg_t_);
    machine.set_low(reg_s_ / reg_t_);
}