#include "Timer.hpp"

// =================================== TIMERS ====================================

// Controllers
#define REG_TM0CNT *(volatile unsigned short*)0x4000102
#define REG_TM1CNT *(volatile unsigned short*)0x4000106
#define REG_TM2CNT *(volatile unsigned short*)0x400010A
#define REG_TM3CNT *(volatile unsigned short*)0x400010E

// Timer values
#define REG_TM0D       *(volatile unsigned short*)0x4000100
#define REG_TM1D       *(volatile unsigned short*)0x4000104
#define REG_TM2D       *(volatile unsigned short*)0x4000108
#define REG_TM3D       *(volatile unsigned short*)0x400010C

// Timer flags
#define TIMER_ON      (1<<7)
#define TIMER_OFF     (0<<7)
#define TM_IRQ        (1<<6)
#define TM_CASCADE    (1<<2)
#define TM_FREQ_1     0
#define TM_FREQ_64    1
#define TM_FREQ_256   2
#define TM_FREQ_1024  3

void Timer::startTimer() {
    REG_TM3CNT = 0;
    REG_TM3D = 0;
    REG_TM3CNT = TIMER_ON | TM_IRQ | TM_CASCADE;

    REG_TM2CNT = 0;
    REG_TM2D = 65536-16384;
    REG_TM2CNT = TIMER_ON | TM_IRQ | TM_FREQ_1024;
}

int Timer::getTime() {


    short seconds = REG_TM3D;
    short millis = (REG_TM2D&~(~0<<14));
    millis = millis*1000/(1<<14);

    return ((int)seconds*1000) + millis;
}

std::string Timer::millisToString(int millis) {
    short minutes = millis / 60000;
    short seconds = (millis % 60000) / 1000;
    short milliseconds = millis % 1000;

    char output[20] = {'\0'};

    sprintf(output, "%d:%02d.%03d", minutes, seconds, milliseconds);
    return std::string(output);

    // return std::to_string(minutes) + std::string(":") + std::to_string(seconds) + std::string(".") + std::to_string(milliseconds); 
}