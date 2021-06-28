#include "cargo.hpp"

Cargo &Cargo::operator+=(size_t amount)
{
    amount_ += amount;
    return *this;
}

Cargo &Cargo::operator-=(size_t amount)
{
    amount_ -= amount;
    return *this;
}

bool Cargo::operator==(const Cargo &cargo) const
{
    return name_ == cargo.name_ && amount_ == cargo.amount_ && basePrice_ == cargo.basePrice_;
}
