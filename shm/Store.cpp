#include <algorithm>
#include "cargo.hpp"
#include "player.hpp"
#include "Time.hpp"
#include "Store.hpp"

constexpr size_t numberOfPossibleFruitCargo = 4;
constexpr size_t numberOfPossibleAlcoholCargo = 4;
constexpr size_t numberOfPossibleItemCargo = 4;

std::vector<std::string> possibleFruitCargoNames = {"Banana", "Pineapple", "Apple", "Pear"};
std::vector<std::string> possibleAlcoholCargoNames = {"Whiskey", "Rum", "Vodka", "Beer"};
std::vector<std::string> possibleItemCargoNames = {"Rope", "Hook", "Screw", "Spoon"};
std::vector<Rarity> rarityChoice = {Rarity::common, Rarity::rare, Rarity::epic, Rarity::legendary};

Store::Store(int money, size_t availableSpace, std::unique_ptr<Time> time) : Storable(money, availableSpace, std::move(time))

{
    storeCargo.reserve(20);
    SetUpRandomCargo(std::move(time));
    storeCargo.shrink_to_fit();
}

Store::~Store() {}

void Store::SetUpRandomCargo(std::unique_ptr<Time> time)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> fruitCargoDistrib(0, numberOfPossibleFruitCargo);
    std::uniform_real_distribution<> alcoholCargoDistrib(0, numberOfPossibleAlcoholCargo);
    std::uniform_real_distribution<> itemCargoDistrib(0, numberOfPossibleItemCargo);
    std::uniform_real_distribution<> fruitPrice(10, 25);
    std::uniform_real_distribution<> alcoholPrice(50, 100);
    std::uniform_real_distribution<> itemPrice(100, 300);
    std::uniform_real_distribution<> quantity(1, 50);
    std::uniform_real_distribution<> percentage(20, 100);
    std::uniform_real_distribution<> itemRarity(0, (int)rarityChoice.size() - 1.0);

    Rarity randomRarity = rarityChoice[(int)itemRarity(gen)];
    size_t fruitCargoNumber = (size_t)fruitCargoDistrib(gen);
    size_t alcoholCargoNumber = (size_t)alcoholCargoDistrib(gen);
    size_t itemCargoNumber = (size_t)itemCargoDistrib(gen);
    size_t fruitPriceX = (size_t)fruitPrice(gen);
    size_t alcoholPriceX = (size_t)alcoholPrice(gen);
    size_t itemPriceX = (size_t)itemPrice(gen);
    size_t cargoQuantity = (size_t)quantity(gen);
    size_t alcoholPercentage = (size_t)percentage(gen);

    std::string fruitCargoName = possibleFruitCargoNames[fruitCargoNumber];
    std::string alcoholCargoName = possibleAlcoholCargoNames[alcoholCargoNumber];
    std::string itemCargoName = possibleItemCargoNames[itemCargoNumber];

    storeCargo.emplace_back(new Fruit(fruitCargoName, (cargoQuantity + 10), fruitPriceX, std::move(time), 15, 0));
    storeCargo.emplace_back(new Alcohol(alcoholCargoName, cargoQuantity, alcoholPriceX, std::move(time), alcoholPercentage));
    storeCargo.emplace_back(new Item(itemCargoName, (cargoQuantity / 2), itemPriceX, std::move(time), randomRarity));
}

std::unique_ptr<Cargo> Store::findMatchCargo(std::unique_ptr<Cargo> cargo)
{
    for (auto &el : storeCargo)
    {
        if (*el == *cargo)
        {
            return std::move(el);
        }
    }

    return nullptr;
}

Response Store::buy(std::unique_ptr<Cargo> cargo, size_t amount, std::unique_ptr<Player> player)
{
    if (findMatchCargo(std::move(cargo)))
    {
        auto price = 0;
        price = (int)(amount * cargo->getPrice());

        if (player->getAvailableSpace() < amount)
        {
            std::cout << "Lack of space" << '\n';
            return Response::lack_of_space;
        }
        if (cargo->getAmount() < amount)
        {
            std::cout << "Lack of cargo" << '\n';
            return Response::lack_of_cargo;
        }
        if (player->getMoney() < price)
        {
            std::cout << "Lack of money" << '\n';
            return Response::lack_of_money;
        }

        money_ += price;
        player->SpendMoney(price);
        player->getShip()->load(std::move(cargo), amount);

        return Response::done;
    }
    else
    {
        return Response::lack_of_cargo;
    }
}

Response Store::sell(std::unique_ptr<Cargo> cargo, size_t amount, std::unique_ptr<Player> player)
{
    if (player->getShip()->findMatchCargo(std::move(cargo)))

    {
        auto price = 0;
        price = (int)(amount * cargo->getPrice());
        if (getAvailableSpace() < amount)
        {
            std::cout << "Lack of space" << '\n';

            return Response::lack_of_space;
        }
        if (player->getShip()->findMatchCargo(std::move(cargo))->getAmount() < amount)
        {
            std::cout << "Lack of cargo" << '\n';

            return Response::lack_of_cargo;
        }
        if (money_ < (int)(amount * cargo->getBasePrice()))
        {
            std::cout << "Lack of money" << '\n';

            return Response::lack_of_money;
        }
        if (money_ < price)
        {
            std::cout << "Lack of money" << '\n';

            return Response::lack_of_money;
        }

        money_ -= price;

        addStoreCargo(std::move(cargo));
        player->getShip()->unload(std::move(cargo), amount);
        player->EarnMoney(price);

        return Response::done;
    }
    else
    {
        return Response::lack_of_cargo;
    }

    return Response::done;
}

std::unique_ptr<Cargo> Store::getCargo(size_t index) const
{
    return nullptr;
}

void Store::nextDay(size_t elapsedTime)
{
    for (auto & el : storeCargo)
    {
        el->reduceAmount(1);
    }
}

void Store::printStoreCargo()
{
    auto i = 0;
    for (auto & el : storeCargo)
    {
        std::cout << '\n';
        el->printCargo(i);
        i++;
    }
}

void Store::removeCargo(std::unique_ptr<Cargo> item, size_t amount)
{
    auto storeCargoAmount = findMatchCargo(std::move(item))->getAmount();
    if (storeCargoAmount == amount)
    {
        auto i = std::find(begin(storeCargo), end(storeCargo), item);
        storeCargo.erase(i);
    }
    else
    {
        findMatchCargo(std::move(item))->reduceAmount(amount);
    }
}

void Store::addStoreCargo(std::unique_ptr<Cargo> item)
{
    auto cargoPtr = findMatchCargo(std::move(item));
    if (cargoPtr)
    {
        cargoPtr->increaseAmount(item->getAmount());
    }
    else
    {
        storeCargo.emplace_back(item);
    }
}
