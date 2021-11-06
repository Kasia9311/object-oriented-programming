#include "island.hpp"

Island::Island(Coordinates position, Time* time) 
    : store_(1000, 100, time), //<---------------------------no idea what to do
     position_(position)
    {}

std::unique_ptr<Store> Island::returnIslandStore()
{
    return std::move(store_);
}