//
//  AnimFrame.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-03.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#include "AnimFrame.hpp"

const SDL_Rect& AnimFrame::getRect()
{
    return m_frameRect;
}

int AnimFrame::getLength()
{
    return m_frameLength;
}

std::vector<SDL_Rect>& AnimFrame::getHurtBoxes()
{
    return m_hurtBoxes;
}

std::vector<SDL_Rect>& AnimFrame::getHitBoxes()
{
    return m_hitBoxes;
}
