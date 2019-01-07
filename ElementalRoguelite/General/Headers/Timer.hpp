//
//  Timer.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Timer {
public:
    //Constructor
    Timer();
    
    //Various basic functions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Get the timer's time
    Uint32 getTicks();
    
    //Check if stopped or paused
    bool isStarted() { return started; }
    bool isPaused() { return paused; }
    
private:
    //The clock time when the timer started
    Uint32 startTicks;
    
    //Ticks stored when the imer was paused
    Uint32 pauseTicks;
    
    //Started and paused flags
    bool started;
    bool paused;
};

#endif /* Timer_hpp */
