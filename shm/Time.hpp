#pragma once

#include <list>
#include <memory>

class TimeEffectable;

class Time {
public:
    Time();
    ~Time();

    void attach(std::unique_ptr<TimeEffectable> observer);
    void detach(std::unique_ptr<TimeEffectable> observer);
    void notify(size_t &);
    void changeTime(size_t);
    void HowManyObserver();
    size_t getCurrentTime() { return currentTime_; }
    
private:
    std::list<std::unique_ptr<TimeEffectable>> list_observer_;
    size_t currentTime_;
};