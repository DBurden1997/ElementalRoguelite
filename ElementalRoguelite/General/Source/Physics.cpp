//
//  Collision.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include <vector>
#include <SDL2/SDL.h>
#include "Physics.hpp"

// Namespace holding collision related functions
namespace physics {
    //Check if there is a collision between two collider rects
    bool isCollision( const SDL_Rect& colliderOne, const SDL_Rect& colliderTwo ) {
        //Positions of the sides of the collision rects
        //First collision rect
        int left1 = colliderOne.x;
        int right1 = colliderOne.x + colliderOne.w;
        int top1 = colliderOne.y;
        int bottom1 = colliderOne.y + colliderOne.h;
        //Second collision rect
        int left2 = colliderTwo.x;
        int right2 = colliderTwo.x + colliderTwo.w;
        int top2 = colliderTwo.y;
        int bottom2 = colliderTwo.y+ colliderTwo.h;
        //Collision flag
        bool collided = true;
        
        if( right1 <= left2 ) {
            collided = false;
        }
        else if( left1 >= right2 ) {
            collided = false;
        }
        else if( bottom1 <= top2 ) {
            collided = false;
        }
        else if( top1 >= bottom2 ) {
            collided = false;
        }
        
        return collided;
    }
    
    //Get the collision vector between two collider rects
    Vec2D< float > getCollisionVector( const SDL_Rect& colliderOne, const SDL_Rect& colliderTwo ) {
        // The collision vector to return
        Vec2D< float > collisionVector(0,0);
        //Positions of the sides of the collision rects
        //First collision rect
        float left1 = colliderOne.x;
        float right1 = colliderOne.x + colliderOne.w;
        float top1 = colliderOne.y;
        float bottom1 = colliderOne.y + colliderOne.h;
        //Second collision rect
        int left2 = colliderTwo.x;
        int right2 = colliderTwo.x + colliderTwo.w;
        int top2 = colliderTwo.y;
        int bottom2 = colliderTwo.y+ colliderTwo.h;
        
        //Get x penetration
        //Collided from the left
        collisionVector.setFirst( left2 - right1 );
        
        //Collided from the right
        if( abs( collisionVector.first() ) > ( right2 - left1 ) ) {
            collisionVector.setFirst( right2 - left1 );
        }
        
        //Get y penetration
        //Collided from the top
        collisionVector.setSecond( top2 - bottom1 );
        
        //Collided from the bottom
        if( abs( collisionVector.second() ) > abs( bottom2 - top1 ) ) {
            collisionVector.setSecond( bottom2 - top1 );
        }
        
        if( abs( collisionVector.first() ) <= abs( collisionVector.second() ) ) {
            collisionVector.setSecond( 0 );
        }
        else if( abs( collisionVector.first() ) > abs( collisionVector.second() ) ) {
            collisionVector.setSecond( 0 );
        }
        return collisionVector;
    }
}
