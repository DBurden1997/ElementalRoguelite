//
//  Animation.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-03.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#include "Animation.hpp"

AnimFrame& Animation::addFrame( std::string &dir, int rowNum, int frameNum, SDL_Rect &frameBase, int frameLength )
{
    SDL_Rect frameRect;
    frameRect.x = frameBase.x + ( frameBase.w * frameNum );
    frameRect.y = frameBase.y + ( frameBase.h * rowNum );
    frameRect.w = frameBase.w;
    frameRect.h = frameBase.h;
    
    std::unique_ptr< AnimFrame > frame = std::make_unique<AnimFrame>( frameRect, frameLength );
    
    return *frame.get();
}

const std::string& Animation::getSpriteSheet()
{
    return m_spriteSheet;
}

const std::string& Animation::getName()
{
    return m_name;
}

bool Animation::doesReplay()
{
    return m_replay;
}

AnimFrame& Animation::getFrame( std::string &dir, int frameNum )
{
    return *m_frames[dir][frameNum].get();
}
