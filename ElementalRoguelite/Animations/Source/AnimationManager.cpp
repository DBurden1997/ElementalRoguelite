//
//  AnimationManager.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2019-01-05.
//  Copyright © 2019 ElementalRoguelike. All rights reserved.
//

#include "AnimationManager.hpp"

#include <iostream>
#include <fstream>

// Get all collision boxes
void loadCollider( std::ifstream& stream, std::vector<SDL_Rect>& colliders ) {
    std::string token = "";
    std::string boxType = "";
    int numBoxes = 0;
    std::string colon, val = "";
    
    // Get the number of collision boxes
    stream >> token;
    if( token != "(" )  return;
    
    while( token != ")" )
    {
        stream >> token;
        if( token == "numBoxes" )
        {
            stream >> token;
            if( token != ":" ) return;
            stream >> numBoxes;
        }
    }
    
    stream >> token;
    if( token != "[" )  return;
    SDL_Rect collider;
    
    while( true )
    {
        stream >> token;
        if( token == "Box" )
        {
            stream >> token;
            if( token != "(" )  return;
            
            token = ",";
            while( token == "," )
            {
                stream >> token >> colon >> val;
                if( colon != ":")
                {
                    return;
                }
                
                if( token == "x" )
                {
                    collider.x = std::stoi(val);
                }
                if( token == "y" )
                {
                    collider.y = std::stoi(val);
                }
                if( token == "w" )
                {
                    collider.w = std::stoi(val);
                }
                if( token == "h" )
                {
                    collider.h = std::stoi(val);
                }
                
                stream >> token;
            }
            
            if( token != ")" )
            {
                return;
            }
            
            colliders.push_back(collider);
        }
        
        stream >> token;
        if( token == "]" )  return;
        
        if( token != "," )
        {
            return;
        }
    }
}

// Get info for a single animation frame
void AnimationManager::loadFrame( std::ifstream& stream, std::string& direction, Animation& anim, SDL_Rect& frameBase )
{
    std::string token, colon, val = "";
    int rowNum = 0;
    int frameNum = 0;
    int frameLength = 0;
    
    stream >> token;
    if( token != "(" )  return;
    
    token = ",";
    while( token == "," )
    {
        stream >> token >> colon >> val;
        if( colon != ":")
        {
            return;
        }
        
        if( token == "row" )
        {
            rowNum = std::stoi(val);
        }
        if( token == "frame" )
        {
            frameNum = std::stoi(val);
        }
        if( token == "length" )
        {
            frameLength = std::stoi(val);
        }
        
        stream >> token;
    }
    
    if( token != ")" )
    {
        return;
    }
    
    AnimFrame& newFrame = anim.addFrame(direction, rowNum, frameNum, frameBase, frameLength);
    
    if( token != "[" )  return;
    
    // Get collision info
    token = ",";
    while( token == "," )
    {
        stream >> token;
        if( token == "HurtBoxes" )
        {
            loadColliders( stream, newFrame.getHurtBoxes() );
        }
        if( token == "HitBoxes" )
        {
            loadColliders( stream, newFrame.getHitBoxes() );
        }
        
        stream >> token;
    }
    
    if( token == "]" )  return;
}

// Get the frames of the animation
void AnimationManager::loadFrames( std::ifstream &stream, std::string& direction, Animation& anim, SDL_Rect& frameBase )
{
    std::string token, colon, val = "";
    int numFrames = 0;
    
    // Get the number of frames
    stream >> token;
    if( token != "(" )  return;
    
    while( token != ")" )
    {
        stream >> token;
        if( token == "numFrames" )
        {
            stream >> token;
            if( token != ":" ) return;
            stream >> numFrames;
        }
    }
    
    stream >> token;
    if( token != "[" )  return;
    
    stream >> token;
    
    // Get each frame
    while( token == "Frame" )
    {
        loadFrame( stream, direction, anim, frameBase );
        stream >> token;
        if( token != "," ) break;
        stream >> token;
    }
        
    stream >> token;
    if( token != "]" )  printf("error\n");
    
    stream >> token;
    if( token != "," )
    {
        return;
    }
}

// Load a direction for an animation
void AnimationManager::loadDirection( std::ifstream &stream, std::string& direction, Animation& anim )
{
    std::string token, colon, val = "";
    SDL_Rect frameBase;
    
    stream >> token;
    if( token != "(" )  return;
    
    token = ",";
    while( token == "," )
    {
        stream >> token >> colon >> val;
        if( colon != ":")
        {
            return;
        }
        
        if( token == "x" )
        {
            frameBase.x = std::stoi(val);
        }
        if( token == "y" )
        {
            frameBase.y = std::stoi(val);
        }
        if( token == "w" )
        {
            frameBase.w = std::stoi(val);
        }
        if( token == "h" )
        {
            frameBase.h = std::stoi(val);
        }
        
        stream >> token;
    }
    
    if( token != ")" )
    {
        return;
    }
    
    if( token != "[" )  return;
    
    // Get list of frames
    token = ",";
    while( token == "," )
    {
        stream >> token;
        if( token == "Frames" )
        {
            loadFrames( stream, direction, anim, frameBase );
        }
        
        stream >> token;
    }
    
    if( token == "]" )  return;
}

bool isDirection( std::string& token )
{
    if( token == "Up" || token == "Down" || token == "Left" || token == "UpLeft" || token == "DownRight" )
    {
        return true;
    }
    return false;
}

// Load an animation
void AnimationManager::loadAnimation( std::ifstream &stream, std::string& animName )
{
    std::string token, colon, val = "";
    std::string spritesheet = "";
    bool replay;
    
    stream >> token;
    if( token != "(" )  return;
    
    token = ",";
    while( token == "," )
    {
        stream >> token >> colon >> val;
        if( colon != ":" )
        {
            return;
        }
        
        if( token == "sheet" )
        {
            spritesheet = val;
        }
        if( token == "replay" )
        {
            replay = std::stoi(val);
        }
        
        stream >> token;
    }
    
    stream >> token;
    if( token != ")" )
    {
        return;
    }
    
    std::shared_ptr<Animation> anim = std::make_shared<Animation>( spritesheet, animName, replay );
    
    if( token != "[" )  return;
    
    token = ",";
    while( token == "," )
    {
        stream >> token;
        if( isDirection(token) )
        {
            loadDirection( stream, token, *anim.get());
        }
        
        stream >> token;
    }
    
    if( token == "]" )  return;
}

void AnimationManager::loadFromFile( const std::string& fileName ) {
    std::ifstream stream;
    stream.open( fileName.c_str() );
    
    std::string setName, token = "";
    while( true )
    {
        stream >> setName >> token;
        if( token != "[" )
        {
            return;
        }
        
        loadAnimationSet( stream, setName );
        
        stream >> token;
        if( token != "]" )
        {
            return;
        }
        stream >> token;
        if( token == "end" )
        {
            break;
        }
        if( token != "," )
        {
            return;
        }
    }
}

