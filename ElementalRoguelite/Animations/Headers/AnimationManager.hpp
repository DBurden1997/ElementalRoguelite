//
//  AnimationManager.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-05.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#ifndef AnimationManager_hpp
#define AnimationManager_hpp

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Animation.hpp"

class AnimationManager
{
    // A map of names to animations
    std::map<std::string, std::shared_ptr<Animation> > m_animationMap;
    
    // Loading helper functions
    loadHitboxes();
    loadFrames();
    loadDirection();
    loadAnimation();
    
public:
    // Constructor
    AnimationManager() {}
    
    // Load all animations in a file
    void loadFromFile(const std::string& fileName);
    
    // Get animation with the given name
    Animation& getAnimation(const std::string& animName);
    
};

#endif /* AnimationManager_hpp */
