//
//  PlayerControlComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef PlayerControlComponent_hpp
#define PlayerControlComponent_hpp

#include "IComponent.hpp"

class PlayerControlComponent : public Component< PlayerControlComponent >
{
public:
    // The player that will control this entity
    const unsigned int m_playerNum = 1;
    
    // Constructor
    PlayerControlComponent( EntityID ownerId, unsigned int playerNum = 1);
    
    virtual void toString() override;
};

#endif /* PlayerControlComponent_hpp */
