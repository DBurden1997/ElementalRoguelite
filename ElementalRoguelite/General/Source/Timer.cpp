//
//  Timer.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "Timer.hpp"

Timer::Timer() : startTicks( 0 ), pauseTicks( 0 ), started( false ), paused( false ) {}

void Timer::start() {
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the start ticks
    startTicks = SDL_GetTicks();
    pauseTicks = 0;
}

void Timer::stop() {
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;
    
    //Reset the ticks
    startTicks = 0;
    pauseTicks = 0;
}

void Timer::pause() {
    //If the timer is started and not paused
    if( started && !paused ) {
        //Pause the timer
        paused = true;
        
        //Set the paused ticks( number of ticks from start)
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    //If the timer is started and paused
    if( started && paused ) {
        //Unpause the timer
        paused = false;
        
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pauseTicks;
        
        //Clear pause ticks
        pauseTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    //The timer time
    Uint32 time = 0;
    
    //If the timer is started
    if( started ) {
        //If the timer is paused
        if( paused ) {
            //Return number of ticks when timer was paused
            time = pauseTicks;
        }
        else {
            //Return current time subtract when the timer started
            time = SDL_GetTicks() - startTicks;
        }
    }
    
    return time;
}
