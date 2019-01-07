//
//  MapManager.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "MapManager.hpp"

#include "Physics.hpp"
#include "MapReader.hpp"
#include "TextureManager.hpp"

MapManager::MapManager( int tileHeight, int tileWidth ) : m_tileHeight( tileHeight ), m_tileWidth( tileWidth ), m_mapReader( new MapReader ) {}

void MapManager::loadMap( const std::string &mapName, TextureManager &aTextureManager )
{
    //Set the map name
    m_mapName = mapName;
    
    //Get the file name
    std::string fileName = "Data/Maps/";
    fileName.append( mapName );
    fileName.append( ".lvl" );
    
    //Load the level map
    m_mapData = m_mapReader->readMapFile( fileName );
    
    //If the map tileset is not loaded
    if( aTextureManager.isLoaded( m_mapName ) ) {
        m_mapTileset = aTextureManager.getTexture( m_mapName );
    }
    else {
        m_mapTileset = aTextureManager.loadTexture( mapName );
    }
}

void MapManager::renderMap( std::shared_ptr<SDL_Renderer> aRenderer )
{
    //Create a clip for rendering the correct tile
    SDL_Rect clip = { 0, 0, m_tileWidth, m_tileHeight };
    int xPos = 0;
    int yPos = 0;
    
    //Iterate through the level map rendering the correct tile
    for( int row = 0; row < m_mapData.size(); row++ ) {
        for( int col = 0; col < m_mapData[0].size(); col++ ){
            xPos = col * m_tileWidth;
            yPos = row * m_tileHeight;
            clip.x = m_mapData[row][col][0] * m_tileWidth;
            
            //Render the tile
            m_mapTileset->render( aRenderer, xPos, yPos, clip );
        }
    }
}


Vec2D< float > MapManager::checkMapCollision( TransformComponent& transform, CollisionComponent& collider )
{
    //Vector to hold resulting collision vector
    Vec2D<float> collisionVector(0,0);
    
    //For each row of tiles
    for( int row = 0; row < m_mapData.size(); row++ ) {
        //For each column of tiles
        for( int col = 0; col < m_mapData[0].size(); col++) {
            //If the tile is collidable
            if( m_mapData[row][col][1] ) {
                //Create two SDL rects to hold all connected collidable tiles as a single colliding box
                SDL_Rect tileCollider = { col * m_tileWidth, row * m_tileHeight, m_tileWidth, m_tileHeight };
                
                // Get the overlap of the collider with the horizontal rect
                Vec2D< float > overlapH = physics::getOverlap<float>(
                                          transform.m_position + collider.m_offset,
                                          collider.m_size,
                                          Vec2D< float >(tileCollider.x, tileCollider.y),
                                          Vec2D< float >(tileCollider.w, tileCollider.h));
                
                //If there is a collision with the horizontal rect
                if( !( overlapH.first() <= 0 || overlapH.second() <= 0 ) ){
                    // Get the previous overlap to help with collision resolution
                    Vec2D< float > prevOverlapH = physics::getOverlap<float>(
                                              transform.m_prevPosition + collider.m_offset,
                                              collider.m_size,
                                              Vec2D< float >(tileCollider.x, tileCollider.y),
                                              Vec2D< float >(tileCollider.w, tileCollider.h));
                    
                    // Resolve collisions
                    // Player came from x direction
                    if( prevOverlapH.second() > 0 )
                    {
                        // Player came from right
                        if( transform.m_position.first() > transform.m_prevPosition.first() )
                        {
                            // Push player out of the tile
                            collisionVector.setFirst( collisionVector.first() - overlapH.first() );
                        }
                        // PLayer came from left
                        else
                        {
                            // Push player out of the tile
                            collisionVector.setFirst( collisionVector.first() + overlapH.first() );
                        }
                    }
                    // Player came from y direction
                    else if( prevOverlapH.first() > 0 )
                    {
                        // Player came from above
                        if( transform.m_position.second() > transform.m_prevPosition.second() )
                        {
                            // Push player out of the tile
                            collisionVector.setSecond( collisionVector.second() - overlapH.second() );
                        }
                        // Player came from below
                        else
                        {
                            // Push player out of the tile
                            collisionVector.setSecond( collisionVector.second() + overlapH.second() );
                            
                        }
                    }
                }
            if( collisionVector != Vec2D< float >( 0, 0 ) )
            {
                return collisionVector;
            }
            }
        }
    }
    //Return the collision vector
    return collisionVector;
}




