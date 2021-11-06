#pragma once
#include "coordinates.hpp"
#include "Store.hpp"
#include <memory>

//Class responsible for representing island in game

class Island {
private:
    std::unique_ptr<Store> store_;
    Coordinates position_;
public:
    explicit Island(Coordinates, Time* );
    Coordinates getPosition() { return position_; }
    void SetPosition(const Coordinates& position) { position_ = position; }
    std::unique_ptr<Store> returnIslandStore();
};
