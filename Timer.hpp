#ifndef TIMER_HPP
#define TIMER_HPP

#include <string>

class Timer {
    public:
        static void startTimer();
        static int getTime();
        static std::string millisToString(int millis);
};

#endif