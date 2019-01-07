//
//  TransformComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "Vec2D.hpp"
#include "IComponent.hpp"

class TransformComponent : public Component< TransformComponent >
{
public:
    // Position
    Vec2D< float > m_position = Vec2D< float >( 0, 0 );
    Vec2D< float > m_prevPosition = Vec2D< float >( 0, 0 );
    
    // Velocity
    Vec2D< float > m_velocity = Vec2D< float >( 0, 0 );
    
    // The origin of the entity
    Vec2D< float > m_origin = Vec2D< float >( 0, 0 );
    
    // The current direction of the entity
    //           8-Directional
    //      -------------------------
    //      | -1,-1 | -1, 0 | -1, 1 |
    //      -------------------------
    //      | 0,-1  | 0, 0  | 0, 1  |
    //      -------------------------
    //      | 1,-1  | 1, 0  | 1, 1  |
    //      -------------------------
    Vec2D< int > m_dir = Vec2D< int >( 0, 0 );
    
    // Constructors
    TransformComponent( EntityID ownerId, float xPos, float yPos, float xVel, float yVel, float xO, float yO );
    
    virtual void toString() override;
};

#endif /* TransformComponent_hpp */
