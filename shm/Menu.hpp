#pragma once
#include <iostream>
#include <memory>
#include "Map.hpp"
#include "Store.hpp"

class Game;

class Menu 
{
public:
    Menu(Game*);
    ~Menu();
    enum MenuItem
    {
        printPlayerCargo,
        printStoreCargo,
        buyCargo,
        sellCargo,
        travel,
        Exit,
    };

    void playerChoice();
    bool isPlayerChoiceValid(const size_t &playerAnswer) const;
    void menuChoice(MenuItem) const;
    void printMenu() const;  

private:
    MenuItem item_;
    Game* game_;
};
