#pragma once
#include "island.hpp"
#include "Time.hpp"
#include <vector>
#include <memory>

//class Island;
class Coordinates;

//Class responsible for representing map in game
class Map {
public:
    Map(Time* time);
    void DebugPrintIsland();
    void PrintCurrentPosition();
    friend class Game;
    std::unique_ptr<Island> getCurrentPos() {return std::move(current_pos_);}
    std::unique_ptr<Store> returnCurrentIslandStore() {return current_pos_->returnIslandStore();}
    void changeCurrentPosition(std::unique_ptr<Island> position) {current_pos_ = std::move(position);}
    size_t calculateDistance(std::unique_ptr<Island>);
    std::unique_ptr<Island> getIsland(const Coordinates &);
    void addIsland(Coordinates &, Time*);

private:
    std::unique_ptr<Island> current_pos_;
    std::vector<std::unique_ptr<Island>> islands_;
    bool contains(const std::vector<Coordinates>&, const Coordinates&);
    void SetUpRandomIsland(Time*);
};
