//
//  TextureManager.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <string>
#include <vector>
#include <SDL2_image/SDL_image.h>
#include "Texture.hpp"

class TextureManager
{
    //List of all currently loaded textures
    static std::vector< std::shared_ptr<Texture> > m_loadedTextures;
    
    //The renderer that will render textures
    static std::shared_ptr< SDL_Renderer > m_renderer;
    
public:
    //Constructor
    TextureManager( std::shared_ptr<SDL_Renderer> aRenderer );
    
    //Load a texture
    std::shared_ptr<Texture> loadTexture( const std::string& name );
    
    //Check if the requested name is currently loaded
    bool isLoaded( const std::string& name );
    
    //Return a pointer to a texture based on its name
    std::shared_ptr<Texture> getTexture( const std::string& name );
    
    //Free all textures
    void freeTextures();
};

#endif /* TextureManager_hpp */
