//
//  MovementSystem.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-01.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef MovementSystem_hpp
#define MovementSystem_hpp

#include <vector>
#include "Vec2D.hpp"
#include "ISystem.hpp"
#include "TransformComponent.hpp"

class MovementSystem : public ISystem
{
    // The list of entity ids
    std::vector< EntityID > m_movableEntities;
    
    // 2D Vector Containing Normalized Velocities
    std::vector< std::vector< Vec2D< float > > > m_normalVelocities;
    
public:
    // Constructor
    MovementSystem();
    
    // Handle entity movement
    virtual void update() override;
    
    // Handle events
    virtual void handleEvent( const Event_Type_Enum type, IEvent& event ) override;
};

#endif /* MovementSystem_hpp */
