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
    Map(std::unique_ptr<Time> time);
    void DebugPrintIsland();
    void PrintCurrentPosition();
    friend class Game;
    std::unique_ptr<Island> getCurrentPos() {return std::move(current_pos_);}
    void changeCurrentPosition(std::unique_ptr<Island> position) {current_pos_ = std::move(position);}
    size_t calculateDistance(std::unique_ptr<Island>);
    std::unique_ptr<Island> getIsland(const Coordinates &);
    void addIsland(Coordinates &, std::unique_ptr<Time>);

private:
    std::unique_ptr<Island> current_pos_;
    std::vector<std::unique_ptr<Island>> islands_;
    bool contains(const std::vector<Coordinates>&, const Coordinates&);
    void SetUpRandomIsland(std::unique_ptr<Time>);
};
