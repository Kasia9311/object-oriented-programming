#pragma once
#include <iostream>
#include <memory>
#include "Map.hpp"
#include "Menu.hpp"
#include "player.hpp"
#include "Time.hpp"
#include "coordinates.hpp"
class Game
{
public:
    Game(size_t money, size_t gameDays, size_t finalGoal);
    Game();

    void displayPlayerStats();
    void setPlayer();
    void startGame();
    void printTitle();
    void printMap(Map &);
    void travel();
    void buyCargo();
    void sellCargo();
    void setStartingCargo();
    void printPlayerCargo();
    void quitRequested();
    void printStoreCargo();
    void endGameWin();
    void endGameLose();
    
private:
    std::unique_ptr<Time> time_;
    size_t money_;
    size_t gameDays_;
    size_t finalGoal_;
    bool quitRequest = false;
    std::unique_ptr<Menu> menu_;
    std::unique_ptr<Map> map_;
    std::unique_ptr<Store> currentStore_;
    std::unique_ptr<Player> playerOne_;
};