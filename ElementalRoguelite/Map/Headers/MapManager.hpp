//
//  MapManager.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef MapManager_hpp
#define MapManager_hpp

#include <vector>
#include <string>
#include <SDL2_image/SDL_image.h>
#include "Vec2D.hpp"
#include "Texture.hpp"
#include "TextureManager.hpp"
#include "MapReader.hpp"
#include "TransformComponent.hpp"
#include "CollisionComponent.hpp"

class MapManager
{
    //Tile dimensions
    const int m_tileHeight = 32;
    const int m_tileWidth = 32;
    
    //Vector containing data to use
    std::vector<std::vector<std::vector<int>>> m_mapData = {};
    
    //Name of the currently loaded map
    std::string m_mapName = "Default";
    
    //Pointer to the tileset of the current map
    std::shared_ptr<Texture> m_mapTileset = nullptr;
    
    //Pointer to a MapReader object
    std::shared_ptr<MapReader> m_mapReader = nullptr;
    
public:
    //Constructor
    MapManager( int tileHeight, int tileWidth );
    
    //Load a new map
    void loadMap( const std::string& mapName, TextureManager& aTextureManager );
    
    //Render the map
    void renderMap( std::shared_ptr<SDL_Renderer> aRenderer );
    
    //Check collisions with the background
    Vec2D< float > checkMapCollision( TransformComponent& transform, CollisionComponent& collider );
};

#endif /* MapManager_hpp */
