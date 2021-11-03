#include <algorithm>
#include <iostream>
#include <numeric>
#include "ship.hpp"
#include "player.hpp"
#include "fruit.hpp"
#include "alcohol.hpp"
#include "item.hpp"

Ship::Ship(std::unique_ptr<Time> time)
    : id_(-1), time_(std::move(time))
{
    time_->attach(std::make_unique<TimeEffectable>(this));
}

Ship::Ship(int capacity, int Crew, int speed, const std::string &name, size_t id, std::unique_ptr<Time> time)
    : capacity_(capacity), crew_(Crew), speed_(speed), name_(name), id_(id), time_(std::move(time))
{}

Ship::Ship(int maxCrew, int speed, size_t id, std::unique_ptr<Time> time)
    : Ship(0, maxCrew, speed, "", id, std::move(time))
{}

Ship::~Ship()
{
    time_->detach(std::make_unique<TimeEffectable>(this));
}

Ship &Ship::operator-=(size_t num)
{
    if (crew_ < num)
    {
        crew_ = 0;
    }
    else
    {
        crew_ -= num;
    }
    return *this;
}

Ship &Ship::operator+=(size_t num)
{
    crew_ += num;
    return *this;
}

void Ship::addCargo(std::unique_ptr<Cargo> item)
{
    auto cargoPtr = findMatchCargo(std::move(item));
    if (cargoPtr)
    {
        cargoPtr->increaseAmount(item->getAmount());
    }
    else
    {
        shipCargo.emplace_back(std::move(item));
    }
}

void Ship::removeCargo(std::unique_ptr<Cargo> item, size_t amount)
{
    const auto shipCargoAmount = findMatchCargo(std::move(item))->getAmount();
    if (shipCargoAmount == amount)
    {
        const auto it = std::find_if(shipCargo.begin(), shipCargo.end(), [&item](std::unique_ptr<Cargo> el)
                                     { return &el == &item; });
        if (it != shipCargo.end())
        {
            shipCargo.erase(it);
        }
    }
    else
    {
        findMatchCargo(std::move(item))->reduceAmount(amount);
    }
}

std::unique_ptr<Cargo> Ship::findMatchCargo(std::unique_ptr<Cargo> cargo)
{
    auto foundCargo = std::find_if(shipCargo.begin(), shipCargo.end(), [&cargo](std::unique_ptr<Cargo> &c)
                  {
                      return (c == cargo);
                  });
    auto cargoPosition = std::distance(shipCargo.begin(), foundCargo);
    shipCargo[cargoPosition];
}

void Ship::load(std::unique_ptr<Cargo> loadCargo, size_t amount)
{
    if (amount <= calculateAvailableSpace())
    {
        loadCargo->reduceAmount(amount);
        auto toAdd = loadCargo->clone();
        toAdd->setAmount(amount);
        addCargo(std::move(toAdd));
    }
}

void Ship::unload(std::unique_ptr<Cargo> unloadCargo, size_t amount)
{
    // Checking if we have enough cargo to unload

    if (auto shipCargo = findMatchCargo(std::move(unloadCargo)))
    {
        if (shipCargo->getAmount() >= amount)
        {
            removeCargo(std::move(unloadCargo), amount);
        }
        else
        {
            std::cout << "Ship: " << this->getName() << " doesn't have enough cargo: " << unloadCargo->getName() << '\n';
        }
    }
    else
    {
        std::cout << "Ship: " << this->getName() << "doesn't have cargo: " << unloadCargo->getName() << '\n';
    }
}

void Ship::setOwner(std::unique_ptr<Player> newOwner)
{
    owner_ = std::move(newOwner);
}

void Ship::setCrew(size_t newCrew)
{
    if (newCrew <= maxCrew_)
    {
        crew_ = newCrew;
    }
}

void Ship::nextDay(size_t elapsedTime)
{
    size_t moneyForCrew = crew_;
    for (auto i = 0; i < (int)elapsedTime; i++)
    {
        if (owner_)
        {
            owner_->SpendMoney((int)moneyForCrew);
        }
    }
}

void Ship::printShipCargo()
{
    auto i = 0;
    std::cout << "Ship Cargo:" << '\n';
    for (auto &el : shipCargo)
    {
        std::cout << '\n';
        el->printCargo(i);
        i++;
    }
}

size_t Ship::calculateAvailableSpace()
{
    int cargoAmount = 0;
    cargoAmount = std::accumulate(shipCargo.begin(), shipCargo.end(), 0, [](int i, Cargo *c)
                                  { return i += (int)c->getAmount(); });
    if ((int)capacity_ - cargoAmount < 0)
    {
        return 0;
    }
    return capacity_ - cargoAmount;
}
