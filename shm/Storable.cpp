#include "Storable.hpp"

Storable::Storable(int money, size_t availableSpace)
    : money_(money), availableSpace_(availableSpace)
{}

Storable::Storable(int money, size_t availableSpace, std::unique_ptr<Time> time)
    : money_(money), availableSpace_(availableSpace), time_(std::move(time))
{
    time_->attach(std::make_unique<TimeEffectable>(this));
}

Storable::~Storable() {}

void Storable::SpendMoney(int moneyToSpend)
{
    if (money_ - moneyToSpend <= 0)
    {
        money_ = 0;
    }
    money_ -= moneyToSpend;
}
void Storable::EarnMoney(int moneyToEarn)
{
    if (moneyToEarn > 0)
    {
        money_ += moneyToEarn;
    }
}
