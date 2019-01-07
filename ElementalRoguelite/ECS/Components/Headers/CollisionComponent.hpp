//
//  CollisionComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef CollisionComponent_hpp
#define CollisionComponent_hpp

#include <memory>
#include <SDL2/SDL.h>
#include "Vec2D.hpp"
#include "IComponent.hpp"

class CollisionComponent : public Component<CollisionComponent>
{
public:
    // Offset of collision box from the position
    Vec2D< float > m_offset;
    
    // Size of the collision box
    Vec2D< float > m_size;
    
    // Type identifier
    std::string m_colliderType;
    
    //Constructor
    CollisionComponent( EntityID ownerId, const std::string& colliderType, int colWidth, int colHeight, int xOffset = 0, int yOffset = 0 );
    
    virtual void toString() override;
};

#endif /* CollisionComponent_hpp */
