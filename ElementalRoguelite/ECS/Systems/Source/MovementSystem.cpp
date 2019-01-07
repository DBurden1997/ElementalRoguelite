//
//  MovementSystem.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-01.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "MovementSystem.hpp"

#include <memory>
#include "Vec2D.hpp"
#include "EventList.hpp"

MovementSystem::MovementSystem()
{
    for ( int x = -1; x <= 1; ++x )
    {
        m_normalVelocities.push_back( {} );
        for ( int y = -1;  y <= 1; ++y )
        {
            Vec2D< float > vec( x, y );
            if( x != 0 && y != 0 )  { vec.normalize(); }
            m_normalVelocities[ x+1 ].push_back( vec );
        }
    }
}

void MovementSystem::update()
{
    m_movableEntities = m_entityManager->getEntitiesWithComponents( { "transform" } );
    
    // For each entity in the list update its position
    for( auto id : m_movableEntities )
    {
        // Get the transform component
        std::shared_ptr< TransformComponent > transform = std::dynamic_pointer_cast< TransformComponent >( m_entityManager->getComponent( id, "transform" ) );
        
        // Set the previous position
        transform->m_prevPosition = transform->m_position;
        // Update the position by the velocity
        transform->m_position += transform->m_velocity;
    }
}

void MovementSystem::handleEvent( const Event_Type_Enum type, IEvent &event )
{
    switch ( type ) {
        case EVENT_MOVEMENT:
        {
            MovementEvent e = dynamic_cast<MovementEvent&>( event );
            std::shared_ptr< TransformComponent > transform = std::dynamic_pointer_cast< TransformComponent >( m_entityManager->getComponent( e.m_entId, "transform" ) );
            if( e.m_axis )
            {
                transform->m_dir.setSecond( e.m_dir );
            }
            else
            {
                transform->m_dir.setFirst( e.m_dir );
            }
            Vec2D< int >dir = transform->m_dir;
            transform->m_velocity = m_normalVelocities[dir.first()+1][dir.second()+1];
            break;
        }
        default:
            break;
    }
}
