//
//  GraphicComponent.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-30.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef GraphicComponent_hpp
#define GraphicComponent_hpp

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "IComponent.hpp"

class GraphicComponent: public Component< GraphicComponent >
{
public:
    // The name of the sprite sheet this component uses
    std::string m_spriteSheet;
    
    // Current clip of sprite sheet being used
    SDL_Rect m_spriteClip;
    
    // Constructor
    GraphicComponent( EntityID ownerId, const std::string& sheetName, int clipX, int clipY, int clipW, int clipH );
    GraphicComponent( EntityID ownerId, const std::string& sheetName, SDL_Rect& clip );
    
    virtual void toString() override;
};

#endif /* GraphicComponent_hpp */
