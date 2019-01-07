//
//  InputSystem.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "InputSystem.hpp"
#include "Vec2D.hpp"
#include "EventList.hpp"

InputSystem::InputSystem()
{
    m_inputActive = std::vector<bool>(INPUT_MAX, false);
}

void InputSystem::update()
{
    m_playerEntities = m_entityManager->getEntitiesWithComponents( { "playerControl" } );
}

void InputSystem::handleEvent( const Event_Type_Enum type, IEvent &event )
{
    bool axis = 0;
    int dir = 0;
    switch ( type ) {
        case EVENT_MOVE_UP:
        {
            m_inputActive[INPUT_MOVE_UP] = true;
            axis = true;
            dir = -1;
            break;
        }
        case EVENT_HALT_UP:
        {
            m_inputActive[INPUT_MOVE_UP] = false;
            axis = true;
            if( m_inputActive[INPUT_MOVE_DOWN])
                dir = 1;
            else
                dir = 0;
            break;
        }
        case EVENT_MOVE_DOWN:
        {
            m_inputActive[INPUT_MOVE_DOWN] = true;
            axis = true;
            dir = 1;
            break;
        }
        case EVENT_HALT_DOWN:
        {
            m_inputActive[INPUT_MOVE_DOWN] = false;
            axis = true;
            if( m_inputActive[INPUT_MOVE_UP])
                dir = -1;
            else
                dir = 0;
            break;
        }
        case EVENT_MOVE_LEFT:
        {
            m_inputActive[INPUT_MOVE_LEFT] = true;
            axis = false;
            dir = -1;
            break;
        }
        case EVENT_HALT_LEFT:
        {
            m_inputActive[INPUT_MOVE_LEFT] = false;
            axis = false;
            if( m_inputActive[INPUT_MOVE_RIGHT])
                dir = 1;
            else
                dir = 0;
            break;
        }
        case EVENT_MOVE_RIGHT:
        {
            m_inputActive[INPUT_MOVE_RIGHT] = true;
            axis = false;
            dir = 1;
            break;
        }
        case EVENT_HALT_RIGHT:
        {
            m_inputActive[INPUT_MOVE_RIGHT] = false;
            axis = false;
            if( m_inputActive[INPUT_MOVE_LEFT])
                dir = -1;
            else
                dir = 0;
            break;
        }
        default:
            break;
    }
    
    for( auto id : m_playerEntities )
    {
        m_publisher->raiseEvent<MovementEvent>( id, axis, dir );
    }
}
