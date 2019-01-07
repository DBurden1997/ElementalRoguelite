//
//  TransformComponent.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "TransformComponent.hpp"

#include <iostream>

TransformComponent::TransformComponent( EntityID ownerId, float xPos, float yPos, float xVel, float yVel, float xO, float yO ) :
    Component( ownerId, "transform" ),
    m_position( Vec2D< float >( xPos, yPos ) ),
    m_prevPosition( Vec2D< float >( 0, 0 ) ),
    m_velocity( Vec2D< float >( xVel, yVel ) ),
    m_origin( Vec2D< float >( xO, yO ) )
{
    int dirX = 0;
    int dirY = 0;
    if( m_velocity.first() < 0 )
    {
        dirX = -1;
    }
    else if( m_velocity.first() > 0)
    {
        dirX = 1;
    }
    if( m_velocity.second() < 0 )
    {
        dirY = -1;
    }
    else if( m_velocity.second() > 0)
    {
        dirY = 1;
    }
    m_dir.setValues( dirX, dirY );
}

void TransformComponent::toString()
{
    std::cout << "Owner: " << owner() << " Type: " << type() << " ID: " << id();
    std::cout << "\nPosition: " << m_position;
    std::cout << "\nVelocity: " << m_velocity;
    std::cout << "\nOrigin: " << m_origin << "\n\n";
}
