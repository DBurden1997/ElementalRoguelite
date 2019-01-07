//
//  PlayerControlComponent.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "PlayerControlComponent.hpp"
#include <iostream>

PlayerControlComponent::PlayerControlComponent( EntityID ownerId, unsigned int playerNum ) :
    Component( ownerId, "playerControl" ),
    m_playerNum(playerNum) {}

void PlayerControlComponent::toString()
{
    std::cout << "Owner: " << owner() << " Type: " << type() << " ID: " << id();
    std::cout << "\nPlayer Number: " << m_playerNum;
}

