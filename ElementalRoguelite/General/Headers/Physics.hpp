//
//  Collision.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-27.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Physics_hpp
#define Physics_hpp

#include <SDL2/SDL.h>
#include "Vec2D.hpp"

// Namespace holding collision related functions
namespace physics
{
    // Get the overlap of two colliders
    template< typename T >
    Vec2D< T > getOverlap( const Vec2D< T >& aPos, const Vec2D< T >& aSize, const Vec2D< T >& bPos, const Vec2D< T >& bSize );
    
    //Check if there is a collision between two collider rects
    bool isCollision( const SDL_Rect& colliderOne, const SDL_Rect& colliderTwo );
    
    //Get the collision vector between two collider rects
    Vec2D< float > getCollisionVector( const SDL_Rect& colliderOne, const SDL_Rect& colliderTwo );
}

// Get overlap of two collider rects
template< typename T >
Vec2D< T > physics::getOverlap( const Vec2D< T >& aPos, const Vec2D< T >& aSize, const Vec2D< T >& bPos, const Vec2D< T >& bSize )
{
    Vec2D< T > aTempPos = aPos + (aSize / 2);
    Vec2D< T > bTempPos = bPos + (bSize / 2);
    // Get the difference in x and y positions
    Vec2D< T > delta( abs( aTempPos.first() - bTempPos.first() ), abs( aTempPos.second() - bTempPos.second() ) );
    
    // Set the overlaps
    T xOverlap = ( aSize.first() / 2 ) + ( bSize.first() / 2 ) - delta.first();
    T yOverlap = ( aSize.second() / 2 ) + ( bSize.second() / 2 ) - delta.second();
    
    // Return the overlap vector
    return Vec2D<T>(xOverlap, yOverlap);
}

#endif /* Physics_hpp */
