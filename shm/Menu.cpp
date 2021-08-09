#include<limits>
#include "Menu.hpp"
#include "Game.hpp"

Menu::Menu(Game* game)
    : game_(game)
    {}

Menu::~Menu() {}

void Menu::playerChoice()
{
    size_t option{};
    do {
        std::cout << "What is your choice capt'n? ";
        std::cin >> option;
    } while (!isPlayerChoiceValid(option));
    item_ = static_cast<MenuItem>(option);
    menuChoice(item_);
}

bool Menu::isPlayerChoiceValid(const size_t &playerAnswer)
{
    if(std::cin.fail() || playerAnswer < 0 || playerAnswer > 5)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong answer, please use numbers 1 - 5" << '\n';
        return false;
    }
    return true;
}

void Menu::menuChoice(MenuItem item)
{
    switch(item)
    {
        case MenuItem::buyCargo:
            game_->buyAllCargo();
            break;
        case MenuItem::sellCargo:
            game_->sellAllCargo();
            break;
        case MenuItem::travel:
            game_->travel();
            break;
        case MenuItem::Exit:
            game_->quitRequested();
            break;
        case MenuItem::printPlayerCargo:
            game_->printPlayerCargo();
            break;
        default:
            std::cout << "Wrong choice, please use numbers 1-5" << '\n';
            break;
    }
}

void Menu::printMenu()
{
    std::cout << "==========================\n";
    std::cout << "1 - Print Cargo\n";
    std::cout << "2 - Buy Cargo\n";
    std::cout << "3 - Sell Cargo\n";
    std::cout << "4 - Travel\n";
    std::cout << "5 - Exit\n";
    std::cout << "==========================\n";
}

