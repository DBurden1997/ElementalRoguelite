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
    bool m_replay;
    
    // List of frames in the animation
    std::vector< AnimFrame > m_frames;
public:
    Animation( const std::string& spriteSheet, const std::string& name, const std::string& direction, Vec2D< int > offset, Vec2D< int > size, bool replay ) : m_spriteSheet( spriteSheet ), m_name( name ), m_direction( direction ), m_offset( offset ), m_size( size ), m_replay( replay ), m_frames( {} ) {}
};

#endif /* Animation_hpp */
