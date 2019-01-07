//
//  GraphicComponent.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "GraphicComponent.hpp"
#include <iostream>

GraphicComponent::GraphicComponent( EntityID ownerId, const std::string& sheetName, int clipX, int clipY, int clipW, int clipH ) :
    Component( ownerId, "graphic" ),
    m_spriteSheet( sheetName )
{
    m_spriteClip.x = clipX;
    m_spriteClip.y = clipY;
    m_spriteClip.w = clipW;
    m_spriteClip.h = clipH;
}

GraphicComponent::GraphicComponent( EntityID ownerId, const std::string& sheetName, SDL_Rect& clip ) :
    Component( ownerId, "graphic" ),
    m_spriteSheet( sheetName ),
    m_spriteClip( clip ) {}

void GraphicComponent::toString()
{
    std::cout << "Owner: " << owner() << " Type: " << type() << " ID: " << id();
    std::cout << "\nSprite Sheet: " << m_spriteSheet;
    std::cout << "\nClip: x: " << m_spriteClip.x << " y: " << m_spriteClip.y
    << " w: " << m_spriteClip.w << " h " << m_spriteClip.h << "\n\n";
}


