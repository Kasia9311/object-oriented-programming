#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Storable.hpp"
#include "alcohol.hpp"
#include "cargo.hpp"
#include "fruit.hpp"
#include "item.hpp"
#include "TimeEffectable.hpp"
#include "cargo.hpp"


class Time;

class Player;
//class Cargo;

enum class Response 
{
    done,
    lack_of_money,
    lack_of_cargo,
    lack_of_space 
};

class Store: public Storable {
public:
    Store(int money, size_t availableSpace, Time* time);
    
    virtual ~Store();   
    Response buy(std::unique_ptr<Cargo> cargo, size_t amount, std::unique_ptr<Player> player);
    Response sell(std::unique_ptr<Cargo> cargo, size_t amount, std::unique_ptr<Player> player);

    std::unique_ptr<Cargo> getCargo(size_t) const override;
    std::unique_ptr<Cargo> findMatchCargo(std::unique_ptr<Cargo>);
    std::vector<std::unique_ptr<Cargo>> storeCargo;

    void addStoreCargo(std::unique_ptr<Cargo>);
    void removeCargo(std::unique_ptr<Cargo>, size_t);    
    void nextDay(size_t) override;
    void printStoreCargo();

    friend std::ostream& operator<<(std::ostream& out, const Store& store) {
        out << "Store: \n";
        for (auto & el : store.storeCargo) {
            out << el->getCargoInfo();
        }

        return out;
    }
private:
    void SetUpRandomCargo(Time*);
};
