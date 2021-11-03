#pragma once

#include <vector>
#include <string>
#include <memory>    
#include "cargo.hpp"
#include "Time.hpp"
#include "TimeEffectable.hpp"
#include "fruit.hpp"
class Player;

//Class responsible for representing ship in game
class Ship : public TimeEffectable {
public:
    Ship(std::unique_ptr<Time> time);
    Ship(int capacity, int Crew, int speed, const std::string& name, size_t id, std::unique_ptr<Time>  time);
    Ship(int maxCrew, int speed, size_t id, std::unique_ptr<Time>  time);
    ~Ship();
    void setName(const std::string& name) { name_ = name; }

    Ship& operator-=(size_t);
    Ship& operator+=(size_t);
    
    void addCargo(std::unique_ptr<Cargo> );
    void removeCargo(std::unique_ptr<Cargo> , size_t);

    size_t getCapacity() const  { return capacity_; }
    size_t getMaxCrew() const   { return maxCrew_; }
    size_t getSpeed() const     { return speed_; }
    size_t getCrew() const     { return crew_; }
    std::string getName() const { return name_; }
    size_t getId() const        { return id_; }
    std::vector<std::unique_ptr<Cargo>> shipCargo; 

    std::unique_ptr<Cargo> findMatchCargo(std::unique_ptr<Cargo>);
    void load(std::unique_ptr<Cargo>, size_t);
    void unload(std::unique_ptr<Cargo>, size_t);
    void printShipCargo();

    void nextDay(size_t) override;
    void setOwner(std::unique_ptr<Player> );
    void setCrew(size_t );

    size_t calculateAvailableSpace();

protected:
    size_t capacity_;
    size_t maxCrew_;
    size_t crew_;
    size_t speed_;
    std::string name_;
    const size_t id_;
    
    std::unique_ptr<Player> owner_ = nullptr;
    std::unique_ptr<Time> time_;
};
