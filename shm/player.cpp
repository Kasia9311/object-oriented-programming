#include <numeric>
#include <iostream>
#include "cargo.hpp"
#include "player.hpp"
#include "ship.hpp"

Player::Player(std::unique_ptr<Ship> ship, int money, int availableSpace)
    : Storable(money, availableSpace)
{
    ship_ = std::move(ship);
    ship_.get()->setOwner(std::make_unique<Player>(this));
}

Player::~Player() {}

const std::unique_ptr<Ship> &Player::getShip()
{
    return ship_;
}

size_t Player::getSpeed() const
{
    if (ship_->getSpeed() > 0)
    {
        return ship_->getSpeed();
    }
    return 0;
}

std::unique_ptr<Cargo> Player::getCargo(size_t index) const
{
    if (ship_->getCargo().at(index))
    {
        return std::move(ship_->getCargo().at(index));
    }
    return nullptr;
}

size_t Player::calculateAvailableSpace()
{
    int cargoAmount = 0;
    int capacity = (int)ship_->getCapacity();
    std::vector<std::unique_ptr<Cargo>> shipCargo = ship_->getCargo();
    cargoAmount = std::accumulate(shipCargo.begin(), shipCargo.end(), 0, [](int i, std::unique_ptr<Cargo> c)
                                  { return i += (int)c->getAmount(); });

    if (capacity - cargoAmount < 0)
    {
        return 0;
    }
    return (int)(capacity - cargoAmount);
}

void Player::setCrew(size_t newCrewSize)
{
    ship_.get()->setCrew(newCrewSize);
}
