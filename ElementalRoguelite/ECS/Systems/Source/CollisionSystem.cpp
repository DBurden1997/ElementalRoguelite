//
//  CollisionSystem.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-10-29.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "Vec2D.hpp"
#include "Physics.hpp"
#include "CollisionSystem.hpp"
#include "TransformComponent.hpp"
#include "CollisionComponent.hpp"

std::vector< EntityID > CollisionSystem::m_collisionEntities = {};

void CollisionSystem::checkBackgroundCollisions( EntityID id )
{
    //Get the collision and position component of the entity we are checking collisions for
    CollisionComponent& collider = dynamic_cast<CollisionComponent&>( *( m_entityManager->getComponent( id, "collision") ) );
    TransformComponent& transform = dynamic_cast<TransformComponent&>( *(  m_entityManager->getComponent( id, "transform") ) );
    
    //Get the collision vector from the Map Manager's collision function
    std::shared_ptr<MapManager> mapMan = m_mapManager.lock();
    Vec2D< float > collisionVector = mapMan->checkMapCollision( transform, collider );
    
    //While there are still collisions keep updating positions
    while( !(collisionVector == Vec2D< float >(0,0) )) {
        //Update position of the position component and collision rects
        transform.m_position += collisionVector;
        
        //Check collisions again to verify there are no more
        collisionVector = mapMan->checkMapCollision( transform, collider );
    }
}

void CollisionSystem::checkEntityCollisions( EntityID id )
{
    //For each collision entity
    for( auto otherId : m_collisionEntities )
    {
        //Flag signalling a collision took place
        bool wasCollision = false;
        //If it isn't the entity we are currently checking collisions for
        if( id != otherId )
        {
            
            //Get the collision and position component of the entity we are checking collisions for
            CollisionComponent& collider = dynamic_cast<CollisionComponent&>( *( m_entityManager->getComponent( id, "collision") ) );
            TransformComponent& transform = dynamic_cast<TransformComponent&>( *(  m_entityManager->getComponent( id, "transform") ) );
            
            
            //Get the collision and position component of the other entity
            CollisionComponent& otherCollider = dynamic_cast<CollisionComponent&>( *( m_entityManager->getComponent( otherId, "collision") ) );
            TransformComponent& otherTransform = dynamic_cast<TransformComponent&>( *(  m_entityManager->getComponent( otherId, "transform") ) );
            
            // Get the overlap
            Vec2D< float > overlap = physics::getOverlap<float>(transform.m_position + collider.m_offset,
                                                         collider.m_size,
                                                         otherTransform.m_position + otherCollider.m_offset,
                                                         otherCollider.m_size);
            
            //While there are collisions
            while( !( overlap.first() <= 0 || overlap.second() <= 0 ) )
            {
                //Set flag to true
                wasCollision = true;
                
                // Get the previous overlap
                Vec2D< float > prevOverlap = physics::getOverlap<float>(transform.m_prevPosition + collider.m_offset,
                                                             collider.m_size,
                                                             otherTransform.m_prevPosition + otherCollider.m_offset,
                                                             otherCollider.m_size);
                
                // Resolve collisions
                // Player came from x direction
                if( prevOverlap.second() > 0 )
                {
                    // Player came from right
                    if( transform.m_position.first() >= transform.m_prevPosition.first() )
                    {
                        // Push player out of the tile
                        transform.m_position.setFirst( transform.m_position.first() - overlap.first() );
                    }
                    // PLayer came from left
                    else
                    {
                        // Push player out of the tile
                        transform.m_position.setFirst( transform.m_position.first() + overlap.first() );
                    }
                }
                // Player came from y direction
                else if( prevOverlap.first() > 0 )
                {
                    // Player came from above
                    if( transform.m_position.second() >= transform.m_prevPosition.second() )
                    {
                        // Push player out of the tile
                        transform.m_position.setSecond( transform.m_position.second() - overlap.second() );
                    }
                    // Player came from below
                    else
                    {
                        // Push player out of the tile
                        transform.m_position.setSecond( transform.m_position.second() + overlap.second() );
                        
                    }
                }
                
                // Get the overlap again
                overlap = physics::getOverlap<float>(transform.m_position + collider.m_offset,
                                                             collider.m_size,
                                                             otherTransform.m_position + otherCollider.m_offset,
                                                             otherCollider.m_size);
            }
        }
    }
}

CollisionSystem::CollisionSystem( std::shared_ptr<MapManager> mapManager ) : m_mapManager( mapManager ) {}

void CollisionSystem::update()
{
    m_collisionEntities = m_entityManager->getEntitiesWithComponents( { "transform", "collision" } );
    
    // For each entity in the list handle collisions
    for( auto id : m_collisionEntities )
    {
        checkBackgroundCollisions( id );
        checkEntityCollisions( id );
    }
}

void CollisionSystem::handleEvent( const Event_Type_Enum type, IEvent &event )
{
    // No events to handle so far
}

