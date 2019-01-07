//
//  InputHandler.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-07.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "InputHandler.hpp"

InputHandler::InputHandler( std::shared_ptr< Publisher > publisher ) :
    m_publisher( publisher )
{
    m_keyMap.insert( std::make_pair( "MOVE_UP", std::make_pair( SDLK_w, SDLK_UP ) ) );
    m_keyMap.insert( std::make_pair( "MOVE_DOWN", std::make_pair( SDLK_s, SDLK_DOWN ) ) );
    m_keyMap.insert( std::make_pair( "MOVE_LEFT", std::make_pair( SDLK_a, SDLK_LEFT ) ) );
    m_keyMap.insert( std::make_pair( "MOVE_RIGHT", std::make_pair( SDLK_d, SDLK_RIGHT ) ) );
}

void InputHandler::getIntent(SDL_Event e)
{
    // Get the intention string
    std::string intent = "none";
    for( auto it = m_keyMap.begin(); it != m_keyMap.end(); ++it )
    {
        if( it->second.first == e.key.keysym.sym || it->second.second == e.key.keysym.sym)
        {
            intent = it->first;
            break;
        }
    }
    
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        if( intent == "MOVE_UP" )
        {
            m_publisher->raiseEvent<MoveUpEvent>(1);
        }
        else if( intent == "MOVE_DOWN" )
        {
            m_publisher->raiseEvent<MoveDownEvent>(1);
        }
        else if( intent == "MOVE_LEFT" )
        {
            m_publisher->raiseEvent<MoveLeftEvent>(1);
        }
        else if( intent == "MOVE_RIGHT" )
        {
            m_publisher->raiseEvent<MoveRightEvent>(1);
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        if( intent == "MOVE_UP" )
        {
            m_publisher->raiseEvent<HaltUpEvent>(1);
        }
        else if( intent == "MOVE_DOWN" )
        {
            m_publisher->raiseEvent<HaltDownEvent>(1);
        }
        else if( intent == "MOVE_LEFT" )
        {
            m_publisher->raiseEvent<HaltLeftEvent>(1);
        }
        else if( intent == "MOVE_RIGHT" )
        {
            m_publisher->raiseEvent<HaltRightEvent>(1);
        }
    }
}
