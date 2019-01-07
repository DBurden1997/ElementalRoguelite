//
//  InputHandler.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-07.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include "Events.hpp"
#include "EventList.hpp"

typedef std::shared_ptr<IEvent> EventPointer;

class InputHandler
{
    // A map of SDL keys to intents
    std::map< std::string, std::pair< SDL_Keycode, SDL_Keycode > > m_keyMap;
    
    // A pointer to the Intent System
    std::shared_ptr< Publisher > m_publisher;
public:
    // Constructor
    InputHandler( std::shared_ptr< Publisher > intentSys );
    
    // Take an input event and determine the intent to be sent
    void getIntent( SDL_Event e );
};

#endif /* InputHandler_hpp */
