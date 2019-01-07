//
//  TextureManager.cpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-25.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#include "TextureManager.hpp"

std::vector< std::shared_ptr<Texture> > TextureManager::m_loadedTextures = {};
std::shared_ptr<SDL_Renderer>  TextureManager::m_renderer = nullptr;

TextureManager::TextureManager( std::shared_ptr<SDL_Renderer> aRenderer )
{
    if( m_renderer.get() == nullptr )
    {
        m_renderer = aRenderer;
    }
}

std::shared_ptr<Texture> TextureManager::loadTexture( const std::string &name )
{
    //Create the file name
    std::string file = "Data/Sprites/";
    file.append( name );
    file.append( ".png" );
    
    //Load the texture
    auto newTexture = std::make_shared<Texture>( name );
    if( !( newTexture->loadFromFile( m_renderer, file ) ) )
    {
        printf( "Unable to load texture: %s!\n", file.c_str() );
    }
    
    //Add the texture to the list
    m_loadedTextures.push_back( newTexture );
    
    //Return the new texture
    return newTexture;
}

bool TextureManager::isLoaded( const std::string &name )
{
    //Search through the loaded textures for the name
    for( const auto& texture : m_loadedTextures ) {
        if( texture->name() == name ) {
            return true;
        }
    }
    
    //If the name isn't found return false
    return false;
}

std::shared_ptr<Texture> TextureManager::getTexture( const std::string &name )
{
    //Search through the loaded textures for the name
    for( const auto& texture : m_loadedTextures ) {
        if( texture->name() == name ) {
            return texture;
        }
    }
    
    //If the name isn't found return false
    return loadTexture( name );
}

//Free all textures
void TextureManager::freeTextures()
{
    for( auto& texture : m_loadedTextures )
    {
        texture->free();
    }
}

