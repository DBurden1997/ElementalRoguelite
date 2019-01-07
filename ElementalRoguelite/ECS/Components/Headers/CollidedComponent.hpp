//
//  CollidedComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-11-11.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef CollidedComponent_hpp
#define CollidedComponent_hpp

#include "IComponent.hpp"

class CollidedComponent : public Component<CollidedComponent>
{
public:
    // The entity that has been collided with
    EntityID m_otherEntity;
    
    // Constructor
    CollidedComponent( EntityID otherEntity );
    
    void toString() override{};
};

#endif /* CollidedComponent_hpp */
