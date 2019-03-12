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
#include <map>
#include <string>
#include <memory>

#include "Vec2D.hpp"
#include "AnimFrame.hpp"

class Animation
{
    // Name of sprite sheet texture
    std::string m_spriteSheet;
    
    // Name of the animation
    std::string m_name;
    
    // If the animation loops
    bool m_replay;
    
    // List of frames in the animation
    std::map< std::string, std::vector< std::unique_ptr< AnimFrame > > > m_frames;
public:
    Animation( const std::string& spriteSheet, const std::string& name, bool replay ) : m_spriteSheet( spriteSheet ), m_name( name ), m_replay( replay ), m_frames( {} ) {}
    
    // Add a frame of the given direction to the animation and return a reference to the frame
    AnimFrame& addFrame( std::string& dir, int rowNum, int frameNum, SDL_Rect& frameBase, int frameLength );
    
    const std::string& getSpriteSheet();
    const std::string& getName();
    bool doesReplay();
    AnimFrame& getFrame( std::string& dir, int frameNum );
};

#endif /* Animation_hpp */
