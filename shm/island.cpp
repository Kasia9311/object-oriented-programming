#include "island.hpp"

Island::Island(Coordinates position, std::unique_ptr<Time> time) 
    : store_(1000, 100, std::move(time)),
     position_(position)
    {}

std::unique_ptr<Store> Island::returnIslandStore()
{
    return std::make_unique<Store>(store_);
}