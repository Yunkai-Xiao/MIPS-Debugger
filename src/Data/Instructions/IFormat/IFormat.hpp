#pragma once

#include "../Instruction_base.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>

class IFormat : public Instruction_base {
  protected:
    unsigned int o_;
    unsigned int s_;
    unsigned int t_;
    unsigned int i_;

  public:
    IFormat(unsigned int o, unsigned int s, unsigned int t, unsigned int i)
        : o_{o}, s_{s}, t_{t}, i_{i} {
        assert(o_ < 64);
        assert(s_ < 32);
        assert(t_ < 32);
        assert(i_ < 65536);
    }
    IFormat(IFormat const &rhs) = default;
    IFormat(IFormat &&rhs) = default;
    ~IFormat() = default;

    IFormat &operator=(IFormat const &rhs) = default;
    IFormat &operator=(IFormat &&rhs) = default;

    int to_binary(bool warn) override {
        if (warn) {
            std::cout
                << "Warning: Arithmetic operation on non-word instruction!"
                << std::endl;
        }
        return i_ | (t_ << 16) | (s_ << 21) | (o_ << 26);
    }
};
