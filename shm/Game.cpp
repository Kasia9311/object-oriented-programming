#include "Game.hpp"
#include <limits>

class Map;

Game::Game(size_t money, size_t gameDays, size_t finalGoal)
    : time_(std::make_unique<Time>()),
      money_(money),
      gameDays_(gameDays),
      finalGoal_(finalGoal),
      menu_(std::make_unique<Menu>(this)),
      map_(std::make_unique<Map>(time_)),
      playerOne_(std::make_unique<Player>(std::make_unique<Ship>(20, 30, 10, "Dar Pomorza", 3, time_), 1000, 1000))

{}

Game::Game() {}

void Game::startGame()
{
    printTitle();
    setPlayer();

    while (true)
    {
        if (playerOne_->getMoney() >= 2000)
        {
            endGameWin();
            quitRequested();
        }
        else if (playerOne_->getMoney() < 0 || time_->getCurrentTime() >= gameDays_)
        {
            endGameLose();
            quitRequested();
        }
        if (quitRequest)
        {
            break;
        }
        menu_->printMenu();
        menu_->playerChoice();
    }
}

void Game::printTitle()
{
    std::cout << "Project SHM" << '\n';
}

void Game::setPlayer()
{
    std::cout << "Set your name captain!:" << '\n';
    std::string playerName;
    std::cin >> playerName;
    playerOne_->setName(playerName);
    setStartingCargo();
    std::cout << "Welcome on board captain " << playerOne_->getName() << '\n';
    map_->changeCurrentPosition(std::move(map_->islands_.at(0)));
    currentStore_ = map_->islands_.at(0)->returnIslandStore();
    std::cout << "Your's ship " << playerOne_->getShip()->getName() << " is waiting! Good Luck!" << '\n';
    std::cout << "You are in start point. ";
    map_->PrintCurrentPosition();
    std::cout << "You have " << playerOne_->getMoney() << " gold in Your treasure chest!" << '\n';
    std::cout << "Choose Your next move!" << '\n';
}

void Game::printMap(Map &map)

{
    map.PrintCurrentPosition();
    map.DebugPrintIsland();
}

void Game::travel()

{
    auto i = 0;
    printMap(*map_);
    std::cout << "Choose Your destination captain!" << '\n';
    std::cin >> i;
    if (isdigit(i) && i < (int)map_->islands_.size() && i >= 0)
    {
        auto travelTime = map_->calculateDistance(std::move(map_->islands_.at(i))) / playerOne_->getSpeed();
        std::cout << "Your travel will take " << travelTime << " days." << '\n';
        map_->changeCurrentPosition(std::move(map_->islands_.at(i)));
        map_->PrintCurrentPosition();
        time_->changeTime(travelTime);
        currentStore_ = map_->islands_.at(i)->returnIslandStore();
    }
    else
    {
        std::cout << "There is no such island on the map! Choose another destination!" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Game::travel();
    }
}

void Game::printPlayerCargo()
{
    playerOne_->getShip()->printShipCargo();
}

void Game::setStartingCargo()
{
    playerOne_->getShip()->shipCargo.emplace_back(std::make_unique<Fruit> ("Banany", 1, 40, std::move(time_), 5, 0));
    playerOne_->getShip()->shipCargo.emplace_back(std::make_unique<Fruit> ("Apple", 1, 14, std::move(time_), 20, 0));
    playerOne_->getShip()->shipCargo.emplace_back(std::make_unique<Alcohol>("Rum", 1, 60, std::move(time_), 70));
    playerOne_->getShip()->shipCargo.emplace_back(std::make_unique<Item>("Hook", 1, 100, std::move(time_), Rarity::common));
}

void Game::quitRequested()
{
    quitRequest = true;
}

void Game::displayPlayerStats()
{
    std::cout << "(Little reminder)" << '\n';
    std::cout << "Available gold: " << playerOne_->getMoney() << '\n';
    std::cout << "Your position on the map: \n";
    map_->PrintCurrentPosition();
    std::cout << "Day " << time_->getCurrentTime() << "/" << gameDays_ << '\n';
    std::cout << "==========================\n";
}

void Game::printStoreCargo()
{
    std::cout << "This store contains: " << '\n';
    currentStore_->printStoreCargo();
}

void Game::buyCargo()
{
    int cargoElement = 0;
    size_t amount = 0;
    std::cout << "Choose cargo: ";
    std::cin >> cargoElement;
    if (cargoElement >= 0 && cargoElement < (int)currentStore_->storeCargo.size())
    {
        std::cout << "Choose amount: ";
        std::cin >> amount;
        currentStore_->buy(std::move(currentStore_->storeCargo.at(cargoElement)), amount, std::move(playerOne_));
    }
    else
    {
        std::cout << "There is no such cargo in this store." << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        buyCargo();
    }
}

void Game::sellCargo()
{
    int cargoElement = 0;
    size_t amount = 0;
    std::cout << "Choose cargo: ";
    std::cin >> cargoElement;
    if (cargoElement >= 0 && cargoElement < (int)playerOne_->getShip()->shipCargo.size())
    {
        std::cout << "Choose amount: ";
        std::cin >> amount;
        currentStore_->sell(playerOne_->getCargo(cargoElement), amount, std::move(playerOne_));
    }
    else
    {
        std::cout << "There is no such cargo in this ship." << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        sellCargo();
    }
}

void Game::endGameLose()
{
    std::cout << "You're time has come Captain! This is sad end!" << '\n';
}
void Game::endGameWin()

{
    std::cout << "Arrr you won" << '\n';
}