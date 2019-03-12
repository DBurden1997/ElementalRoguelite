//
//  AnimFrame.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-03.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#ifndef AnimFrame_hpp
#define AnimFrame_hpp

#include <string>
#include <vector>

#include <SDL2/SDL.h>

class AnimFrame
{
    // The rect of the frame in the spritesheet
    SDL_Rect m_frameRect;
    
    // Number of game frames to spend in this frame
    unsigned int m_frameLength;
    
    // List of all hurtboxes for this frame
    std::vector<SDL_Rect> m_hurtBoxes;
    
    // List of all hitboxes for this frame
    std::vector<SDL_Rect> m_hitBoxes;
    
public:
    AnimFrame( SDL_Rect frameRect, int length ) : m_frameRect( frameRect ), m_frameLength( length ), m_hurtBoxes( {} ), m_hitBoxes( {} ) {}
    
    const SDL_Rect& getRect();
    int getLength();
    std::vector<SDL_Rect>& getHurtBoxes();
    std::vector<SDL_Rect>& getHitBoxes();
};

#endif /* AnimFrame_hpp */
