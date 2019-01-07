//
//  Animation.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-03.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <vector>
#include <string>

#include "Vec2D.hpp"
#include "AnimFrame.hpp"

class Animation
{
    // Name of sprite sheet texture
    std::string m_spriteSheet;
    
    // Name of the animation
    std::string m_name;
    
    // Direction of the animation
    std::string m_direction;
    
    // Offset in sprite sheet
    Vec2D< int > m_offset;
    
    // Sprite size
    Vec2D< int > m_size;
    
    // If the animation loops
    bool replay;
    
    // List of frames in the animation
    std::vector< AnimFrame > m_frames;
public:
};

#endif /* Animation_hpp */
