
#include <iostream>

#include "alcohol.hpp"
#include "cargo.hpp"
#include "coordinates.hpp"
#include "dryfruit.hpp"
#include "fruit.hpp"
#include "island.hpp"
#include "item.hpp"
#include "Map.hpp"
#include "player.hpp"
#include "ship.hpp"
#include "Storable.hpp"
#include "Store.hpp"
#include <memory>


int main()
{
    
    // std::cout << "Test Cargo" << '\n';

    // Cargo cotton("banany", 15, 150); // ( name, amount, basePrice) bananas does not work, imagine why?
    // Cargo kryptonite("krypton", 20, 200); // ( name, amount, basePrice)
    // Cargo onion("cebula", 250, 1); // ( name, amount, basePrice)

    // std::cout << (onion == cotton) << " " << (cotton == kryptonite) << " " << (onion == kryptonite) << "\n";
    // std::cout << cotton.getAmount() << " " << cotton.getBasePrice() << " " << cotton.getName() << "\n\n";

    // //cotton -= 100;
   
    // std::cout << "Test islands" << '\n';

    // Coordinates miami(125.f, 174.f);
    // Coordinates breslau(180.f, 115.f);
    // Coordinates chicago(125.f, 174.f);
    // std::cout << (breslau == miami) << " " << (chicago == breslau) << " " << (miami == chicago) << "\n\n";

    // std::cout << "Test ship Titanic" << '\n';
     
    // Ship Titanic(20, 90, 1);
    // //Titanic.addCargo(std::shared_ptr<Cargo>(kryptonite));
    // Titanic.load(std::make_shared<Cargo>(kryptonite));

    // std::cout << "Vector size: " << Titanic.getCargo().size() << '\n';
    // std::cout << "Titanic cargo: " << Titanic.getCargo()[0]->getName() << '\n';
    // std::cout << Titanic.getCargo()[0]->getAmount() << "\n\n";
    
    // std::cout << "Test make_unique ptr ship" << '\n';
    // auto ship = std::make_unique<Ship>(20, 1, 2, "titanic", 3);
    // ship->load(std::make_shared<Cargo>(cotton));
    // size_t shipCargoSize = ship->getCargo().size();
    // Player player(std::move(ship), 1, 1);
    // std::cout << "Vector size: " << shipCargoSize << '\n';
    // std::cout << "Player's ship speed: " << player.getShip()->getSpeed() << '\n';
    // std::cout << "Player's ship cargo name: " << player.getCargo(0)->getName() << '\n';
    // std::cout << "Player's ship cargo (should be 15): " << player.getCargo(0)->getAmount() << '\n';
    // std::cout << "Player's ship cargo base price: " << player.getCargo(0)->getBasePrice() << '\n';
    
    // std::cout << "Available space: " << player.getAvailableSpace() << "\n\n";

    // std::cout << "Random islands positions: X | Y" << '\n';
    // Map map;
    // map.DebugPrintIsland();

    // std::cout << '\n' << "Get miami position: X | Y" << '\n';
    // map.addIsland(miami);
    // Island *is = map.getIsland(miami);
    // std::cout << is->getPosition().GetPositionX() << " " << is->getPosition().GetPositionY() << '\n';

    // std::cout << "Test Store" << '\n';
    // Store store(100, 500); //(Money, Avalivable space)
    // store.cargo_.push_back(std::make_shared<Cargo>(cotton));
    // store.cargo_.push_back(std::make_shared<Cargo>(kryptonite));
    // std::cout << store.findMatchCargo(&cotton) << " adres cotton: " << store.cargo_[0].get() <<'\n';
    // store.sell(&onion, 5, &player);
    // store.sell(&onion, 55, &player);
    // std::cout << "Print store cargo" << '\n';
    // store.printStoreCargo();

/*
    Alcohol a("A", 1, 1, 96);
    Fruit f("F", 1, 1, 5000, 1);
    //DryFruit* df = new Fruit("DF", 1, 1, 12, 1);
    Item i("I", 1, 1, Rarity::common);

    std::cout << "Alcohol: " << a.getPrice() << "\n";
    std::cout << "Fruit: " << f.getPrice() << "\n";
    std::cout << "Item: " << i.getPrice() << "\n";

    a.nextDay();
    f.nextDay();
    i.nextDay();

    std::cout << "Alcohol: " << a.getPrice() << "\n";
    std::cout << "Fruit: " << f.getPrice() << "\n";
    std::cout << "Item: " << i.getPrice() << "\n";

    Store store(100, 500); //(Money, Avalivable space)
    Fruit cotton("banany", 15, 150,1,1); // ( name, amount, basePrice) bananas does not work, imagine why?
    Fruit kryptonite("krypton", 20, 200,1,1); // ( name, amount, basePrice)

    store.cargo_.push_back(std::make_shared<Fruit>(cotton));
    store.cargo_.push_back(std::make_shared<Fruit>(kryptonite));

    std::cout << store;*/

}