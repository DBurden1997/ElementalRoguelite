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
#include "AnimFrame.hpp"

typedef std::map<std::string, std::shared_ptr<Animation> > AnimationSet;

class AnimationManager
{
    // A map of names to animation sets
    std::map<std::string, AnimationSet > m_animationMap;
    
    // Loading helper functions
    void loadColliders( std::ifstream& stream, std::vector<SDL_Rect>& colliders );
    void loadFrame( std::ifstream& stream, std::string& direction, Animation& anim, SDL_Rect& frameBase );
    void loadFrames( std::ifstream& stream, std::string& direction, Animation& anim, SDL_Rect& frameBase );
    void loadDirection( std::ifstream& stream, std::string& direction, Animation& anim );
    void loadAnimation( std::ifstream& stream, std::string& animName );
    void loadAnimationSet( std::ifstream& stream, std::string& setName );
    
    bool isDirection( std::string& token );
public:
    // Constructor
    AnimationManager() {}
    
    // Load all animations in a file
    void loadFromFile(const std::string& fileName);
    
    // Get animation with the given name
    Animation& getAnimation(const std::string& animName);
    
};

#endif /* AnimationManager_hpp */
