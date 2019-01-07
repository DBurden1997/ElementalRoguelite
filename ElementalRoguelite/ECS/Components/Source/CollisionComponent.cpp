//
//  CollisionComponent.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent( EntityID ownerId, const std::string& colliderType, int colWidth, int colHeight, int xOffset, int yOffset ) :
    Component<CollisionComponent>(ownerId, "collision" ),
    m_colliderType( colliderType ),
    m_offset( Vec2D< float >( xOffset, yOffset ) ),
    m_size( Vec2D< float >( colWidth, colHeight ) ) {}

void CollisionComponent::toString()
{
    std::cout << "Type: " << m_colliderType << "\nOffset: " << m_offset << "\nSize: " << m_size;
}
