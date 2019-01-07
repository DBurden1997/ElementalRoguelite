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
    // What row in the animation the frame is in
    unsigned int m_rowNum;
    
    // Frame within the row
    unsigned int m_frameNum;
    
    // Number of game frames to spend in this frame
    unsigned int m_frameLength;
    
    // List of all hurtboxes for this frame
    std::vector<SDL_Rect> m_hurtBoxes;
    
    // List of all hitboxes for this frame
    std::vector<SDL_Rect> m_hitBoxes;
};

#endif /* AnimFrame_hpp */
